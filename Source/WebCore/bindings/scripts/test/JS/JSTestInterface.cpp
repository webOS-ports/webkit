/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#if ENABLE(Condition1) || ENABLE(Condition2)

#include "JSTestInterface.h"

#include "ExceptionCode.h"
#include "JSDOMBinding.h"
#include "JSTestObj.h"
#include "TestInterface.h"
#include "TestObj.h"
#include "TestSupplemental.h"
#include <runtime/Error.h>
#include <wtf/GetPtr.h>

#if ENABLE(Condition11) || ENABLE(Condition12) || ENABLE(Condition22) || ENABLE(Condition23)
#include "JSNode.h"
#include "KURL.h"
#include <runtime/JSString.h>
#endif

#if ENABLE(Condition11) || ENABLE(Condition12) || ENABLE(Condition22) || ENABLE(Condition23)
#include "Node.h"
#endif

using namespace JSC;

namespace WebCore {

/* Hash table */

static const HashTableValue JSTestInterfaceTableValues[] =
{
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsStr1", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceImplementsStr1), (intptr_t)0 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsStr2", DontDelete, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceImplementsStr2), (intptr_t)setJSTestInterfaceImplementsStr2 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsStr3", DontDelete, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceImplementsStr3), (intptr_t)setJSTestInterfaceImplementsStr3 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsNode", DontDelete, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceImplementsNode), (intptr_t)setJSTestInterfaceImplementsNode },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalStr1", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSupplementalStr1), (intptr_t)0 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalStr2", DontDelete, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSupplementalStr2), (intptr_t)setJSTestInterfaceSupplementalStr2 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalStr3", DontDelete, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSupplementalStr3), (intptr_t)setJSTestInterfaceSupplementalStr3 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalNode", DontDelete, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSupplementalNode), (intptr_t)setJSTestInterfaceSupplementalNode },
#endif
    { "constructor", DontEnum | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceConstructor), (intptr_t)0 },
    { 0, 0, NoIntrinsic, 0, 0 }
};

static const HashTable JSTestInterfaceTable = { 33, 31, JSTestInterfaceTableValues, 0 };
/* Hash table for constructor */

static const HashTableValue JSTestInterfaceConstructorTableValues[] =
{
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "IMPLEMENTSCONSTANT1", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceIMPLEMENTSCONSTANT1), (intptr_t)0 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "IMPLEMENTSCONSTANT2", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceIMPLEMENTSCONSTANT2), (intptr_t)0 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "SUPPLEMENTALCONSTANT1", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSUPPLEMENTALCONSTANT1), (intptr_t)0 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "SUPPLEMENTALCONSTANT2", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSUPPLEMENTALCONSTANT2), (intptr_t)0 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsStaticReadOnlyAttr", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceConstructorImplementsStaticReadOnlyAttr), (intptr_t)0 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsStaticAttr", DontDelete, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceConstructorImplementsStaticAttr), (intptr_t)setJSTestInterfaceConstructorImplementsStaticAttr },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalStaticReadOnlyAttr", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceConstructorSupplementalStaticReadOnlyAttr), (intptr_t)0 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalStaticAttr", DontDelete, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceConstructorSupplementalStaticAttr), (intptr_t)setJSTestInterfaceConstructorSupplementalStaticAttr },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsMethod4", DontDelete | JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestInterfaceConstructorFunctionImplementsMethod4), (intptr_t)0 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalMethod4", DontDelete | JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestInterfaceConstructorFunctionSupplementalMethod4), (intptr_t)0 },
#endif
    { 0, 0, NoIntrinsic, 0, 0 }
};

static const HashTable JSTestInterfaceConstructorTable = { 11, 7, JSTestInterfaceConstructorTableValues, 0 };

#if ENABLE(Condition22) || ENABLE(Condition23)
COMPILE_ASSERT(1 == TestInterface::IMPLEMENTSCONSTANT1, TestInterfaceEnumIMPLEMENTSCONSTANT1IsWrongUseDoNotCheckConstants);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
COMPILE_ASSERT(2 == TestInterface::CONST_IMPL, TestInterfaceEnumCONST_IMPLIsWrongUseDoNotCheckConstants);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
COMPILE_ASSERT(1 == TestSupplemental::SUPPLEMENTALCONSTANT1, TestInterfaceEnumSUPPLEMENTALCONSTANT1IsWrongUseDoNotCheckConstants);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
COMPILE_ASSERT(2 == TestSupplemental::CONST_IMPL, TestInterfaceEnumCONST_IMPLIsWrongUseDoNotCheckConstants);
#endif

