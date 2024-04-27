module top (
  input clk,
  input rst,
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

endmodule
