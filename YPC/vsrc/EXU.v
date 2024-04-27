module EXU #(DATA_WIDTH = 32) (
  input clk,
  input rst,
  input [31:0] immI,
  input [4:0] rd, rs1,
  input [6:0] opcode7,
  input [2:0] opcode3,
  output reg [31:0] wdata,
  output reg wen 
);

  // 寄存器文件模块
  RegisterFile regfile (
    .clk(clk),
    .wdata(wdata),
    .waddr(rs1),
    .wen(wen),
    .rdata(rs1_value)
  );

  reg [31:0] rs1_value; // 从寄存器文件中读取的rs1值

  always @(posedge clk) begin
    if (rst) begin
      wen <= 0;
    end
    else begin
      // 从寄存器文件中读取rs1的值
      rs1_value <= regfile.rdata;

      case (opcode3)
        3'b000: begin // ADDI
          wen <= 1;
          wdata <= rs1_value + immI;
        end
        // 添加其他指令的处理
        default: begin
          wen <= 0;
        end
      endcase
    end
  end
  
endmodule
