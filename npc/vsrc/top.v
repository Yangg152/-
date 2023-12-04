module top (
    input rst,
    input [3:0] A, B, // 4位输入A和B
    input [2:0] Func, // 3位功能选择
    output reg [3:0] Result, // 4位结果
    output Zero, Carry, Overflow // 状态标志
);

ALU_4bit alu_instance (
    .A(A),
    .B(B),
    .Func(Func),
    .Result(Result),
    .Zero(Zero),
    .Carry(Carry),
    .Overflow(Overflow)
);

endmodule
