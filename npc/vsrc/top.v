module top(
  input  rst,
  input  [7:0] a,
  input   en,
  output [3:0] y,
  output [6:0] seg,
  output aout
);

  wire [2:0] encoded_output;
  wire a_output;
  wire [6:0] segout;
  encoder_8to3 encoder1 (
    .binary_input(a),
    .en(en),
    .encoded_output(encoded_output),
    .a(a_output)
  );

  assign y = {1'b0, encoded_output};

  bcd7seg seg1(
    .b(y),
    .h(segout)
  );

  assign seg = segout;
  assign aout = a_output;
endmodule
