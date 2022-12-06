module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input   logic               clk,    // this is the internal clock of the counter
    input   logic               rst,    // reset : this resets the counter back to 0 when asserted
    input   logic               en,     // when this signal is asserted, the counter counts up
    // input   logic               one,
    output  logic [WIDTH-1:0]   count   // this is the output signal which shows the count 
);

always_ff @ (posedge clk)
    if(rst) count <= {WIDTH{1'b0}};                 // when reset is asserted output signal count is receiving the value of 0
    else if(en)    count <= count + {{WIDTH-1{1'b0}}, en}; // if reset is not asserted output is the current value of count plus one; this shows that the value of count is saved in the register and then passed to an adder 
    else if(!en)          count <= count - {{WIDTH-1{1'b0}}, 1'b1};     // when en and rst are unasserted, count down

endmodule 
