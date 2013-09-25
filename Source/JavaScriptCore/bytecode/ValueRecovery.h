/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef ValueRecovery_h
#define ValueRecovery_h

#include "DataFormat.h"
#include "GPRInfo.h"
#include "FPRInfo.h"
#include "JSCJSValue.h"
#include "MacroAssembler.h"
#include "VirtualRegister.h"
#include <stdio.h>
#include <wtf/Platform.h>

namespace JSC {

struct DumpContext;

// Describes how to recover a given bytecode virtual register at a given
// code point.
enum ValueRecoveryTechnique {
    // It's already in the stack at the right location.
    AlreadyInJSStack,
    // It's already in the stack but unboxed.
    AlreadyInJSStackAsUnboxedInt32,
    AlreadyInJSStackAsUnboxedInt52,
    AlreadyInJSStackAsUnboxedCell,
    AlreadyInJSStackAsUnboxedBoolean,
    AlreadyInJSStackAsUnboxedDouble,
    // It's in a register.
    InGPR,
    UnboxedInt32InGPR,
    UnboxedInt52InGPR,
    UnboxedStrictInt52InGPR,
    UnboxedBooleanInGPR,
#if USE(JSVALUE32_64)
    InPair,
#endif
    InFPR,
    UInt32InGPR,
    // It's in the stack, but at a different location.
    DisplacedInJSStack,
    // It's in the stack, at a different location, and it's unboxed.
    Int32DisplacedInJSStack,
    Int52DisplacedInJSStack,
    StrictInt52DisplacedInJSStack,
    DoubleDisplacedInJSStack,
    CellDisplacedInJSStack,
    BooleanDisplacedInJSStack,
    // It's an Arguments object.
    ArgumentsThatWereNotCreated,
    // It's a constant.
    Constant,
    // Don't know how to recover it.
    DontKnow
};

class ValueRecovery {
public:
    ValueRecovery()
        : m_technique(DontKnow)
    {
    }
    
    bool isSet() const { return m_technique != DontKnow; }
    bool operator!() const { return !isSet(); }
    
    static ValueRecovery alreadyInJSStack()
    {
        ValueRecovery result;
        result.m_technique = AlreadyInJSStack;
        return result;
    }
    
    static ValueRecovery alreadyInJSStackAsUnboxedInt32()
    {
        ValueRecovery result;
        result.m_technique = AlreadyInJSStackAsUnboxedInt32;
        return result;
    }
    
    static ValueRecovery alreadyInJSStackAsUnboxedInt52()
    {
        ValueRecovery result;
        result.m_technique = AlreadyInJSStackAsUnboxedInt52;
        return result;
    }
    
    static ValueRecovery alreadyInJSStackAsUnboxedCell()
    {
        ValueRecovery result;
        result.m_technique = AlreadyInJSStackAsUnboxedCell;
        return result;
    }
    
    static ValueRecovery alreadyInJSStackAsUnboxedBoolean()
    {
        ValueRecovery result;
        result.m_technique = AlreadyInJSStackAsUnboxedBoolean;
        return result;
    }
    
    static ValueRecovery alreadyInJSStackAsUnboxedDouble()
    {
        ValueRecovery result;
        result.m_technique = AlreadyInJSStackAsUnboxedDouble;
        return result;
    }
    
    static ValueRecovery inGPR(MacroAssembler::RegisterID gpr, DataFormat dataFormat)
    {
        ASSERT(dataFormat != DataFormatNone);
#if USE(JSVALUE32_64)
        ASSERT(dataFormat == DataFormatInt32 || dataFormat == DataFormatCell || dataFormat == DataFormatBoolean);
#endif
        ValueRecovery result;
        if (dataFormat == DataFormatInt32)
            result.m_technique = UnboxedInt32InGPR;
        else if (dataFormat == DataFormatInt52)
            result.m_technique = UnboxedInt52InGPR;
        else if (dataFormat == DataFormatStrictInt52)
            result.m_technique = UnboxedStrictInt52InGPR;
        else if (dataFormat == DataFormatBoolean)
            result.m_technique = UnboxedBooleanInGPR;
        else
            result.m_technique = InGPR;
        result.m_source.gpr = gpr;
        return result;
    }
    
