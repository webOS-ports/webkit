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

#include "JSTestSerializedScriptValueInterface.h"

#include "JSMessagePort.h"
#include "MessagePort.h"
#include "SerializedScriptValue.h"
#include "TestSerializedScriptValueInterface.h"
#include <runtime/JSArray.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

/* Hash table */

static const HashTableValue JSTestSerializedScriptValueInterfaceTableValues[] =
{
    { "value", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestSerializedScriptValueInterfaceValue), (intptr_t)setJSTestSerializedScriptValueInterfaceValue, NoIntrinsic },
    { "readonlyValue", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestSerializedScriptValueInterfaceReadonlyValue), (intptr_t)0, NoIntrinsic },
    { "cachedValue", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestSerializedScriptValueInterfaceCachedValue), (intptr_t)setJSTestSerializedScriptValueInterfaceCachedValue, NoIntrinsic },
    { "ports", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestSerializedScriptValueInterfacePorts), (intptr_t)0, NoIntrinsic },
    { "cachedReadonlyValue", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestSerializedScriptValueInterfaceCachedReadonlyValue), (intptr_t)0, NoIntrinsic },
    { "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestSerializedScriptValueInterfaceConstructor), (intptr_t)0, NoIntrinsic },
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestSerializedScriptValueInterfaceTable = { 17, 15, JSTestSerializedScriptValueInterfaceTableValues, 0 };
/* Hash table for constructor */

static const HashTableValue JSTestSerializedScriptValueInterfaceConstructorTableValues[] =
{
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestSerializedScriptValueInterfaceConstructorTable = { 1, 0, JSTestSerializedScriptValueInterfaceConstructorTableValues, 0 };
const ClassInfo JSTestSerializedScriptValueInterfaceConstructor::s_info = { "TestSerializedScriptValueInterfaceConstructor", &Base::s_info, &JSTestSerializedScriptValueInterfaceConstructorTable, 0, CREATE_METHOD_TABLE(JSTestSerializedScriptValueInterfaceConstructor) };

JSTestSerializedScriptValueInterfaceConstructor::JSTestSerializedScriptValueInterfaceConstructor(Structure* structure, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(structure, globalObject)
{
}

void JSTestSerializedScriptValueInterfaceConstructor::finishCreation(ExecState* exec, JSDOMGlobalObject* globalObject)
{
    Base::finishCreation(exec->vm());
    ASSERT(inherits(info()));
    putDirect(exec->vm(), exec->propertyNames().prototype, JSTestSerializedScriptValueInterfacePrototype::self(exec, globalObject), DontDelete | ReadOnly);
    putDirect(exec->vm(), exec->propertyNames().length, jsNumber(0), ReadOnly | DontDelete | DontEnum);
}

bool JSTestSerializedScriptValueInterfaceConstructor::getOwnPropertySlot(JSObject* object, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSTestSerializedScriptValueInterfaceConstructor, JSDOMWrapper>(exec, &JSTestSerializedScriptValueInterfaceConstructorTable, jsCast<JSTestSerializedScriptValueInterfaceConstructor*>(object), propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSTestSerializedScriptValueInterfacePrototypeTableValues[] =
{
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestSerializedScriptValueInterfacePrototypeTable = { 1, 0, JSTestSerializedScriptValueInterfacePrototypeTableValues, 0 };
const ClassInfo JSTestSerializedScriptValueInterfacePrototype::s_info = { "TestSerializedScriptValueInterfacePrototype", &Base::s_info, &JSTestSerializedScriptValueInterfacePrototypeTable, 0, CREATE_METHOD_TABLE(JSTestSerializedScriptValueInterfacePrototype) };

JSObject* JSTestSerializedScriptValueInterfacePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTestSerializedScriptValueInterface>(exec, globalObject);
}

const ClassInfo JSTestSerializedScriptValueInterface::s_info = { "TestSerializedScriptValueInterface", &Base::s_info, &JSTestSerializedScriptValueInterfaceTable, 0 , CREATE_METHOD_TABLE(JSTestSerializedScriptValueInterface) };

JSTestSerializedScriptValueInterface::JSTestSerializedScriptValueInterface(Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestSerializedScriptValueInterface> impl)
    : JSDOMWrapper(structure, globalObject)
    , m_impl(impl.leakRef())
{
}

void JSTestSerializedScriptValueInterface::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(info()));
}

JSObject* JSTestSerializedScriptValueInterface::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return JSTestSerializedScriptValueInterfacePrototype::create(exec->vm(), globalObject, JSTestSerializedScriptValueInterfacePrototype::createStructure(globalObject->vm(), globalObject, globalObject->objectPrototype()));
}

void JSTestSerializedScriptValueInterface::destroy(JSC::JSCell* cell)
{
    JSTestSerializedScriptValueInterface* thisObject = static_cast<JSTestSerializedScriptValueInterface*>(cell);
    thisObject->JSTestSerializedScriptValueInterface::~JSTestSerializedScriptValueInterface();
}

JSTestSerializedScriptValueInterface::~JSTestSerializedScriptValueInterface()
{
    releaseImplIfNotNull();
}

bool JSTestSerializedScriptValueInterface::getOwnPropertySlot(JSObject* object, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    JSTestSerializedScriptValueInterface* thisObject = jsCast<JSTestSerializedScriptValueInterface*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    return getStaticValueSlot<JSTestSerializedScriptValueInterface, Base>(exec, &JSTestSerializedScriptValueInterfaceTable, thisObject, propertyName, slot);
}

JSValue jsTestSerializedScriptValueInterfaceValue(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestSerializedScriptValueInterface* castedThis = jsCast<JSTestSerializedScriptValueInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestSerializedScriptValueInterface* impl = static_cast<TestSerializedScriptValueInterface*>(castedThis->impl());
    JSValue result = impl->value() ? impl->value()->deserialize(exec, castedThis->globalObject(), 0) : jsNull();
    return result;
}


JSValue jsTestSerializedScriptValueInterfaceReadonlyValue(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestSerializedScriptValueInterface* castedThis = jsCast<JSTestSerializedScriptValueInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestSerializedScriptValueInterface* impl = static_cast<TestSerializedScriptValueInterface*>(castedThis->impl());
    JSValue result = impl->readonlyValue() ? impl->readonlyValue()->deserialize(exec, castedThis->globalObject(), 0) : jsNull();
    return result;
}


JSValue jsTestSerializedScriptValueInterfaceCachedValue(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestSerializedScriptValueInterface* castedThis = jsCast<JSTestSerializedScriptValueInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    if (JSValue cachedValue = castedThis->m_cachedValue.get())
        return cachedValue;
    TestSerializedScriptValueInterface* impl = static_cast<TestSerializedScriptValueInterface*>(castedThis->impl());
    JSValue result = impl->cachedValue() ? impl->cachedValue()->deserialize(exec, castedThis->globalObject(), 0) : jsNull();
    castedThis->m_cachedValue.set(exec->vm(), castedThis, result);
    return result;
}


JSValue jsTestSerializedScriptValueInterfacePorts(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestSerializedScriptValueInterface* castedThis = jsCast<JSTestSerializedScriptValueInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestSerializedScriptValueInterface* impl = static_cast<TestSerializedScriptValueInterface*>(castedThis->impl());
    JSValue result = jsArray(exec, castedThis->globalObject(), impl->ports());
    return result;
}


JSValue jsTestSerializedScriptValueInterfaceCachedReadonlyValue(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestSerializedScriptValueInterface* castedThis = jsCast<JSTestSerializedScriptValueInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    if (JSValue cachedValue = castedThis->m_cachedReadonlyValue.get())
        return cachedValue;
    TestSerializedScriptValueInterface* impl = static_cast<TestSerializedScriptValueInterface*>(castedThis->impl());
    JSValue result = impl->cachedReadonlyValue() ? impl->cachedReadonlyValue()->deserialize(exec, castedThis->globalObject(), 0) : jsNull();
    castedThis->m_cachedReadonlyValue.set(exec->vm(), castedThis, result);
    return result;
}


JSValue jsTestSerializedScriptValueInterfaceConstructor(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestSerializedScriptValueInterface* domObject = jsCast<JSTestSerializedScriptValueInterface*>(asObject(slotBase));
    return JSTestSerializedScriptValueInterface::getConstructor(exec, domObject->globalObject());
}

void JSTestSerializedScriptValueInterface::put(JSCell* cell, ExecState* exec, PropertyName propertyName, JSValue value, PutPropertySlot& slot)
{
    JSTestSerializedScriptValueInterface* thisObject = jsCast<JSTestSerializedScriptValueInterface*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    lookupPut<JSTestSerializedScriptValueInterface, Base>(exec, propertyName, value, &JSTestSerializedScriptValueInterfaceTable, thisObject, slot);
}

void setJSTestSerializedScriptValueInterfaceValue(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    JSTestSerializedScriptValueInterface* castedThis = jsCast<JSTestSerializedScriptValueInterface*>(thisObject);
    TestSerializedScriptValueInterface* impl = static_cast<TestSerializedScriptValueInterface*>(castedThis->impl());
    RefPtr<SerializedScriptValue> nativeValue(SerializedScriptValue::create(exec, value, 0, 0));
    if (exec->hadException())
        return;
    impl->setValue(nativeValue);
}


void setJSTestSerializedScriptValueInterfaceCachedValue(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    JSTestSerializedScriptValueInterface* castedThis = jsCast<JSTestSerializedScriptValueInterface*>(thisObject);
    TestSerializedScriptValueInterface* impl = static_cast<TestSerializedScriptValueInterface*>(castedThis->impl());
    RefPtr<SerializedScriptValue> nativeValue(SerializedScriptValue::create(exec, value, 0, 0));
    if (exec->hadException())
        return;
    impl->setCachedValue(nativeValue);
}


JSValue JSTestSerializedScriptValueInterface::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestSerializedScriptValueInterfaceConstructor>(exec, jsCast<JSDOMGlobalObject*>(globalObject));
}

void JSTestSerializedScriptValueInterface::visitChildren(JSCell* cell, SlotVisitor& visitor)
{
    JSTestSerializedScriptValueInterface* thisObject = jsCast<JSTestSerializedScriptValueInterface*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    COMPILE_ASSERT(StructureFlags & OverridesVisitChildren, OverridesVisitChildrenWithoutSettingFlag);
    ASSERT(thisObject->structure()->typeInfo().overridesVisitChildren());
    Base::visitChildren(thisObject, visitor);
    visitor.append(&thisObject->m_cachedValue);
    visitor.append(&thisObject->m_cachedReadonlyValue);
}

static inline bool isObservable(JSTestSerializedScriptValueInterface* jsTestSerializedScriptValueInterface)
{
    if (jsTestSerializedScriptValueInterface->hasCustomProperties())
        return true;
    return false;
}

bool JSTestSerializedScriptValueInterfaceOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    JSTestSerializedScriptValueInterface* jsTestSerializedScriptValueInterface = jsCast<JSTestSerializedScriptValueInterface*>(handle.get().asCell());
    if (!isObservable(jsTestSerializedScriptValueInterface))
        return false;
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestSerializedScriptValueInterfaceOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    JSTestSerializedScriptValueInterface* jsTestSerializedScriptValueInterface = jsCast<JSTestSerializedScriptValueInterface*>(handle.get().asCell());
    DOMWrapperWorld* world = static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestSerializedScriptValueInterface->impl(), jsTestSerializedScriptValueInterface);
    jsTestSerializedScriptValueInterface->releaseImpl();
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestSerializedScriptValueInterface@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore34TestSerializedScriptValueInterfaceE[]; }
#endif
#endif
JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TestSerializedScriptValueInterface* impl)
{
    if (!impl)
        return jsNull();
    if (JSValue result = getExistingWrapper<JSTestSerializedScriptValueInterface>(exec, impl))
        return result;

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = *(reinterpret_cast<void**>(impl));
#if PLATFORM(WIN)
    void* expectedVTablePointer = reinterpret_cast<void*>(__identifier("??_7TestSerializedScriptValueInterface@WebCore@@6B@"));
#else
    void* expectedVTablePointer = &_ZTVN7WebCore34TestSerializedScriptValueInterfaceE[2];
#if COMPILER(CLANG)
    // If this fails TestSerializedScriptValueInterface does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    COMPILE_ASSERT(__is_polymorphic(TestSerializedScriptValueInterface), TestSerializedScriptValueInterface_is_not_polymorphic);
#endif
#endif
    // If you hit this assertion you either have a use after free bug, or
    // TestSerializedScriptValueInterface has subclasses. If TestSerializedScriptValueInterface has subclasses that get passed
    // to toJS() we currently require TestSerializedScriptValueInterface you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    ReportMemoryCost<TestSerializedScriptValueInterface>::reportMemoryCost(exec, impl);
    return createNewWrapper<JSTestSerializedScriptValueInterface>(exec, globalObject, impl);
}

TestSerializedScriptValueInterface* toTestSerializedScriptValueInterface(JSC::JSValue value)
{
    return value.inherits(JSTestSerializedScriptValueInterface::info()) ? jsCast<JSTestSerializedScriptValueInterface*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(Condition1) || ENABLE(Condition2)
