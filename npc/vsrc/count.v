module count(
    input clk,
    input start,
    input stop,
    input rest,
    output reg [6:0] out1,
    output reg [6:0] out2
);

reg [6:0] count;

always @(posedge clk) 
begin
    if (rest) 
    begin
        count <= 0;
    end 
    else if (start && !stop) 
    begin
        if (count == 99) 
        begin
            count <= 0;
        end 
        else 
        begin
            count <= count + 1;
        end
    end
    out1 = count % 10; // 个位数
    out2 = count / 10; // 十位数
end


endmodule
