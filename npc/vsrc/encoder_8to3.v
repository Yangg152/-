module encoder_8to3(
  input [7:0] binary_input,
  input en,
  output reg [2:0] encoded_output,
  output a
);

always @(en or binary_input) begin
  if (en == 0) begin
    encoded_output = 3'b000; // 默认情况，输出最高位1的位置
    a = 0;
  end else begin
    case (1'b1) // 只关心有1的位
      binary_input[7]: encoded_output = 3'b111;
      binary_input[6]: encoded_output = 3'b110;
      binary_input[5]: encoded_output = 3'b101;
      binary_input[4]: encoded_output = 3'b100;
      binary_input[3]: encoded_output = 3'b011;
      binary_input[2]: encoded_output = 3'b010;
      binary_input[1]: encoded_output = 3'b001;
      binary_input[0]: encoded_output = 3'b000;
      default: encoded_output = 3'b000; // 或者其他默认值
    endcase
    a = |binary_input; // a 为 1 当 binary_input 中有1时
  end
end


endmodule
