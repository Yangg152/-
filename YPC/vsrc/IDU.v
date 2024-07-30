module IDU #(DATA_WIDTH = 32) (
  input clk,
  input rst,
  input [DATA_WIDTH-1:0] inst,
  output reg [31:0] imm,
  output reg [4:0] rd, rs1, rs2,
  output reg [6:0] opcode7,
  output reg [2:0] opcode3,
  output reg wen,
  output reg ebreak
);

  always @(*) begin
    if(rst == 1) begin
      imm     =  0;
      rd      =  0;
      rs1     =  0;
      rs2     =  0;
      opcode7 =  0;
      opcode3 =  0;
      wen     =  0;
    end else begin
      imm     =  {{21{inst[31]}}, inst[30:20]};
      rd      =  inst[11:7];
      rs1     =  inst[19:15];
      rs2     =  inst[24:20];
      opcode7 =  inst[6:0];
      opcode3 =  inst[14:12];
      wen     =  (imm != 0) ? 1'b1 : 1'b0;
    end
  end

  always @(*) begin
    case (opcode7)
      7'b1110011: begin
        case (opcode3)
          3'b000: begin
            if (inst[30:20] == 1) begin
              ebreak = 1'b1;
            end else begin
              ebreak = 1'b0;
            end
          end
          default: begin
            ebreak = 1'b0;
          end
        endcase
      end
      default: begin
        ebreak = 1'b0;
      end
    endcase
  end

endmodule
