module DataMemory (
    input wire clk,            // 系统时钟
    input wire [31:0] address, // 地址
    input wire [31:0] write_data, // 写入的数据
    input wire [2:0] MemOP,    // 存储器操作类型
    output reg [31:0] read_data // 读出的数据
);

    // 假设使用128KB的存储器
    reg [7:0] memory [0:128*1024-1];

    // 写操作（在时钟的下降沿）
    always @(negedge clk) begin
        case (MemOP)
            3'b010: // 4字节写入
                {memory[address], memory[address+1], memory[address+2], memory[address+3]} = write_data;
            3'b001: // 2字节写入带符号扩展
                {memory[address], memory[address+1]} = write_data[15:0];
            3'b000: // 1字节写入带符号扩展
                memory[address] = write_data[7:0];
        endcase
    end

    // 读操作（在时钟的上升沿）
    always @(posedge clk) begin
        case (MemOP)
            3'b010: // 4字节读取
                read_data = {memory[address], memory[address+1], memory[address+2], memory[address+3]};
            3'b001: // 2字节读取带符号扩展
                read_data = {{16{memory[address+1][7]}}, memory[address], memory[address+1]};
            3'b101: // 2字节读取无符号扩展
                read_data = {16'b0, memory[address], memory[address+1]};
            3'b000: // 1字节读取带符号扩展
                read_data = {{24{memory[address][7]}}, memory[address]};
            3'b100: // 1字节读取无符号扩展
                read_data = {24'b0, memory[address]};
            default: 
                read_data = 32'b0;
        endcase
    end
endmodule
