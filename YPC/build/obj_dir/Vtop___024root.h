// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;

class Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_OUT8(out1,6,0);
    VL_OUT8(out2,6,0);
    VL_OUT8(out3,6,0);
    VL_OUT8(out4,6,0);
    VL_OUT8(out5,6,0);
    VL_OUT8(out6,6,0);
    VL_OUT8(prbs_output,7,0);
    CData/*3:0*/ top__DOT__cout1;
    CData/*3:0*/ top__DOT__cout2;
    CData/*3:0*/ top__DOT__cout3;
    CData/*3:0*/ top__DOT__cout4;
    CData/*3:0*/ top__DOT__cout5;
    CData/*3:0*/ top__DOT__cout6;
    CData/*0:0*/ top__DOT__clk1hz;
    CData/*7:0*/ top__DOT__keyout;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
