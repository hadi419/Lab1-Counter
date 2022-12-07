#!/bin/sh

# cleanup
rm -rf obj_dir
rm -f counter.vcd

# run verilator to translate verilog into c++, including c++ testbench
verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp

# build c++ progect via make automatically generated by Verilator
make -j -C obj_dir/ -f Vcounter.mk Vcounter

# run executable simulation file
obj_dir/Vcounter