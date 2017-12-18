#!/bin/sh

# Compile proto into pb file
protoc -ocommands.pb commands.proto

# Generate C code from pb file
python ~/Documents/Arduino/libraries/nanopb-master/generator/nanopb_generator.py commands.pb

# move the header files up one level into the source code directory
mv *.h *.c ../
