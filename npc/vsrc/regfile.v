module regfile (
    input wire WrClk,      // 写入时钟
    input wire RegWr,      // 写入使能
    input wire [4:0] Ra, Rb, Rw, // 读写地址
    input wire [31:0] busW, // 写入数据
    output wire [31:0] busA, busB // 读出数据
);

reg [31:0] registers [31:0]; // 32个32位寄存器

// 初始化寄存器（假设初始状态为0）
integer i;
initial begin
    for (i = 0; i < 32; i = i + 1) begin
        registers[i] = 32'b0;
    end
end

// 写操作（在时钟下降沿）
always @(negedge WrClk) begin
    if (RegWr && Rw != 5'b0) begin // 如果写使能有效且不是x0寄存器
        registers[Rw] <= busW;
    end
end

// 读操作（非同步）
assign busA = (Ra == 5'b0) ? 32'b0 : registers[Ra]; // 如果是x0寄存器则输出0
assign busB = (Rb == 5'b0) ? 32'b0 : registers[Rb]; // 如果是x0寄存器则输出0

endmodule
