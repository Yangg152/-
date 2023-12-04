module top (
  input clk,
  input start,
  input stop,
  input rst,
  output reg [6:0] out1,
  output reg [6:0] out2
);

  wire [6:0] cout1;
  wire [6:0] cout2;
  wire clk1hz;
  // 实例化计数器模块
  divclk clk1(
    .clk_5MHz(clk),
    .clk_1Hz(clk1hz)
  );

  count count99 (
    .clk(clk1hz),
    .start(start),
    .stop(stop),
    .rest(rst),
    .out1(cout1),
    .out2(cout2)
  );

  bcd7seg seg1 (
    .b(cout1[3:0]),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out1)    // 将七段显示输出连接到bcd7seg模块的输出
  );

  bcd7seg seg2 (
    .b(cout2[3:0]),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out2)    // 将七段显示输出连接到bcd7seg模块的输出
  );

endmodule
