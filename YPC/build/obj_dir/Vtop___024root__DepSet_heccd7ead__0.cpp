// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ __Vdly__top__DOT__pc_internal;
    __Vdly__top__DOT__pc_internal = 0;
    IData/*31:0*/ __Vdly__top__DOT__exu__DOT__rs1_value;
    __Vdly__top__DOT__exu__DOT__rs1_value = 0;
    CData/*4:0*/ __Vdlyvdim0__top__DOT__exu__DOT__regfile__DOT__rf__v0;
    __Vdlyvdim0__top__DOT__exu__DOT__regfile__DOT__rf__v0 = 0;
    IData/*31:0*/ __Vdlyvval__top__DOT__exu__DOT__regfile__DOT__rf__v0;
    __Vdlyvval__top__DOT__exu__DOT__regfile__DOT__rf__v0 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__exu__DOT__regfile__DOT__rf__v0;
    __Vdlyvset__top__DOT__exu__DOT__regfile__DOT__rf__v0 = 0;
    // Body
    __Vdly__top__DOT__pc_internal = vlSelf->top__DOT__pc_internal;
    __Vdly__top__DOT__exu__DOT__rs1_value = vlSelf->top__DOT__exu__DOT__rs1_value;
    __Vdlyvset__top__DOT__exu__DOT__regfile__DOT__rf__v0 = 0U;
    __Vdly__top__DOT__pc_internal = vlSelf->pc;
    __Vdly__top__DOT__exu__DOT__rs1_value = ((0U == (IData)(vlSelf->top__DOT__rs1))
                                              ? 0U : 
                                             vlSelf->top__DOT__exu__DOT__regfile__DOT__rf
                                             [vlSelf->top__DOT__rs1]);
    if (vlSelf->top__DOT__wen) {
        if ((0U != (IData)(vlSelf->top__DOT__rs1))) {
            __Vdlyvval__top__DOT__exu__DOT__regfile__DOT__rf__v0 
                = vlSelf->top__DOT__wdata;
            __Vdlyvset__top__DOT__exu__DOT__regfile__DOT__rf__v0 = 1U;
            __Vdlyvdim0__top__DOT__exu__DOT__regfile__DOT__rf__v0 
                = vlSelf->top__DOT__rs1;
        }
    }
    __Vdly__top__DOT__pc_internal = ((IData)(vlSelf->rst)
                                      ? 0x80000000U
                                      : ((IData)(4U) 
                                         + vlSelf->top__DOT__pc_internal));
    vlSelf->top__DOT__pc_internal = __Vdly__top__DOT__pc_internal;
    if (__Vdlyvset__top__DOT__exu__DOT__regfile__DOT__rf__v0) {
        vlSelf->top__DOT__exu__DOT__regfile__DOT__rf[__Vdlyvdim0__top__DOT__exu__DOT__regfile__DOT__rf__v0] 
            = __Vdlyvval__top__DOT__exu__DOT__regfile__DOT__rf__v0;
    }
    vlSelf->pc = vlSelf->top__DOT__pc_internal;
    vlSelf->top__DOT__wen = ((~ (IData)(vlSelf->rst)) 
                             & (0U == (IData)(vlSelf->top__DOT__opcode3)));
    if ((1U & (~ (IData)(vlSelf->rst)))) {
        __Vdly__top__DOT__exu__DOT__rs1_value = vlSelf->top__DOT__exu__DOT__rs1_value;
        if ((0U == (IData)(vlSelf->top__DOT__opcode3))) {
            vlSelf->top__DOT__wdata = (vlSelf->top__DOT__exu__DOT__rs1_value 
                                       + vlSelf->top__DOT__imm);
        }
    }
    if (vlSelf->rst) {
        vlSelf->top__DOT__opcode7 = 0U;
        vlSelf->top__DOT__rd = 0U;
        vlSelf->top__DOT__rs1 = 0U;
        vlSelf->top__DOT__imm = 0U;
        vlSelf->top__DOT__opcode3 = 0U;
    } else {
        vlSelf->top__DOT__opcode7 = (0x7fU & vlSelf->inst);
        vlSelf->top__DOT__rd = (0x1fU & (vlSelf->inst 
                                         >> 7U));
        vlSelf->top__DOT__rs1 = (0x1fU & (vlSelf->inst 
                                          >> 0xfU));
        vlSelf->top__DOT__imm = (((- (IData)((vlSelf->inst 
                                              >> 0x1fU))) 
                                  << 0xbU) | (0x7ffU 
                                              & (vlSelf->inst 
                                                 >> 0x14U)));
        vlSelf->top__DOT__opcode3 = (7U & (vlSelf->inst 
                                           >> 0xcU));
    }
    vlSelf->top__DOT__exu__DOT__rs1_value = __Vdly__top__DOT__exu__DOT__rs1_value;
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vtop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vtop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/yang/Desktop/workspace/ysys-study/YPC/vsrc/top.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vtop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/yang/Desktop/workspace/ysys-study/YPC/vsrc/top.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vtop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
