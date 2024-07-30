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

void mem_date() {
    // 假设要将addi指令存储到内存地址0处
    uint32_t rd = 5; // 寄存器t0的编号
    uint32_t rs1 = 1; // 寄存器t1的编号，假设是寄存器t1
    uint32_t imm = 10; // 立即数10
    uint32_t opcode = 0b0010011; // addi指令的操作码
    // 构建addi指令
    uint32_t addi_instr = ((imm & 0xfff) << 20) | (rs1 << 15) | (rd << 7) | (opcode);
    // 存储到内存中（假设存储到地址0）
    mem[0] = addi_instr;

    rd = 5; // 寄存器t0的编号
    rs1 = 1; // 寄存器t1的编号，假设是寄存器t1
    imm = 5; // 立即数10
    opcode = 0b0010011; // addi指令的操作码
    // 构建addi指令
    addi_instr = ((imm & 0xfff) << 20) | (rs1 << 15) | (rd << 7) | (opcode);
    // 存储到内存中（假设存储到地址0）
    mem[1] = addi_instr;

    addi_instr = 0x00100073;
    mem[2] = addi_instr;
}

unsigned int pmem_read(unsigned int pc) {
    int pc_offset = 0;
    pc_offset = pc - 0x80000000;
    unsigned index = pc_offset/4;
    if (pc_offset < MEM_SIZE && pc_offset >= 0) {
        return mem[index];
    } else {
        // 如果地址超出了指令存储器的范围，返回0
        return 0;
    }
}

bool top_out = 0;

extern "C" void top_break(bool re) {
    if(re == 1) {
        top_out =  1;
    }
    else {
        top_out =  0;
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
    mem_date();
    top->rst = 1;
    top->clk = 0;
    top->eval();    
    while (sim_time < MAX_SIM_TIME) {
    //while (!top_out) {
        if(sim_time > 8) {
            top->rst = 0; 
        }
        top->clk ^= 1; 
        top->eval(); 
        top->inst = pmem_read(top->pc);
        top->eval(); 
        m_trace->dump(sim_time);
        sim_time++; // 更新仿真时间
        if(top_out) {
            top->clk ^= 1; 
            top->eval(); 
            top->inst = pmem_read(top->pc);
            top->eval(); 
            m_trace->dump(sim_time);
            sim_time++; // 更新仿真时间
            break;
        }
    }
    m_trace->close();
    delete top;
    exit(EXIT_SUCCESS);
}
