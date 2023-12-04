module top (
  input clk,
  input rst,
  input btn,
  output reg [6:0] out1,
  output reg [6:0] out2,
  output reg [7:0] prbs_output // 8位伪随机序列输出
);

  wire [3:0] cout1;
  wire [3:0] cout2;
  wire clk1hz;
  
  divclk clk1(
    .clk_5MHz(clk),
    .clk_1Hz(clk1hz)
  );

  PRBS pbrs1(
    .clk(clk1hz),      // 模拟按钮作为时钟信号
    .prbs_output(prbs_output), // 8位伪随机序列输出
    .out1(cout1),    
    .out2(cout2)  
  );

  bcd7seg seg1 (
    .b(cout1),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out1)    // 将七段显示输出连接到bcd7seg模块的输出
  );

  bcd7seg seg2 (
    .b(cout2),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out2)    // 将七段显示输出连接到bcd7seg模块的输出
  );

endmodule
