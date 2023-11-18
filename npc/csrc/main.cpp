 #include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <nvboard.h>
 
#include "Vtop.h"
#include "verilated.h"
 
#include "verilated_vcd_c.h"

static TOP_NAME dut;

void nvboard_bind_all_pins(Vtop* top);


int main(int argc,char** argv,char** env){
  nvboard_bind_all_pins(&dut);
  nvboard_init();
  
 
	  while(1) {
	    nvboard_update();
	    dut.f = dut.a ^ dut.b;	
	  }
	return 0;	
}
