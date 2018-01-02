//---------------------------------------------------------------
//-- Arduino Mega Stack Light Enclosure (Brandon Patram)
//-- (c) December, 2017
//---------------------------------------------------------------
//-- See repo license for licensing information
//---------------------------------------------------------------

// units are all in mm (millimeters)

$fs = .1; // increase resolution to every .5 units
$fa = 8;

//--------------------------------------
//-- Build 2D point array of an arc
//-- INPUTS:
//--   start: starting angle
//--   end: ending angle
//--   r: radius of circle to build arc from
//--   offset: 2D coords to offset all points by. Default: [0,0]
//--------------------------------------
function arc_points(start, end, r, offset = [0, 0]) = [
    for (a = [start : (start < end ? $fa : $fa * -1) : end]) [
        ((r * cos(a)) + offset[0]), ((r * sin(a)) + offset[1])
    ]
];

//--------------------------------------
//-- Build 2D polygon of an arc
//-- INPUTS:
//--   start: starting angle
//--   end: ending angle
//--   r: radius of circle to build arc from
//--   offset: 2D coords to offset all points by. Default: [0,0]
//--   closed: Create a wedge shape or simply an arc. Default: false
//--------------------------------------
module arc(start = 0, end = 90, r = 1, closed = false, offset = [0, 0]) {
    p = arc_points(start, end, r, offset);
    if (closed) {
        polygon(concat(p, [ offset ]));
    } else {
        polygon(p);
    }
}

module pill(r, h, depth = 1) {
    linear_extrude(height = depth) {
        hull() {
            translate([0, (h/2)-r, 0]) { circle(r = r); }
            translate([0, ((h/2)-r)*-1, 0]) { circle(r = r); }
        }
    }
}

module rounded_rect(r, w, h, depth = 1) {
    hull() {
        translate([(w/2)-r, 0, 0]) { pill(r, h, depth = depth); }
        translate([((w/2)-r)*-1, 0, 0]) { pill(r, h, depth = depth); }
    }
}

//--------------------------------------
//-- Duplicate child object(s) in a circle
//-- INPUTS:
//--   clones: Number of objects to be ditributed around the circle. Default: 1
//--   r: radius of circle to build arc from. Default: 1
//--------------------------------------
module radial_cloner(clones = 1, r = 1) {
    function calculate_angle(index, length) = 360/length * index;

    for (i = [0 : 1 : clones]) {
        translate([cos(calculate_angle(i, clones)) * r, sin(calculate_angle(i, clones)) * r, 0]) {
            rotate([0, 0, calculate_angle(i, clones)]) {
                children();
            }
        }
    }
}

//--------------------------------------
//-- Duplicate child object(s) along a point array
//-- INPUTS:
//--   clones: Number of objects to be ditributed around the circle. Default: 1
//--   points: Array of 2D or 3D coords to clone child on to
//--------------------------------------
module vertex_cloner(clones = 1, points = []) {
    for (p = points) {
        for (i = [0 : 1 : clones]) {
            translate(p) {
                children();
            }
        }
    }
}

module stack_light() {
    base_radius = 8/2;
    stack_radius = 5/2;
    base_height = .95;
    fillet_radius = .2;
    wall_thickness = .2;
    middle_wirehole_radius = 1.3/2;
    wire_cutaway_height = .5;
    mount_hole_radius = .4/2;

    function stack_light_base() = concat(
        [[0, 0], [base_radius, 0], [base_radius, base_height - fillet_radius]],
        arc_points(0, 90, r = fillet_radius, offset = [base_radius - fillet_radius, base_height - fillet_radius]),
        [[base_radius - fillet_radius, base_height], [stack_radius - fillet_radius, base_height]],
        arc_points(270, 180, r = fillet_radius, offset = [stack_radius - fillet_radius, base_height + fillet_radius]),
        [[0, base_height + fillet_radius]]
    );

    module base() {
        difference() {
            union() {
                difference() {
                    // main base shape
                    rotate_extrude() { polygon(stack_light_base()); }
                    // inner base to cut out
                    cylinder(h = base_height - fillet_radius, r = base_radius - wall_thickness);
                }
                radial_cloner(clones = 3, r = base_radius - .8) {
                    // outer mount screw hole walls
                    translate([0, 0, .1]) { cylinder(r = 1/2 + wall_thickness, h = base_height - .1 - fillet_radius); }
                    // inner mount hole thickness
                    rotate([0, 0, 90]) { pill(r = .4/2 + wall_thickness, h = .6, depth = base_height); }
                }
            }
            // middle hole for wires
            cylinder(h = base_height + fillet_radius, r = middle_wirehole_radius);
            radial_cloner(clones = 3, r = base_radius - .8) {
                // inset mount screw hole
                translate([0, 0, .1 + wall_thickness]) { cylinder(r = 1.1/2, h = base_height - wall_thickness); }
                // mount screw hole
                translate([0, 0, -.4]) { rotate([0, 0, 90]) { pill(r = mount_hole_radius, h = .6, depth = base_height * 2); } }
            }
            // side cutout for wires
            translate([base_radius * -1, 0, (wire_cutaway_height - fillet_radius)/2]) { rotate([90, 0, 90]) { rounded_rect(w = 1.2, r = fillet_radius, h = wire_cutaway_height + fillet_radius, depth = wall_thickness * 4); } }
        }
    }

    base();
}

module enclosure() {
    stacklight_base_radius = 8/2;
    stacklight_base_height = .3;
    stacklight_mount_hole_radius = .1;
    fillet_radius = .2;
    wall_thickness = .2;
    pcb_box_size = [5.35, 10.16, 3.5];
    pcb_thickness = .16; // thickness of circut board itself
    box_inner_gap = .3;

