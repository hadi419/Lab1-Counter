module top #(
    parameter WIDTH = 8
)(
    // interface signals
    input logic                     clk,    // clock 
    input logic                     rst,    // reset
    input logic                     en,     // enable 
    input logic [WIDTH-1:0]         v,      // value to preload
    input logic                     ld,
    output logic [11:0]             bcd     // count output 
);

    logic   [WIDTH-1:0]             count;  // interconnect wire, this is the internal node insidde the design

counter myCounter (
    .clk (clk),
    .rst (rst),
    .en (en),
    .ld (ld),
    .v (v),
    .count (count)
);

bin2bcd myDecoder (
    .x (count),
    .BCD (bcd)
);

endmodule
