module RegisterFile #(ADDR_WIDTH = 5, DATA_WIDTH = 32) (
  input clk,
  input wen,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input [ADDR_WIDTH-1:0] raddr,
  output reg [DATA_WIDTH-1:0] rdata
);

  reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

  // 初始化块，将所有寄存器的初始值设为 0
  initial begin
    integer i;
    for (i = 0; i < 2**ADDR_WIDTH; i = i + 1) begin
      rf[i] = 32'h00000000;
    end
  end

  always @(posedge clk) begin
    if (wen) rf[waddr] <= wdata;
  end

 assign rdata = (raddr == 0) ? 32'h00000000 : rf[raddr]; // Output 0 for address 0

endmodule
