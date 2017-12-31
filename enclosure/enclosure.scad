// units are all in mm (millimeters)

$fs = .1; // increase resolution to every .5 units
$fa = 8;

function arc_points(start, end, r, offset = [0, 0]) = [ 
    for (a = [start : (start < end ? $fa : $fa * -1) : end]) [((r * cos(a)) + offset[0]), ((r * sin(a)) + offset[1]) ] 
];
    
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

module radial_cloner(clones = 1, radius = 1) {
    function calculate_angle(index, length) = 360/length * index;
    
    for (i = [0 : 1 : clones]) {
        translate([cos(calculate_angle(i, clones)) * radius, sin(calculate_angle(i, clones)) * radius, 0]) {
            rotate([0, 0, calculate_angle(i, clones)]) {
                children();
            }
        }
    }
}

module stack_light() {
    base_radius = 8/2;
    stack_radius = 4.9/2;
    base_height = .95;
    fillet_radius = .2;
    base_thickness = .2;
    middle_wirehole_radius = 1.3/2;
    wire_cutaway_height = .5;
    
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
                    cylinder(h = base_height - fillet_radius, r = base_radius - base_thickness);
                }
                radial_cloner(clones = 3, radius = base_radius - .8) {
                    // outer mount screw hole walls
                    translate([0, 0, .1]) { cylinder(r = 1/2 + base_thickness, h = base_height - .1 - fillet_radius); }
                    // inner mount hole thickness
                    rotate([0, 0, 90]) { pill(r = .4/2 + base_thickness, h = .6, depth = base_height); }
                }
            }
            // middle hole for wires
            cylinder(h = base_height + fillet_radius, r = middle_wirehole_radius);
            radial_cloner(clones = 3, radius = base_radius - .8) {
                // inset mount screw hole 
                translate([0, 0, .1 + base_thickness]) { cylinder(r = 1/2, h = base_height - base_thickness); }
                // mount screw hole
                translate([0, 0, -.4]) { rotate([0, 0, 90]) { pill(r = .4/2, h = .6, depth = base_height * 2); } }
            }
            // side cutout for wires
            translate([base_radius * -1, 0, (wire_cutaway_height - fillet_radius)/2]) { rotate([90, 0, 90]) { rounded_rect(w = 1.2, r = fillet_radius, h = wire_cutaway_height + fillet_radius, depth = base_thickness * 4); } }
        }
    }
        
    base();
}

stack_light();