EncodedJSValue JSC_HOST_CALL JSTestInterfaceConstructor::constructJSTestInterface(ExecState* exec)
{
    JSTestInterfaceConstructor* castedThis = jsCast<JSTestInterfaceConstructor*>(exec->callee());
    if (exec->argumentCount() < 1)
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    ExceptionCode ec = 0;
    const String& str1(exec->argument(0).isEmpty() ? String() : exec->argument(0).toString(exec)->value(exec));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    const String& str2(exec->argument(1).isEmpty() ? String() : exec->argument(1).toString(exec)->value(exec));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    ScriptExecutionContext* context = castedThis->scriptExecutionContext();
    if (!context)
        return throwVMError(exec, createReferenceError(exec, "TestInterface constructor associated document is unavailable"));
    RefPtr<TestInterface> object = TestInterface::create(context, str1, str2, ec);
    if (ec) {
        setDOMException(exec, ec);
        return JSValue::encode(JSValue());
    }
    return JSValue::encode(asObject(toJS(exec, castedThis->globalObject(), object.get())));
}

const ClassInfo JSTestInterfaceConstructor::s_info = { "TestInterfaceConstructor", &Base::s_info, &JSTestInterfaceConstructorTable, 0, CREATE_METHOD_TABLE(JSTestInterfaceConstructor) };

JSTestInterfaceConstructor::JSTestInterfaceConstructor(Structure* structure, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(structure, globalObject)
{
}

void JSTestInterfaceConstructor::finishCreation(ExecState* exec, JSDOMGlobalObject* globalObject)
{
    Base::finishCreation(exec->vm());
    ASSERT(inherits(info()));
    putDirect(exec->vm(), exec->propertyNames().prototype, JSTestInterfacePrototype::self(exec, globalObject), DontDelete | ReadOnly);
    putDirect(exec->vm(), exec->propertyNames().length, jsNumber(1), ReadOnly | DontDelete | DontEnum);
}

bool JSTestInterfaceConstructor::getOwnPropertySlot(JSObject* object, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSTestInterfaceConstructor, JSDOMWrapper>(exec, JSTestInterfaceConstructorTable, jsCast<JSTestInterfaceConstructor*>(object), propertyName, slot);
}

#if ENABLE(TEST_INTERFACE)
ConstructType JSTestInterfaceConstructor::getConstructData(JSCell*, ConstructData& constructData)
{
    constructData.native.function = constructJSTestInterface;
    return ConstructTypeHost;
}
#endif // ENABLE(TEST_INTERFACE)

/* Hash table for prototype */

static const HashTableValue JSTestInterfacePrototypeTableValues[] =
{
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "IMPLEMENTSCONSTANT1", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceIMPLEMENTSCONSTANT1), (intptr_t)0 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "IMPLEMENTSCONSTANT2", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceIMPLEMENTSCONSTANT2), (intptr_t)0 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "SUPPLEMENTALCONSTANT1", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSUPPLEMENTALCONSTANT1), (intptr_t)0 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "SUPPLEMENTALCONSTANT2", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSUPPLEMENTALCONSTANT2), (intptr_t)0 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsMethod1", DontDelete | JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestInterfacePrototypeFunctionImplementsMethod1), (intptr_t)0 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsMethod2", DontDelete | JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestInterfacePrototypeFunctionImplementsMethod2), (intptr_t)2 },
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    { "implementsMethod3", DontDelete | JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestInterfacePrototypeFunctionImplementsMethod3), (intptr_t)0 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalMethod1", DontDelete | JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestInterfacePrototypeFunctionSupplementalMethod1), (intptr_t)0 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalMethod2", DontDelete | JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestInterfacePrototypeFunctionSupplementalMethod2), (intptr_t)2 },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalMethod3", DontDelete | JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestInterfacePrototypeFunctionSupplementalMethod3), (intptr_t)0 },
#endif
    { 0, 0, NoIntrinsic, 0, 0 }
};

