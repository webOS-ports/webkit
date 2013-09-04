/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
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

#include "config.h"
#include "StackIterator.h"

#include "Arguments.h"
#include "CallFrameInlines.h"
#include "Executable.h"
#include "Interpreter.h"
#include "Operations.h"
#include <wtf/DataLog.h>

namespace JSC {

StackIterator::StackIterator(CallFrame* startFrame, StackIterator::FrameFilter filter)
    : m_startFrame(startFrame)
    , m_filter(filter)
{
    resetIterator();
}

size_t StackIterator::numberOfFrames()
{
    int savedFrameIndex = m_frame.index();
    resetIterator();
    while (m_frame.callFrame())
        gotoNextFrameWithFilter();
    size_t numberOfFrames = m_frame.index();

    resetIterator();
    gotoFrameAtIndex(savedFrameIndex);

    return numberOfFrames;
}

void StackIterator::gotoFrameAtIndex(size_t index)
{
    while (m_frame.callFrame() && (m_frame.index() != index))
        gotoNextFrameWithFilter();
}

void StackIterator::gotoNextFrame()
{
#if ENABLE(DFG_JIT)
    if (m_frame.isInlinedFrame()) {
        InlineCallFrame* inlineCallFrame = m_frame.inlineCallFrame();
        CodeOrigin* callerCodeOrigin = &inlineCallFrame->caller;
        readInlinedFrame(m_frame.callFrame(), callerCodeOrigin);

    } else
#endif // ENABLE(DFG_JIT)
        readFrame(m_frame.callerFrame());
}

void StackIterator::gotoNextFrameWithFilter()
{
    ASSERT(m_frame.callFrame());
    while (m_frame.callFrame()) {
        gotoNextFrame();
        if (!m_frame.callFrame() || !m_filter || !m_filter(&m_frame))
            break;
    }
    m_frame.m_index++;
}

void StackIterator::resetIterator()
{
    m_frame.m_index = 0;
    readFrame(m_startFrame);
}

void StackIterator::readFrame(CallFrame* callFrame)
{
    ASSERT(!callFrame->hasHostCallFrameFlag());
    if (!callFrame) {
        m_frame.setToEnd();
        return;
    }

#if !ENABLE(DFG_JIT)
    readNonInlinedFrame(callFrame);

#else // !ENABLE(DFG_JIT)
    // If the frame doesn't have a code block, then it's not a DFG frame.
    // Hence, we're not at an inlined frame.
    CodeBlock* codeBlock = callFrame->codeBlock();
    if (!codeBlock) {
        readNonInlinedFrame(callFrame);
        return;
    }

    // If the code block does not have any code origins, then there's no
    // inlining. Hence, we're not at an inlined frame.
    if (!codeBlock->hasCodeOrigins()) {
        readNonInlinedFrame(callFrame);
        return;
    }

    unsigned index = callFrame->locationAsCodeOriginIndex();
    ASSERT(codeBlock->canGetCodeOrigin(index));
    if (!codeBlock->canGetCodeOrigin(index)) {
        // See assertion above. In release builds, we try to protect ourselves
        // from crashing even though stack walking will be goofed up.
        m_frame.setToEnd();
        return;
    }

    CodeOrigin codeOrigin = codeBlock->codeOrigin(index);
    if (!codeOrigin.inlineCallFrame) {
        readNonInlinedFrame(callFrame, &codeOrigin);
        return;
    }

    readInlinedFrame(callFrame, &codeOrigin);
#endif // !ENABLE(DFG_JIT)
}

void StackIterator::readNonInlinedFrame(CallFrame* callFrame, CodeOrigin* codeOrigin)
{
    m_frame.m_callFrame = callFrame;
    m_frame.m_argumentCountIncludingThis = callFrame->argumentCountIncludingThis();
    m_frame.m_callerFrame = callFrame->callerFrame()->removeHostCallFrameFlag();
    m_frame.m_callee = callFrame->callee();
    m_frame.m_scope = callFrame->scope();
    m_frame.m_codeBlock = callFrame->codeBlock();
    m_frame.m_bytecodeOffset = !m_frame.codeBlock() ? 0
        : codeOrigin ? codeOrigin->bytecodeIndex
        : callFrame->locationAsBytecodeOffset();
#if ENABLE(DFG_JIT)
    m_frame.m_inlineCallFrame = 0;
#endif
}

#if ENABLE(DFG_JIT)
static unsigned inlinedFrameOffset(CodeOrigin* codeOrigin)
{
    InlineCallFrame* inlineCallFrame = codeOrigin->inlineCallFrame;
    unsigned frameOffset = inlineCallFrame ? inlineCallFrame->stackOffset : 0;
    return frameOffset;
}

void StackIterator::readInlinedFrame(CallFrame* callFrame, CodeOrigin* codeOrigin)
{
    ASSERT(codeOrigin);
    ASSERT(!callFrame->hasHostCallFrameFlag());

    unsigned frameOffset = inlinedFrameOffset(codeOrigin);
    bool isInlined = !!frameOffset;
    if (isInlined) {
        InlineCallFrame* inlineCallFrame = codeOrigin->inlineCallFrame;

        m_frame.m_callFrame = callFrame;
        m_frame.m_inlineCallFrame = inlineCallFrame;
        m_frame.m_argumentCountIncludingThis = inlineCallFrame->arguments.size();
        m_frame.m_codeBlock = inlineCallFrame->baselineCodeBlock();
        m_frame.m_bytecodeOffset = codeOrigin->bytecodeIndex;

        JSFunction* callee = inlineCallFrame->callee.get();
        if (callee) {
            m_frame.m_scope = callee->scope();
            m_frame.m_callee = callee;
        } else {
            CallFrame* inlinedFrame = callFrame + frameOffset;
            m_frame.m_scope = inlinedFrame->scope();
            m_frame.m_callee = inlinedFrame->callee();
        }
        ASSERT(m_frame.scope());
        ASSERT(m_frame.callee());

        // The callerFrame just needs to be non-null to indicate that we
        // haven't reached the last frame yet. Setting it to the root
        // frame (i.e. the callFrame that this inlined frame is called from)
        // would work just fine.
        m_frame.m_callerFrame = callFrame;
        return;
    }

    readNonInlinedFrame(callFrame, codeOrigin);
}
#endif // ENABLE(DFG_JIT)

StackIterator::Frame::CodeType StackIterator::Frame::codeType() const
{
    if (!isJSFrame())
        return StackIterator::Frame::Native;

    switch (codeBlock()->codeType()) {
    case EvalCode:
        return StackIterator::Frame::Eval;
    case FunctionCode:
        return StackIterator::Frame::Function;
    case GlobalCode:
        return StackIterator::Frame::Global;
    }
    RELEASE_ASSERT_NOT_REACHED();
    return StackIterator::Frame::Global;
}

String StackIterator::Frame::functionName()
{
    String traceLine;
    JSObject* callee = this->callee();

    switch (codeType()) {
    case StackIterator::Frame::Eval:
        traceLine = "eval code";
        break;
    case StackIterator::Frame::Native:
        if (callee)
            traceLine = getCalculatedDisplayName(callFrame(), callee).impl();
        break;
    case StackIterator::Frame::Function:
        traceLine = getCalculatedDisplayName(callFrame(), callee).impl();
        break;
    case StackIterator::Frame::Global:
        traceLine = "global code";
        break;
    }
    return traceLine.isNull() ? emptyString() : traceLine;
}

String StackIterator::Frame::sourceURL()
{
    String traceLine;

    switch (codeType()) {
    case StackIterator::Frame::Eval:
    case StackIterator::Frame::Function:
    case StackIterator::Frame::Global: {
        String sourceURL = codeBlock()->ownerExecutable()->sourceURL();
        if (!sourceURL.isEmpty())
            traceLine = sourceURL.impl();
        break;
    }
    case StackIterator::Frame::Native:
        traceLine = "[native code]";
        break;
    }
    return traceLine.isNull() ? emptyString() : traceLine;
}

String StackIterator::Frame::toString()
{
    StringBuilder traceBuild;
    String functionName = this->functionName();
    String sourceURL = this->sourceURL();
    traceBuild.append(functionName);
    if (!sourceURL.isEmpty()) {
        if (!functionName.isEmpty())
            traceBuild.append('@');
        traceBuild.append(sourceURL);
        if (isJSFrame()) {
            unsigned line = 0;
            unsigned column = 0;
            computeLineAndColumn(line, column);
            traceBuild.append(':');
            traceBuild.appendNumber(line);
            traceBuild.append(':');
            traceBuild.appendNumber(column);
        }
    }
    return traceBuild.toString().impl();
}

Arguments* StackIterator::Frame::arguments()
{
    ASSERT(m_callFrame);
    CallFrame* physicalFrame = m_callFrame;
    VM& vm = physicalFrame->vm();
    Arguments* arguments;
#if ENABLE(DFG_JIT)
    if (isInlinedFrame()) {
        ASSERT(m_inlineCallFrame);
        arguments = Arguments::create(vm, physicalFrame, m_inlineCallFrame);
        arguments->tearOff(physicalFrame, m_inlineCallFrame);
    } else 
#endif
    {
        arguments = Arguments::create(vm, physicalFrame);
        arguments->tearOff(physicalFrame);
    }
    return arguments;
}

void StackIterator::Frame::computeLineAndColumn(unsigned& line, unsigned& column)
{
    CodeBlock* codeBlock = this->codeBlock();
    if (!codeBlock) {
        line = 0;
        column = 0;
        return;
    }

    int divot = 0;
    int unusedStartOffset = 0;
    int unusedEndOffset = 0;
    unsigned divotLine = 0;
    unsigned divotColumn = 0;
    retrieveExpressionInfo(divot, unusedStartOffset, unusedEndOffset, divotLine, divotColumn);

    line = divotLine + codeBlock->ownerExecutable()->lineNo();
    column = divotColumn + (divotLine ? 1 : codeBlock->firstLineColumnOffset());
}

void StackIterator::Frame::retrieveExpressionInfo(int& divot, int& startOffset, int& endOffset, unsigned& line, unsigned& column)
{
    CodeBlock* codeBlock = this->codeBlock();
    codeBlock->unlinkedCodeBlock()->expressionRangeForBytecodeOffset(bytecodeOffset(), divot, startOffset, endOffset, line, column);
    divot += codeBlock->sourceOffset();
}

void StackIterator::Frame::setToEnd()
{
    m_callFrame = 0;
#if ENABLE(DFG_JIT)
    m_inlineCallFrame = 0;
#endif
}

#ifndef NDEBUG

static const char* jitTypeName(JITCode::JITType jitType)
{
    switch (jitType) {
    case JITCode::None: return "None";
    case JITCode::HostCallThunk: return "HostCallThunk";
    case JITCode::InterpreterThunk: return "InterpreterThunk";
    case JITCode::BaselineJIT: return "BaselineJIT";
    case JITCode::DFGJIT: return "DFGJIT";
    case JITCode::FTLJIT: return "FTLJIT";
    }
    return "<unknown>";
}

static void printIndents(int levels)
{
    while (levels--)
        dataLogFString("   ");
}

static void printif(int indentLevels, const char* format, ...)
{
    va_list argList;
    va_start(argList, format);

    if (indentLevels)
        printIndents(indentLevels);

#if COMPILER(CLANG) || (COMPILER(GCC) && GCC_VERSION_AT_LEAST(4, 6, 0))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#pragma GCC diagnostic ignored "-Wmissing-format-attribute"
#endif

    WTF::dataLogFV(format, argList);

#if COMPILER(CLANG) || (COMPILER(GCC) && GCC_VERSION_AT_LEAST(4, 6, 0))
#pragma GCC diagnostic pop
#endif

    va_end(argList);
}

void StackIterator::Frame::print(int indentLevel)
{
    int i = indentLevel;

    if (!this->callFrame()) {
        printif(i, "frame 0x0\n");
        return;
    }

    CodeBlock* codeBlock = this->codeBlock();
    printif(i, "frame %p {\n", this->callFrame());

    CallFrame* callFrame = m_callFrame;
    CallFrame* callerFrame = this->callerFrame();
    void* returnPC = callFrame->hasReturnPC() ? callFrame->returnPC().value() : 0;

    printif(i, "   name '%s'\n", functionName().utf8().data());
    printif(i, "   sourceURL '%s'\n", sourceURL().utf8().data());
    printif(i, "   hostFlag %d\n", callerFrame->hasHostCallFrameFlag());

#if ENABLE(DFG_JIT)
    printif(i, "   isInlinedFrame %d\n", isInlinedFrame());
    if (isInlinedFrame())
        printif(i, "   InlineCallFrame %p\n", m_inlineCallFrame);
#endif

    printif(i, "   callee %p\n", callee());
    printif(i, "   returnPC %p\n", returnPC);
    printif(i, "   callerFrame %p\n", callerFrame->removeHostCallFrameFlag());
    unsigned locationRawBits = callFrame->locationAsRawBits();
    printif(i, "   rawLocationBits %u 0x%x\n", locationRawBits, locationRawBits);
    printif(i, "   codeBlock %p\n", codeBlock);
    if (codeBlock) {
        JITCode::JITType jitType = codeBlock->jitType();
        if (callFrame->hasLocationAsBytecodeOffset()) {
            unsigned bytecodeOffset = callFrame->locationAsBytecodeOffset();
            printif(i, "      bytecodeOffset %u %p / %zu\n", bytecodeOffset, reinterpret_cast<void*>(bytecodeOffset), codeBlock->instructions().size());
#if ENABLE(DFG_JIT)
        } else {
            unsigned codeOriginIndex = callFrame->locationAsCodeOriginIndex();
            printif(i, "      codeOriginIdex %u %p / %zu\n", codeOriginIndex, reinterpret_cast<void*>(codeOriginIndex), codeBlock->codeOrigins().size());
#endif
        }
        unsigned line = 0;
        unsigned column = 0;
        computeLineAndColumn(line, column);
        printif(i, "      line %d\n", line);
        printif(i, "      column %d\n", column);
        printif(i, "      jitType %d <%s> isOptimizingJIT %d\n", jitType, jitTypeName(jitType), JITCode::isOptimizingJIT(jitType));
#if ENABLE(DFG_JIT)
        printif(i, "      hasCodeOrigins %d\n", codeBlock->hasCodeOrigins());
        if (codeBlock->hasCodeOrigins()) {
            JITCode* jitCode = codeBlock->jitCode().get();
            printif(i, "         jitCode %p start %p end %p\n", jitCode, jitCode->start(), jitCode->end());
        }
#endif
    }
    printif(i, "}\n");
}

#endif // NDEBUG

} // namespace JSC

#ifndef NDEBUG
using JSC::StackIterator;

// For debugging use
void debugPrintCallFrame(JSC::CallFrame*);
void debugPrintStack(JSC::CallFrame* topCallFrame);

void debugPrintCallFrame(JSC::CallFrame* callFrame)
{
    if (!callFrame)
        return;
    StackIterator iter = callFrame->begin();
    iter->print(2);
}

class DebugPrintStackFunctor {
public:
    StackIterator::Status operator()(StackIterator& iter)
    {
        iter->print(2);
        return StackIterator::Continue;
    }
};

void debugPrintStack(JSC::CallFrame* topCallFrame)
{
    if (!topCallFrame)
        return;
    DebugPrintStackFunctor functor;
    StackIterator iter = topCallFrame->begin();
    iter.iterate(functor);
}
#endif // !NDEBUG
