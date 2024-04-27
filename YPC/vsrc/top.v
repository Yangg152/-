module top (
  input clk,
  input rst,
  input [31:0] inst,
  output reg [31:0] out,
  output reg [31:0] pc // 添加一个输出端口
);
  reg  [31:0]   pc_internal;
  wire [31:0]   imm;
  wire [4:0]    rd, rs1;
  wire [6:0]    opcode7;
  wire [2:0]    opcode3;
  wire [31:0]   wdata;
  wire          wen;

  // 将内部 pc 与外部 pc 同步
  always @(posedge clk) begin
    pc_internal <= pc;
  end

  always @(posedge clk) begin
    if(rst) begin
      pc_internal <= 32'h80000000;
    end
    else begin
      pc_internal <= pc_internal + 4;
    end
  end

  // 将内部 pc 输出到外部 pc
  assign pc = pc_internal;

  // IFU ifu (
  //   .clk         (clk),
  //   .rst         (rst),
  //   .pc          (pc_n)
  // );

  IDU idu (
    .clk         (clk),
    .rst         (rst),
    .inst        (inst),
    .imm         (imm),
    .rd          (rd),
    .rs1         (rs1),
    .opcode7     (opcode7),
    .opcode3     (opcode3)
  );

  EXU exu(
    .clk         (clk),
    .rst         (rst),
    .immI        (imm),
    .rd          (rd),
    .rs1         (rs1),
    .opcode7     (opcode7),
    .opcode3     (opcode3),
    .wdata       (wdata),
    .wen         (wen)
  );
  
endmodule