    static ValueRecovery uint32InGPR(MacroAssembler::RegisterID gpr)
    {
        ValueRecovery result;
        result.m_technique = UInt32InGPR;
        result.m_source.gpr = gpr;
        return result;
    }
    
#if USE(JSVALUE32_64)
    static ValueRecovery inPair(MacroAssembler::RegisterID tagGPR, MacroAssembler::RegisterID payloadGPR)
    {
        ValueRecovery result;
        result.m_technique = InPair;
        result.m_source.pair.tagGPR = tagGPR;
        result.m_source.pair.payloadGPR = payloadGPR;
        return result;
    }
#endif

    static ValueRecovery inFPR(MacroAssembler::FPRegisterID fpr)
    {
        ValueRecovery result;
        result.m_technique = InFPR;
        result.m_source.fpr = fpr;
        return result;
    }
    
    static ValueRecovery displacedInJSStack(VirtualRegister virtualReg, DataFormat dataFormat)
    {
        ValueRecovery result;
        switch (dataFormat) {
        case DataFormatInt32:
            result.m_technique = Int32DisplacedInJSStack;
            break;
            
        case DataFormatInt52:
            result.m_technique = Int52DisplacedInJSStack;
            break;
            
        case DataFormatStrictInt52:
            result.m_technique = StrictInt52DisplacedInJSStack;
            break;
            
        case DataFormatDouble:
            result.m_technique = DoubleDisplacedInJSStack;
            break;

        case DataFormatCell:
            result.m_technique = CellDisplacedInJSStack;
            break;
            
        case DataFormatBoolean:
            result.m_technique = BooleanDisplacedInJSStack;
            break;
            
        default:
            ASSERT(dataFormat != DataFormatNone && dataFormat != DataFormatStorage);
            result.m_technique = DisplacedInJSStack;
            break;
        }
        result.m_source.virtualReg = virtualReg;
        return result;
    }
    
    static ValueRecovery constant(JSValue value)
    {
        ValueRecovery result;
        result.m_technique = Constant;
        result.m_source.constant = JSValue::encode(value);
        return result;
    }
    
    static ValueRecovery argumentsThatWereNotCreated()
    {
        ValueRecovery result;
        result.m_technique = ArgumentsThatWereNotCreated;
        return result;
    }
    
    ValueRecoveryTechnique technique() const { return m_technique; }
    
    bool isConstant() const { return m_technique == Constant; }
    
    bool isInRegisters() const
    {
        switch (m_technique) {
        case InGPR:
        case UnboxedInt32InGPR:
        case UnboxedBooleanInGPR:
#if USE(JSVALUE32_64)
        case InPair:
#endif
        case InFPR:
            return true;
        default:
            return false;
        }
    }
    
    bool isAlreadyInJSStack() const
    {
        switch (technique()) {
        case AlreadyInJSStack:
        case AlreadyInJSStackAsUnboxedInt32:
        case AlreadyInJSStackAsUnboxedInt52:
        case AlreadyInJSStackAsUnboxedCell:
        case AlreadyInJSStackAsUnboxedBoolean:
        case AlreadyInJSStackAsUnboxedDouble:
            return true;
        default:
            return false;
        }
    }
    
    MacroAssembler::RegisterID gpr() const
    {
        ASSERT(m_technique == InGPR || m_technique == UnboxedInt32InGPR || m_technique == UnboxedBooleanInGPR || m_technique == UInt32InGPR || m_technique == UnboxedInt52InGPR || m_technique == UnboxedStrictInt52InGPR);
        return m_source.gpr;
    }
    
#if USE(JSVALUE32_64)
    MacroAssembler::RegisterID tagGPR() const
    {
        ASSERT(m_technique == InPair);
        return m_source.pair.tagGPR;
    }
    
