module Keyboard_display(
  input clk,       // 时钟信号
  input rst,       // 复位信号
  input [7:0] keys, // 按键输入
  output reg [3:0] out1, // 七段数码管输出
  output reg [3:0] out2, // 七段数码管输出
  output reg [3:0] out3, // 七段数码管输出
  output reg [3:0] out4, // 七段数码管输出
  output reg [3:0] out5, // 七段数码管输出
  output reg [3:0] out6 // 七段数码管输出
);

// 定义状态
reg [1:0] state;
parameter IDLE = 2'b00;
parameter PRESS = 2'b01;
parameter RELEASE = 2'b10;
parameter init = 2'b11;


// 初始化ROM
reg [7:0] rom[0:255];
// 初始化ROM
initial begin
    // 定义扫描码到ASCII码的映射
    rom[8'h1C] = 8'h61; // 'a'
    rom[8'h32] = 8'h62; // 'b'
    // ... 添加其他映射
end


// 寄存器和计数器
reg [7:0] prev_keys;
reg [15:0] key_count;
reg [7:0] temp1;
reg [7:0] temp2;
reg [15:0] tempout1;
reg [15:0] tempout2;

always @(posedge clk or posedge rst) begin
  if (rst) begin
    state <= init;
    prev_keys <= keys;
    key_count <= 0;
    temp1 <= 0;
    temp2 <= 0;
  end else begin
    // 添加一个新的状态DEBOUNCE
    case (state)
      init:
        if (keys == prev_keys) begin
          state <= init;
          key_count <= 0;
          prev_keys <= keys;
          temp1 <= 0;
          temp2 <= 0;
        end else begin
          state <= PRESS;
          prev_keys <= keys;
        end
      IDLE:
        if (keys != prev_keys) begin
          state <= PRESS;
          prev_keys <= keys;
          temp1 <= rom[keys];
          temp2 <= keys;
          if (keys == 8'hf0)
          key_count <= key_count + 1;
        end else begin
          state <= IDLE;
          key_count <= key_count;
          prev_keys <= keys;
          temp1 <= temp1;
          temp2 <= temp2;
        end
      PRESS:
        if (keys == prev_keys) begin
            // 检测到按键稳定，切换到RELEASE状态
            state <= RELEASE;
            temp1 <= rom[keys];
            temp2 <= keys;
          end
      RELEASE:
        if (keys != prev_keys) begin
          state <= IDLE;
          prev_keys <= keys;
          temp1 <= rom[keys];
          temp2 <= keys;
        end
      default:
        state <= init;
    endcase
  end
    out1 <= temp1[3:0];
    out2 <= temp1[7:4];
    out3 <= temp2[3:0];
    out4 <= temp2[7:4];
    tempout1 <= key_count % 10; // 个位数
    tempout2 <= key_count / 10; // 十位数
    out5 <= tempout1[3:0];
    out6 <= tempout2[3:0];
end

endmodule
