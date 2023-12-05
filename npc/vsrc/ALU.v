module ALU (
    input wire [31:0] A, B, // ALU输入
    input wire [3:0] ALUctr, // ALU控制信号
    output reg [31:0] ALUout // ALU输出
);

// 中间变量
wire [31:0] sum;     // 加法或减法的结果
wire [31:0] shift;   // 移位操作的结果
wire less;           // 比较大小的结果
wire [31:0] bitwise; // 位运算结果

// 加法或减法
assign sum = ALUctr[3] ? A - B : A + B;

// 比较大小并设置less标志，使用减法操作的结果
assign less = (ALUctr[3]) ? A < B : $signed(A) < $signed(B); // ALUctr[3]=1为无符号比较，否则为有符号比较

// 移位操作
assign shift = (ALUctr[2] ? (ALUctr[3] ? $signed(A) >>> B[4:0] : A >> B[4:0]) : A << B[4:0]);

// 位运算
assign bitwise = (ALUctr[2:0] == 3'b100) ? A ^ B :
                 (ALUctr[2:0] == 3'b110) ? A | B :
                 (ALUctr[2:0] == 3'b111) ? A & B : 32'bx;

// ALU操作选择
always @(*) begin
    casex (ALUctr)
        4'b0xxx: ALUout = sum; // 加法或减法
        4'b10x0: ALUout = {31'b0, less}; // 比较大小
        4'b1x01: ALUout = shift; // 移位操作
        4'bx011: ALUout = B; // 直接输出B
        4'bx100: ALUout = bitwise; // 位运算 - 异或
        4'bx110: ALUout = bitwise; // 位运算 - 或
        4'bx111: ALUout = bitwise; // 位运算 - 与
        default: ALUout = 32'b0;
    endcasex
end

endmodule