static const HashTable JSTestInterfacePrototypeTable = { 34, 31, JSTestInterfacePrototypeTableValues, 0 };
const ClassInfo JSTestInterfacePrototype::s_info = { "TestInterfacePrototype", &Base::s_info, &JSTestInterfacePrototypeTable, 0, CREATE_METHOD_TABLE(JSTestInterfacePrototype) };

JSObject* JSTestInterfacePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTestInterface>(exec, globalObject);
}

bool JSTestInterfacePrototype::getOwnPropertySlot(JSObject* object, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    JSTestInterfacePrototype* thisObject = jsCast<JSTestInterfacePrototype*>(object);
    return getStaticPropertySlot<JSTestInterfacePrototype, JSObject>(exec, JSTestInterfacePrototypeTable, thisObject, propertyName, slot);
}

const ClassInfo JSTestInterface::s_info = { "TestInterface", &Base::s_info, &JSTestInterfaceTable, 0 , CREATE_METHOD_TABLE(JSTestInterface) };

JSTestInterface::JSTestInterface(Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestInterface> impl)
    : JSDOMWrapper(structure, globalObject)
    , m_impl(impl.leakRef())
{
}

void JSTestInterface::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(info()));
}

JSObject* JSTestInterface::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return JSTestInterfacePrototype::create(exec->vm(), globalObject, JSTestInterfacePrototype::createStructure(globalObject->vm(), globalObject, globalObject->objectPrototype()));
}

void JSTestInterface::destroy(JSC::JSCell* cell)
{
    JSTestInterface* thisObject = static_cast<JSTestInterface*>(cell);
    thisObject->JSTestInterface::~JSTestInterface();
}

JSTestInterface::~JSTestInterface()
{
    releaseImplIfNotNull();
}

bool JSTestInterface::getOwnPropertySlot(JSObject* object, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    JSTestInterface* thisObject = jsCast<JSTestInterface*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    return getStaticValueSlot<JSTestInterface, Base>(exec, JSTestInterfaceTable, thisObject, propertyName, slot);
}

