module PRBS(
  input clk,      // 模拟按钮作为时钟信号
  output reg [7:0] prbs_output, // 8位伪随机序列输出
  output reg [3:0] out1,    
  output reg [3:0] out2  
);

reg [7:0] shift_register = 8'b00000001;
reg [7:0] prbs;
reg [3:0] hex_value;

always @(posedge clk) begin
  // 伪随机序列生成
  shift_register[7] <= shift_register[4] ^ shift_register[3] ^ shift_register[2] ^ shift_register[0];
  shift_register[6:0] <= shift_register[7:1];

  // 将伪随机序列转换为十六进制
  prbs <= shift_register;
  out1 <= prbs[3:0] ; // 个位数
  out2 <= prbs[7:4]; // 十位数
  // 更新输出
  prbs_output <= prbs;
end

endmodule