    MacroAssembler::RegisterID payloadGPR() const
    {
        ASSERT(m_technique == InPair);
        return m_source.pair.payloadGPR;
    }
#endif
    
    MacroAssembler::FPRegisterID fpr() const
    {
        ASSERT(m_technique == InFPR);
        return m_source.fpr;
    }
    
    VirtualRegister virtualRegister() const
    {
        ASSERT(m_technique == DisplacedInJSStack || m_technique == Int32DisplacedInJSStack || m_technique == DoubleDisplacedInJSStack || m_technique == CellDisplacedInJSStack || m_technique == BooleanDisplacedInJSStack || m_technique == Int52DisplacedInJSStack || m_technique == StrictInt52DisplacedInJSStack);
        return m_source.virtualReg;
    }
    
    JSValue constant() const
    {
        ASSERT(m_technique == Constant);
        return JSValue::decode(m_source.constant);
    }
    
    void dumpInContext(PrintStream& out, DumpContext* context) const
    {
        switch (technique()) {
        case AlreadyInJSStack:
            out.printf("-");
            return;
        case AlreadyInJSStackAsUnboxedInt32:
            out.printf("(int32)");
            return;
        case AlreadyInJSStackAsUnboxedInt52:
            out.printf("(int52)");
            return;
        case AlreadyInJSStackAsUnboxedCell:
            out.printf("(cell)");
            return;
        case AlreadyInJSStackAsUnboxedBoolean:
            out.printf("(bool)");
            return;
        case AlreadyInJSStackAsUnboxedDouble:
            out.printf("(double)");
            return;
        case InGPR:
            out.print(gpr());
            return;
        case UnboxedInt32InGPR:
            out.print("int32(", gpr(), ")");
            return;
        case UnboxedInt52InGPR:
            out.print("int53(", gpr(), ")");
            return;
        case UnboxedStrictInt52InGPR:
            out.print("strictInt52(", gpr(), ")");
            return;
        case UnboxedBooleanInGPR:
            out.print("bool(", gpr(), ")");
            return;
        case UInt32InGPR:
            out.print("uint32(", gpr(), ")");
            return;
        case InFPR:
            out.print(fpr());
            return;
#if USE(JSVALUE32_64)
        case InPair:
            out.print("pair(", tagGPR(), ", ", payloadGPR(), ")");
            return;
#endif
        case DisplacedInJSStack:
            out.printf("*%d", virtualRegister());
            return;
        case Int32DisplacedInJSStack:
            out.printf("*int32(%d)", virtualRegister());
            return;
        case Int52DisplacedInJSStack:
            out.printf("*int52(%d)", virtualRegister());
            return;
        case StrictInt52DisplacedInJSStack:
            out.printf("*strictInt52(%d)", virtualRegister());
            return;
        case DoubleDisplacedInJSStack:
            out.printf("*double(%d)", virtualRegister());
            return;
        case CellDisplacedInJSStack:
            out.printf("*cell(%d)", virtualRegister());
            return;
        case BooleanDisplacedInJSStack:
            out.printf("*bool(%d)", virtualRegister());
            return;
        case ArgumentsThatWereNotCreated:
            out.printf("arguments");
            return;
        case Constant:
            out.print("[", inContext(constant(), context), "]");
            return;
        case DontKnow:
            out.printf("!");
            return;
        }
        RELEASE_ASSERT_NOT_REACHED();
    }
    
    void dump(PrintStream& out) const
    {
        dumpInContext(out, 0);
    }
    
private:
    ValueRecoveryTechnique m_technique;
    union {
        MacroAssembler::RegisterID gpr;
        MacroAssembler::FPRegisterID fpr;
#if USE(JSVALUE32_64)
        struct {
            MacroAssembler::RegisterID tagGPR;
            MacroAssembler::RegisterID payloadGPR;
        } pair;
#endif
        VirtualRegister virtualReg;
        EncodedJSValue constant;
    } m_source;
};

} // namespace JSC

#endif // ValueRecovery_h
