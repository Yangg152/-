// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+1,"clk", false,-1);
    tracep->declBit(c+2,"rst", false,-1);
    tracep->declBus(c+3,"out1", false,-1, 6,0);
    tracep->declBus(c+4,"out2", false,-1, 6,0);
    tracep->declBus(c+5,"out3", false,-1, 6,0);
    tracep->declBus(c+6,"out4", false,-1, 6,0);
    tracep->declBus(c+7,"out5", false,-1, 6,0);
    tracep->declBus(c+8,"out6", false,-1, 6,0);
    tracep->declBus(c+9,"prbs_output", false,-1, 7,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+1,"clk", false,-1);
    tracep->declBit(c+2,"rst", false,-1);
    tracep->declBus(c+3,"out1", false,-1, 6,0);
    tracep->declBus(c+4,"out2", false,-1, 6,0);
    tracep->declBus(c+5,"out3", false,-1, 6,0);
    tracep->declBus(c+6,"out4", false,-1, 6,0);
    tracep->declBus(c+7,"out5", false,-1, 6,0);
    tracep->declBus(c+8,"out6", false,-1, 6,0);
    tracep->declBus(c+9,"prbs_output", false,-1, 7,0);
    tracep->declBus(c+10,"cout1", false,-1, 3,0);
    tracep->declBus(c+11,"cout2", false,-1, 3,0);
    tracep->declBus(c+12,"cout3", false,-1, 3,0);
    tracep->declBus(c+13,"cout4", false,-1, 3,0);
    tracep->declBus(c+14,"cout5", false,-1, 3,0);
    tracep->declBus(c+15,"cout6", false,-1, 3,0);
    tracep->declBit(c+16,"clk1hz", false,-1);
    tracep->declBus(c+17,"keyout", false,-1, 7,0);
    tracep->popNamePrefix(1);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->clk));
    bufp->fullBit(oldp+2,(vlSelf->rst));
    bufp->fullCData(oldp+3,(vlSelf->out1),7);
    bufp->fullCData(oldp+4,(vlSelf->out2),7);
    bufp->fullCData(oldp+5,(vlSelf->out3),7);
    bufp->fullCData(oldp+6,(vlSelf->out4),7);
    bufp->fullCData(oldp+7,(vlSelf->out5),7);
    bufp->fullCData(oldp+8,(vlSelf->out6),7);
    bufp->fullCData(oldp+9,(vlSelf->prbs_output),8);
    bufp->fullCData(oldp+10,(vlSelf->top__DOT__cout1),4);
    bufp->fullCData(oldp+11,(vlSelf->top__DOT__cout2),4);
    bufp->fullCData(oldp+12,(vlSelf->top__DOT__cout3),4);
    bufp->fullCData(oldp+13,(vlSelf->top__DOT__cout4),4);
    bufp->fullCData(oldp+14,(vlSelf->top__DOT__cout5),4);
    bufp->fullCData(oldp+15,(vlSelf->top__DOT__cout6),4);
    bufp->fullBit(oldp+16,(vlSelf->top__DOT__clk1hz));
    bufp->fullCData(oldp+17,(vlSelf->top__DOT__keyout),8);
}
