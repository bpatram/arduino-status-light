#!/bin/sh

# Compile proto into pb file
protoc -ocommands.pb commands.proto

# Generate C code from pb file
python ~/Documents/Arduino/libraries/nanopb-master/generator/nanopb_generator.py commands.pb

# Move the C output into the Arduino project
mv *.h *.c ../arduino-controller
