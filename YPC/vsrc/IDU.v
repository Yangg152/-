module IDU #(DATA_WIDTH = 32) (
  input clk,
  input rst,
  input [DATA_WIDTH-1:0] inst,
  output reg [31:0]   imm     ,
  output reg [4:0]    rd, rs1, rs2  ,
  output reg [6:0]    opcode7  ,
  output reg [2:0]    opcode3  ,
  output reg          wen
);
  always @(*) begin
    if(rst == 1) begin
      assign  imm     =  0;
      assign  rd      =  0;
      assign  rs1     =  0;
      assign  rs2     =  0;
      assign  opcode7 =  0;
      assign  opcode3 =  0;
      assign  wen     =  0;
    end else begin
      assign  imm     =   {{21{inst[31]}}, inst[30:20]};
      assign  rd      =   inst[11:7];
      assign  rs1     =   inst[19:15];
      assign  rs2     =   inst[24:20];
      assign  opcode7 =   inst[6:0];
      assign  opcode3 =   inst[14:12];
      assign  wen     =   (imm != 0) ? 1'b1 : 0'b0;
    end
  end


endmodule
  
