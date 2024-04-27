#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtop.h"

#define MEM_SIZE 1024  // 指令存储器大小
#define MAX_SIM_TIME 20  // 仿真总时钟边沿数
vluint64_t sim_time = 0; // 用于计数时钟边沿

static int mem[MEM_SIZE] = {

};

unsigned int pmem_read(unsigned int x) {
    // 假设要将addi指令存储到内存地址0处
    uint32_t rd = 5; // 寄存器t0的编号
    uint32_t rs1 = 1; // 寄存器t1的编号，假设是寄存器t1
    uint32_t imm = 10; // 立即数10
    uint32_t opcode = 0b0010011; // addi指令的操作码
    // 构建addi指令
    uint32_t addi_instr = (imm & 0xfff) | (rs1 << 15) | (rd << 7) | (opcode << 25);
    // 存储到内存中（假设存储到地址0）
    mem[0] = addi_instr;

    unsigned index = x/4;
    if (x < MEM_SIZE) {
        return mem[x];
    } else {
        // 如果地址超出了指令存储器的范围，返回0
        return 0;
    }
}

int main(int argc, char** argv, char** env) {
    Vtop *top = new Vtop; // 例化转换后的 TOP 模块
	  // 接下来的四行代码用于设置波形存储为VCD文件
    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;  
    top->trace(m_trace, 5);               
    m_trace->open("waveform.vcd");
	// 实际进行仿真的代码
    top->rst = 1;
    while (sim_time < MAX_SIM_TIME) {
        if(sim_time > 5) {
            top->rst = 0;
        }
        top->clk ^= 1; 
        top->inst = pmem_read(top->pc);
        top->eval();  
        m_trace->dump(sim_time);
        sim_time++; // 更新仿真时间
    }

    m_trace->close();
    delete top;
    exit(EXIT_SUCCESS);
}
