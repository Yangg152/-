module IDU #(DATA_WIDTH = 32) (
  input clk,
  input rst,
  input [DATA_WIDTH-1:0] inst,
  output reg [31:0]   imm     ,
  output reg [4:0]    rd, rs1  ,
  output reg [6:0]    opcode7  ,
  output reg [2:0]    opcode3  
);

  always @(posedge clk) begin
    if (rst) begin
      imm     <=   0;
      rd      <=   0;
      rs1     <=   0;
      opcode7 <=   0;
      opcode3 <=   0;
    end
    else begin
      imm     <=   {{21{inst[31]}}, inst[30:20]};
      rd      <=   inst[11:7];
      rs1     <=   inst[19:15];
      opcode7 <=   inst[6:0];
      opcode3 <=   inst[14:12];
    end
  end
endmodule
  
