module top(
  input  rst,
  input  [7:0] a,
  input  [1:0] s,
  output [1:0] y
);
  wire [1:0] out;

  mux41b i0 (.a(a), .s(s), .y(out));
  
  assign y = out;
endmodule
