#include "Vcounter.h"           // header included for a specific module, notice the way it is written #include "Vmodulename.h"
#include "verilated.h"          // this header included for all testbenches
#include "verilated_vcd_c.h"    // this header included for all testbenches

int main(int argc, char **argv, char **env){    // for all testbenches this is the layout for the main function
    int i;      // internal variables for the simulation: i for number of clock cycles, clk for the clock phase (0 or 1)      
    int clk;

    Verilated::commandArgs(argc, argv); // include this for all testbenches
    // ini top verilog instance 
    Vcounter* top = new Vcounter;   // instantiate a counter module 
    // init trace dump
    Verilated::traceEverOn(true);   // turn on signal tracing and dump the signal into a file named counter.vcd
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");  // make a file named counter.vcd and dump the trace in it 

    // initialise simulation inputs, these are variables inside the module we created, here the counter has three inputs: clk, rst, en
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation for many clock cycles: this for loop is where the simulation happens and controls how many clock cycles the simulation runs
    for (i = 0; i < 300; i++){

        // dump variables into the VCD file and toggle the clock
        for(clk = 0; clk < 2; clk++){       // runs twice for the two phases of the clock
            tfp->dump (2*i+clk);    //unit is in ps, 2*i+clk is the time from the time axis, which maybe means just dump the current value at the given time
            top->clk = !top->clk;   // change the clock signal within the top level entity (counter), which is toggling between 0 and 1
            top->eval ();           // force the model to evaluate on both sides of the clock
        }
        top->rst = (i < 2) | (i == 15);     // reset the counter to 0 on the clock cycle numbered 15(16th clock cycle since i starts at 0) and stay reset for two clock cycles 0 and 1
        top->en = (i > 4);      // enable counting after clock cycle numbered 4
        if(Verilated::gotFinish())  exit(0);
    }
    tfp->close();
    exit(0);
}