// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
    vlSelf->__Vtrigrprev__TOP__clk = vlSelf->clk;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    // Body
    vlSelf->top__DOT__regfile__DOT__rf[0U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[1U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[2U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[3U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[4U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[5U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[6U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[7U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[8U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[9U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0xaU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0xbU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0xcU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0xdU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0xeU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0xfU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x10U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x11U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x12U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x13U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x14U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x15U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x16U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x17U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x18U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x19U] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x1aU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x1bU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x1cU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x1dU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x1eU] = 0U;
    vlSelf->top__DOT__regfile__DOT__rf[0x1fU] = 0U;
    vlSelf->top__DOT__regfile__DOT__unnamedblk1__DOT__i = 0x20U;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        Vtop___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("/home/yang/Desktop/workspace/ysys-study/YPC/vsrc/top.v", 1, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            Vtop___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->top__DOT__pc_n = ((0U == vlSelf->pc) ? 0x80000000U
                               : ((IData)(4U) + vlSelf->pc));
    if (vlSelf->rst) {
        vlSelf->top__DOT__rd = 0U;
        vlSelf->top__DOT__rs2 = 0U;
        vlSelf->top__DOT__opcode7 = 0U;
        vlSelf->top__DOT__opcode3 = 0U;
        vlSelf->top__DOT__rs1 = 0U;
        vlSelf->top__DOT__imm = 0U;
        vlSelf->top__DOT__wen = 0U;
    } else {
        vlSelf->top__DOT__rd = (0x1fU & (vlSelf->inst 
                                         >> 7U));
        vlSelf->top__DOT__rs2 = (0x1fU & (vlSelf->inst 
                                          >> 0x14U));
        vlSelf->top__DOT__opcode7 = (0x7fU & vlSelf->inst);
        vlSelf->top__DOT__opcode3 = (7U & (vlSelf->inst 
                                           >> 0xcU));
        vlSelf->top__DOT__rs1 = (0x1fU & (vlSelf->inst 
                                          >> 0xfU));
        vlSelf->top__DOT__imm = (((- (IData)((vlSelf->inst 
                                              >> 0x1fU))) 
                                  << 0xbU) | (0x7ffU 
                                              & (vlSelf->inst 
                                                 >> 0x14U)));
        vlSelf->top__DOT__wen = ((0U != vlSelf->top__DOT__imm)
                                  ? 1U : 0U);
    }
    vlSelf->top__DOT__result = (vlSelf->top__DOT__imm 
                                + ((0U == (IData)(vlSelf->top__DOT__rs1))
                                    ? 0U : vlSelf->top__DOT__regfile__DOT__rf
                                   [vlSelf->top__DOT__rs1]));
}

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VicoTriggered.at(0U)) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->rst = 0;
    vlSelf->inst = 0;
    vlSelf->out = 0;
    vlSelf->pc = 0;
    vlSelf->top__DOT__pc_n = 0;
    vlSelf->top__DOT__imm = 0;
    vlSelf->top__DOT__rd = 0;
    vlSelf->top__DOT__rs1 = 0;
    vlSelf->top__DOT__rs2 = 0;
    vlSelf->top__DOT__opcode7 = 0;
    vlSelf->top__DOT__opcode3 = 0;
    vlSelf->top__DOT__wdata = 0;
    vlSelf->top__DOT__wen = 0;
    vlSelf->top__DOT__rs1_value = 0;
    vlSelf->top__DOT__rs2_value = 0;
    vlSelf->top__DOT__rd_value = 0;
    vlSelf->top__DOT__result = 0;
    vlSelf->top__DOT__ifu__DOT__inst = 0;
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->top__DOT__regfile__DOT__rf[__Vi0] = 0;
    }
    vlSelf->top__DOT__regfile__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->__Vtrigrprev__TOP__clk = 0;
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
