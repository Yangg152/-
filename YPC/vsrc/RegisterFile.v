module RegisterFile #(ADDR_WIDTH = 5, DATA_WIDTH = 32) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input wen,
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
    if (wen) begin
      if (waddr != 0) // Check if address is not 0
        rf[waddr] <= wdata;
    end
    rdata <= (waddr == 0) ? 32'h00000000 : rf[waddr]; // Output 0 for address 0
  end

endmodule
