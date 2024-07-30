module top (
  input clk,
  input rst,
  input [31:0] inst,
  output reg [31:0] out,
  output reg [31:0] pc // 添加一个输出端口
);

  reg [31:0]  pc_n;
  Reg #(32, 32'h80000000) pc_reg (clk, rst, pc_n, pc, 1'b1);
  assign pc_n = (pc == 0) ? 32'h80000000 : pc + 4;

  IFU ifu (
    .clk         (clk),
    .rst         (rst),
    .pc          (pc),
    .inst        ()
  );

  wire [31:0]   imm;
  wire [4:0]    rd, rs1, rs2;
  wire [6:0]    opcode7;
  wire [2:0]    opcode3;

  IDU idu (
    .clk         (clk),
    .rst         (rst),
    .inst        (inst),
    .imm         (imm),
    .rd          (rd),
    .rs1         (rs1),
    .rs2         (rs2),
    .opcode7     (opcode7),
    .opcode3     (opcode3),
    .wen         (wen)
  );

  wire [31:0]   wdata;
  wire          wen;
  wire [31:0]   rs1_value, rs2_value, rd_value;
  wire [31:0]   result; 

  EXU exu(
    .clk               (clk),
    .rst               (rst),
    .immI              (imm),
    .opcode7           (opcode7),
    .opcode3           (opcode3),
    .rd_value          (rd_value),
    .rs1_value         (regfile_out),
    .rs2_value         (rs2_value),
    .result            (result)    
  );

  wire [31:0]   regfile_out;
  // 寄存器文件模块
  RegisterFile regfile (
    .clk(clk),
    .wen(wen),
    .wdata(result),
    .waddr(rd),
    .raddr(rs1),
    .rdata(regfile_out)
  );

  
endmodule
