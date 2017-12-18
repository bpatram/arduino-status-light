#!/bin/sh

# Compile proto into pb file
protoc -ocommands.pb commands.proto

# Compile for JS consumtion
protoc --js_out=import_style=commonjs,binary:. commands.proto

# Generate C code from pb file
python ~/Documents/Arduino/libraries/nanopb-master/generator/nanopb_generator.py commands.pb

# Move the C output into the Arduino project
mv *.h *.c ../arduino-controller

# Move the JS output into the Node project
mv *.js ../node-serial-controller/src
