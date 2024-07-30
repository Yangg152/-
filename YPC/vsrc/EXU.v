module EXU #(DATA_WIDTH = 32) (
  input clk,
  input rst,
  input [31:0] immI,
  input [31:0] rs1_value, rs2_value, rd_value,
  input [6:0] opcode7,
  input [2:0] opcode3,
  output reg [31:0] result
);

  assign result = immI + rs1_value;
  
endmodule