#if ENABLE(Condition22) || ENABLE(Condition23)
JSValue jsTestInterfaceConstructorImplementsStaticReadOnlyAttr(ExecState* exec, JSValue slotBase, PropertyName)
{
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(exec);
    JSValue result = jsNumber(TestInterface::implementsStaticReadOnlyAttr());
    return result;
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
JSValue jsTestInterfaceConstructorImplementsStaticAttr(ExecState* exec, JSValue slotBase, PropertyName)
{
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(exec);
    JSValue result = jsStringWithCache(exec, TestInterface::implementsStaticAttr());
    return result;
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
JSValue jsTestInterfaceImplementsStr1(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    JSValue result = jsStringWithCache(exec, impl->implementsStr1());
    return result;
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
JSValue jsTestInterfaceImplementsStr2(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    JSValue result = jsStringWithCache(exec, impl->implementsStr2());
    return result;
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
JSValue jsTestInterfaceImplementsStr3(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(slotBase));
    return castedThis->implementsStr3(exec);
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
JSValue jsTestInterfaceImplementsNode(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(impl->implementsNode()));
    return result;
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceConstructorSupplementalStaticReadOnlyAttr(ExecState* exec, JSValue slotBase, PropertyName)
{
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(exec);
    JSValue result = jsNumber(TestSupplemental::supplementalStaticReadOnlyAttr());
    return result;
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceConstructorSupplementalStaticAttr(ExecState* exec, JSValue slotBase, PropertyName)
{
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(exec);
    JSValue result = jsStringWithCache(exec, TestSupplemental::supplementalStaticAttr());
    return result;
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSupplementalStr1(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    JSValue result = jsStringWithCache(exec, TestSupplemental::supplementalStr1(impl));
    return result;
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSupplementalStr2(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    JSValue result = jsStringWithCache(exec, TestSupplemental::supplementalStr2(impl));
    return result;
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSupplementalStr3(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(slotBase));
    return castedThis->supplementalStr3(exec);
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSupplementalNode(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(TestSupplemental::supplementalNode(impl)));
    return result;
}

#endif

JSValue jsTestInterfaceConstructor(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestInterface* domObject = jsCast<JSTestInterface*>(asObject(slotBase));
    return JSTestInterface::getConstructor(exec, domObject->globalObject());
}

void JSTestInterface::put(JSCell* cell, ExecState* exec, PropertyName propertyName, JSValue value, PutPropertySlot& slot)
{
    JSTestInterface* thisObject = jsCast<JSTestInterface*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    if (thisObject->putDelegate(exec, propertyName, value, slot))
        return;
    lookupPut<JSTestInterface, Base>(exec, propertyName, value, JSTestInterfaceTable, thisObject, slot);
}

void JSTestInterface::putByIndex(JSCell* cell, ExecState* exec, unsigned index, JSValue value, bool shouldThrow)
{
    JSTestInterface* thisObject = jsCast<JSTestInterface*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    PropertyName propertyName = Identifier::from(exec, index);
    PutPropertySlot slot(shouldThrow);
    if (thisObject->putDelegate(exec, propertyName, value, slot))
        return;
    Base::putByIndex(cell, exec, index, value, shouldThrow);
}

#if ENABLE(Condition22) || ENABLE(Condition23)
void setJSTestInterfaceConstructorImplementsStaticAttr(ExecState* exec, JSObject*, JSValue value)
{
    UNUSED_PARAM(exec);
    const String& nativeValue(value.isEmpty() ? String() : value.toString(exec)->value(exec));
    if (exec->hadException())
        return;
    TestInterface::setImplementsStaticAttr(nativeValue);
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
void setJSTestInterfaceImplementsStr2(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(thisObject);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    const String& nativeValue(value.isEmpty() ? String() : value.toString(exec)->value(exec));
    if (exec->hadException())
        return;
    impl->setImplementsStr2(nativeValue);
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
void setJSTestInterfaceImplementsStr3(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    jsCast<JSTestInterface*>(thisObject)->setImplementsStr3(exec, value);
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
void setJSTestInterfaceImplementsNode(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(thisObject);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    Node* nativeValue(toNode(value));
    if (exec->hadException())
        return;
    impl->setImplementsNode(nativeValue);
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
void setJSTestInterfaceConstructorSupplementalStaticAttr(ExecState* exec, JSObject*, JSValue value)
{
    UNUSED_PARAM(exec);
    const String& nativeValue(value.isEmpty() ? String() : value.toString(exec)->value(exec));
    if (exec->hadException())
        return;
    TestSupplemental::setSupplementalStaticAttr(nativeValue);
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
void setJSTestInterfaceSupplementalStr2(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(thisObject);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    const String& nativeValue(value.isEmpty() ? String() : value.toString(exec)->value(exec));
    if (exec->hadException())
        return;
    TestSupplemental::setSupplementalStr2(impl, nativeValue);
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
void setJSTestInterfaceSupplementalStr3(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    jsCast<JSTestInterface*>(thisObject)->setSupplementalStr3(exec, value);
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
void setJSTestInterfaceSupplementalNode(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(thisObject);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    Node* nativeValue(toNode(value));
    if (exec->hadException())
        return;
    TestSupplemental::setSupplementalNode(impl, nativeValue);
}

#endif

JSValue JSTestInterface::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestInterfaceConstructor>(exec, jsCast<JSDOMGlobalObject*>(globalObject));
}

#if ENABLE(Condition22) || ENABLE(Condition23)
EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionImplementsMethod1(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(JSTestInterface::info()))
        return throwVMTypeError(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestInterface::info());
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    impl->implementsMethod1();
    return JSValue::encode(jsUndefined());
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionImplementsMethod2(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(JSTestInterface::info()))
        return throwVMTypeError(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestInterface::info());
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    if (exec->argumentCount() < 2)
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    ExceptionCode ec = 0;
    ScriptExecutionContext* scriptContext = jsCast<JSDOMGlobalObject*>(exec->lexicalGlobalObject())->scriptExecutionContext();
    if (!scriptContext)
        return JSValue::encode(jsUndefined());
    const String& strArg(exec->argument(0).isEmpty() ? String() : exec->argument(0).toString(exec)->value(exec));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    TestObj* objArg(toTestObj(exec->argument(1)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());

    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(impl->implementsMethod2(scriptContext, strArg, objArg, ec)));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionImplementsMethod3(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(JSTestInterface::info()))
        return throwVMTypeError(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestInterface::info());
    return JSValue::encode(castedThis->implementsMethod3(exec));
}

#endif

#if ENABLE(Condition22) || ENABLE(Condition23)
EncodedJSValue JSC_HOST_CALL jsTestInterfaceConstructorFunctionImplementsMethod4(ExecState* exec)
{
    TestInterface::implementsMethod4();
    return JSValue::encode(jsUndefined());
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionSupplementalMethod1(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(JSTestInterface::info()))
        return throwVMTypeError(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestInterface::info());
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    TestSupplemental::supplementalMethod1(impl);
    return JSValue::encode(jsUndefined());
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionSupplementalMethod2(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(JSTestInterface::info()))
        return throwVMTypeError(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestInterface::info());
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    if (exec->argumentCount() < 2)
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    ExceptionCode ec = 0;
    ScriptExecutionContext* scriptContext = jsCast<JSDOMGlobalObject*>(exec->lexicalGlobalObject())->scriptExecutionContext();
    if (!scriptContext)
        return JSValue::encode(jsUndefined());
    const String& strArg(exec->argument(0).isEmpty() ? String() : exec->argument(0).toString(exec)->value(exec));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    TestObj* objArg(toTestObj(exec->argument(1)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());

    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(TestSupplemental::supplementalMethod2(impl, scriptContext, strArg, objArg, ec)));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionSupplementalMethod3(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(JSTestInterface::info()))
        return throwVMTypeError(exec);
    JSTestInterface* castedThis = jsCast<JSTestInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestInterface::info());
    return JSValue::encode(castedThis->supplementalMethod3(exec));
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
EncodedJSValue JSC_HOST_CALL jsTestInterfaceConstructorFunctionSupplementalMethod4(ExecState* exec)
{
    TestSupplemental::supplementalMethod4();
    return JSValue::encode(jsUndefined());
}

#endif

// Constant getters

#if ENABLE(Condition22) || ENABLE(Condition23)
JSValue jsTestInterfaceIMPLEMENTSCONSTANT1(ExecState* exec, JSValue, PropertyName)
{
    UNUSED_PARAM(exec);
    return jsNumber(static_cast<int>(1));
}

#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSValue jsTestInterfaceIMPLEMENTSCONSTANT2(ExecState* exec, JSValue, PropertyName)
{
    UNUSED_PARAM(exec);
    return jsNumber(static_cast<int>(2));
}

#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSUPPLEMENTALCONSTANT1(ExecState* exec, JSValue, PropertyName)
{
    UNUSED_PARAM(exec);
    return jsNumber(static_cast<int>(1));
}

#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSUPPLEMENTALCONSTANT2(ExecState* exec, JSValue, PropertyName)
{
    UNUSED_PARAM(exec);
    return jsNumber(static_cast<int>(2));
}

#endif
static inline bool isObservable(JSTestInterface* jsTestInterface)
{
    if (jsTestInterface->hasCustomProperties())
        return true;
    return false;
}

bool JSTestInterfaceOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    JSTestInterface* jsTestInterface = jsCast<JSTestInterface*>(handle.get().asCell());
    if (jsTestInterface->impl()->hasPendingActivity())
        return true;
    if (!isObservable(jsTestInterface))
        return false;
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestInterfaceOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    JSTestInterface* jsTestInterface = jsCast<JSTestInterface*>(handle.get().asCell());
    DOMWrapperWorld* world = static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestInterface->impl(), jsTestInterface);
    jsTestInterface->releaseImpl();
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TestInterface* impl)
{
    if (!impl)
        return jsNull();
    if (JSValue result = getExistingWrapper<JSTestInterface>(exec, impl))
        return result;
#if COMPILER(CLANG)
    // If you hit this failure the interface definition has the ImplementationLacksVTable
    // attribute. You should remove that attribute. If the class has subclasses
    // that may be passed through this toJS() function you should use the SkipVTableValidation
    // attribute to TestInterface.
    COMPILE_ASSERT(!__is_polymorphic(TestInterface), TestInterface_is_polymorphic_but_idl_claims_not_to_be);
#endif
    ReportMemoryCost<TestInterface>::reportMemoryCost(exec, impl);
    return createNewWrapper<JSTestInterface>(exec, globalObject, impl);
}

TestInterface* toTestInterface(JSC::JSValue value)
{
    return value.inherits(JSTestInterface::info()) ? jsCast<JSTestInterface*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(Condition1) || ENABLE(Condition2)
