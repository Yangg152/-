module MuxKey #(
  parameter NR_KEY = 2, 
  parameter KEY_LEN = 1, 
  parameter DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 0) i0 (out, key, {DATA_LEN{1'b0}}, lut);
endmodule

module MuxKeyWithDefault #(
  parameter NR_KEY = 2, 
  parameter KEY_LEN = 1, 
  parameter DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [DATA_LEN-1:0] default_out,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 1) i0 (out, key, default_out, lut);
endmodule

module mux21e(a,b,s,y);
  input   a,b,s;
  output  y;
  MuxKey #(2, 1, 1) i0 (y, s, {
    1'b0, a,
    1'b1, b
  });
endmodule

module mux41b(a,s,y);
  input  [7:0] a;
  input  [1:0] s;
  output [1:0] y;
  MuxKey #(4, 2, 2) i0 (y, s, {
    2'b00, a[1:0],
    2'b01, a[3:2],
    2'b10, a[5:4],
    2'b11, a[7:6]
  });
endmodule