    power_cutout_size = [.9, 1.5, 1.1];
    standoff_height = .5;
    standoff_outer_radius = .3; // no bigger than .3 because soilder points are in the way
    standoff_inner_radius = .1; // hole for screw
    pcb_hole_radius = .4/2;
    inner_box_size = [
        pcb_box_size[0] + box_inner_gap * 2,
        pcb_box_size[1] + box_inner_gap * 2,
        pcb_box_size[2] + standoff_height + box_inner_gap * 2
    ];
    standoff_coords = [ // these coords use the top left as the origin
        // top left (near power)
        [.05 + pcb_hole_radius, -1.2 - pcb_hole_radius],
        // top right (near usb)
        [pcb_box_size[0] - .08 - pcb_hole_radius, -1.33 - pcb_hole_radius],
        // bottom left
        [.05 + pcb_hole_radius, (pcb_box_size[1] * -1) + .3 + pcb_hole_radius],
        // bottom right
        [pcb_box_size[0] - .07 - pcb_hole_radius, (pcb_box_size[1] * -1) + .94 + pcb_hole_radius]
    ];

    module standoff() {
        render(convexity=12) {
            difference() {
                cylinder(h = standoff_height, r = standoff_outer_radius);
                // inner hole for screw
                translate([0, 0, wall_thickness]) { cylinder(h = standoff_height, r = standoff_inner_radius); }
            }
        }
    }
    
    module arduino() {
        // literal arduino board, useful to align standoffs and bounding box
        render(convexity=20) translate([pcb_box_size[0]/-2, pcb_box_size[1]/2, pcb_thickness]) {
            rotate([0, 0, 270]) {
                scale([.1, .1, .1]) {
                    // thank you: https://grabcad.com/library/arduino-mega-2560
                    import("./Arduino_MEGA2560.stl", convexity=15);
                }
            }
        }
    }

    module arduino_bounds() {
        usb_cutout_size = [1.27, 1.6, 1.1];
        usb_position = [ // these coords use the top left as the origin
            usb_cutout_size[0]/-2 - pcb_box_size[0]/-2 - .92,
            usb_cutout_size[1]/-2 + pcb_box_size[1]/2 + .65,
            usb_cutout_size[2]/2
        ];

        // bounding box of arduino and relay board
        translate([0, 0, pcb_box_size[2]/2]) { cube(pcb_box_size, center = true); }
        // usb bounding box
        translate([0, 0, pcb_thickness]) { translate(usb_position) { cube(usb_cutout_size, center = true); } }
    }

    module full_box() {
        outer_size = [
            inner_box_size[0] + wall_thickness * 2,
            inner_box_size[1] + wall_thickness * 2,
            inner_box_size[2] + wall_thickness * 2
        ];
        pcb_offset = [0, 0, standoff_height + wall_thickness];


        module box() {
            render(convexity=20) difference() {
                hull() {
                    // main outer housing
                    rounded_rect(r = fillet_radius, w = outer_size[0], h = outer_size[1], depth = outer_size[2]);
                    // main box cylinder/buldge
                    cylinder(r = stacklight_base_radius + wall_thickness, h = outer_size[2] + stacklight_base_height);
                }
                hull() {
                    // inner cylinder for case body
                    translate([0, 0, wall_thickness]) { 
                        cylinder(r = stacklight_base_radius, h = outer_size[2] - wall_thickness*2); 
                    }
                    // inner cutout
                    translate([0, 0, (inner_box_size[2]/2) + wall_thickness]) {
                        cube([inner_box_size[0], inner_box_size[1], inner_box_size[2]], center = true);
                    }
                }
                // bottom branding
                rotate([0, 0, 270]) {
                    linear_extrude(.1) {
                        mirror([1, 0, 0]) {
                            // if you need the Hack font you can find it here: https://github.com/source-foundry/Hack
                            // you can install via homebrew: brew tap caskroom/fonts; brew cask install font-hack
                            translate([0, .5, 0]) { text("ARDUINO STACK LIGHT", size = .5, font = "Hack:style=bold", halign = "center"); }
                            translate([0, -.5, 0]) { text("CONTROLLER Rev. 1", size = .5, font = "Hack:style=bold", halign = "center"); }
                        }
                    }
                }
                // holes for arduino connections (usb mainly)
                translate(pcb_offset) { arduino_bounds(); }
                
                // inner cylinder for the stacklight to sit on
                translate([0, 0, outer_size[2]]) {
                    cylinder(r = stacklight_base_radius, h = stacklight_base_height); 
                }
                // screw holes for stack light
                translate([0, 0, outer_size[2] - wall_thickness*2]) {
                    radial_cloner(clones = 3, r = stacklight_base_radius - .8) {
                        cylinder(r = stacklight_mount_hole_radius, h = wall_thickness * 4);
                    }
                }
            }

            // standoffs to screw arduino down into
            translate([pcb_box_size[0]/-2, pcb_box_size[1]/2]) {
                vertex_cloner(points = standoff_coords) {
                    // we move these up so they sit on top of the floor and not clip through
                    translate([0, 0, wall_thickness]) { standoff(); }
                }
            }
        }
        
        
        
        // cut off top to see bottom half
        difference() {
            box();
            translate([15/-2, 15/-2, 0]) { cube([15, 15, 1.5]); }
        }
        #color("Red", .5) translate(pcb_offset) arduino();
        
        translate([10,0,0]) {
            intersection() {
                box();
                translate([15/-2, 15/-2, 0]) { cube([15, 15, 1.5]); }
            }
            #color("Red", .5) translate(pcb_offset) arduino();
        }
    }
    
    full_box();
}

#color("Purple", .5) translate([0,0, 4.8]) { stack_light(); }
enclosure();
