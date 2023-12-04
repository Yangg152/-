module ALU_4bit (
    input [3:0] A, B, // 4位输入A和B
    input [2:0] Func, // 3位功能选择
    output reg [3:0] Result, // 4位结果
    output Zero, Carry, Overflow // 状态标志
);

// 内部变量
reg [4:0] temp; // 用于存储中间结果和进位
assign Carry = temp[4]; // 进位标志
assign Overflow = ((A[3] ~^ B[3]) & (A[3] ^ Result[3])); // 溢出标志

always @(A, B, Func) begin
    temp = 5'b0;
    Result = 4'b0;
    case (Func)
        3'b000: temp = A + B; // 加法
        3'b001: temp = A - B; // 减法
        3'b010: Result = ~A; // 取反
        3'b011: Result = A & B; // 与
        3'b100: Result = A | B; // 或
        3'b101: Result = A ^ B; // 异或
        3'b110: Result = (A < B) ? 4'b0001 : 4'b0000; // 比较大小
        3'b111: Result = (A == B) ? 4'b0001 : 4'b0000; // 判断相等
        default: begin 
            Result = 4'b0000;
            temp = 5'b0;
        end
    endcase
    if (Func < 3'b110) // 对于加减法
        Result = temp[3:0]; // 只取低4位作为结果
end

assign Zero = (Result == 4'b0000); // 零标志

endmodule
