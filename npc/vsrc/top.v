module top (
  input clk,
  input rst,
  input ps2_clk,
  input ps2_data,
  output reg [6:0] out1,
  output reg [6:0] out2,
  output reg [6:0] out3,
  output reg [6:0] out4,
  output reg [6:0] out5,
  output reg [6:0] out6,
  output reg [7:0] prbs_output // 8位伪随机序列输出
);

  wire [3:0] cout1;
  wire [3:0] cout2;
  wire [3:0] cout3;
  wire [3:0] cout4;
  wire [3:0] cout5;
  wire [3:0] cout6;
  wire clk1hz;
  wire [7:0] keyout;

  ps2_keyboard my_keyboard(
    .clk(clk),
    .resetn(~rst),
    .ps2_clk(ps2_clk),
    .ps2_data(ps2_data),
    .out(keyout)
  );

  Keyboard_display display1(
    .clk(clk),       // 时钟信号
    .rst(rst),       // 复位信号
    .keys(keyout), // 按键输入
    .out1(cout1), // 七段数码管输出
    .out2(cout2), // 七段数码管输出
    .out3(cout3), // 七段数码管输出
    .out4(cout4), // 七段数码管输出
    .out5(cout5), // 七段数码管输出
    .out6(cout6) // 七段数码管输出
  );

  divclk clk1(
    .clk_5MHz(clk),
    .clk_1Hz(clk1hz)
  );

  bcd7seg seg1 (
    .b(cout1),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out1)    // 将七段显示输出连接到bcd7seg模块的输出
  );
  bcd7seg seg2 (
    .b(cout2),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out2)    // 将七段显示输出连接到bcd7seg模块的输出
  );
  bcd7seg seg3 (
    .b(cout3),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out3)    // 将七段显示输出连接到bcd7seg模块的输出
  );
  bcd7seg seg4 (
    .b(cout4),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out4)    // 将七段显示输出连接到bcd7seg模块的输出
  );
  bcd7seg seg5 (
    .b(cout5),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out5)    // 将七段显示输出连接到bcd7seg模块的输出
  );
  bcd7seg seg6 (
    .b(cout6),   // 将BCD输入连接到bcd7seg模块的输入
    .h(out6)    // 将七段显示输出连接到bcd7seg模块的输出
  );
endmodule
