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

#ifndef JSTestTypedefs_h
#define JSTestTypedefs_h

#include "JSDOMBinding.h"
#include "TestTypedefs.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class JSTestTypedefs : public JSDOMWrapper {
public:
    typedef JSDOMWrapper Base;
    static JSTestTypedefs* create(JSC::Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestTypedefs> impl)
    {
        JSTestTypedefs* ptr = new (NotNull, JSC::allocateCell<JSTestTypedefs>(globalObject->vm().heap)) JSTestTypedefs(structure, globalObject, impl);
        ptr->finishCreation(globalObject->vm());
        return ptr;
    }

    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    static bool getOwnPropertySlot(JSC::JSObject*, JSC::ExecState*, JSC::PropertyName, JSC::PropertySlot&);
    static void put(JSC::JSCell*, JSC::ExecState*, JSC::PropertyName, JSC::JSValue, JSC::PutPropertySlot&);
    static void destroy(JSC::JSCell*);
    ~JSTestTypedefs();
    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

    static JSC::JSValue getConstructor(JSC::ExecState*, JSC::JSGlobalObject*);
    TestTypedefs* impl() const { return m_impl; }
    void releaseImpl() { m_impl->deref(); m_impl = 0; }

    void releaseImplIfNotNull()
    {
        if (m_impl) {
            m_impl->deref();
            m_impl = 0;
        }
    }

private:
    TestTypedefs* m_impl;
protected:
    JSTestTypedefs(JSC::Structure*, JSDOMGlobalObject*, PassRefPtr<TestTypedefs>);
    void finishCreation(JSC::VM&);
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | JSC::InterceptsGetOwnPropertySlotByIndexEvenWhenLengthIsNotZero | Base::StructureFlags;
};

class JSTestTypedefsOwner : public JSC::WeakHandleOwner {
public:
    virtual bool isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown>, void* context, JSC::SlotVisitor&);
    virtual void finalize(JSC::Handle<JSC::Unknown>, void* context);
};

inline JSC::WeakHandleOwner* wrapperOwner(DOMWrapperWorld*, TestTypedefs*)
{
    DEFINE_STATIC_LOCAL(JSTestTypedefsOwner, jsTestTypedefsOwner, ());
    return &jsTestTypedefsOwner;
}

inline void* wrapperContext(DOMWrapperWorld* world, TestTypedefs*)
{
    return world;
}

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, TestTypedefs*);
TestTypedefs* toTestTypedefs(JSC::JSValue);

class JSTestTypedefsPrototype : public JSC::JSNonFinalObject {
public:
    typedef JSC::JSNonFinalObject Base;
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    static JSTestTypedefsPrototype* create(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestTypedefsPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestTypedefsPrototype>(vm.heap)) JSTestTypedefsPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static bool getOwnPropertySlot(JSC::JSObject*, JSC::ExecState*, JSC::PropertyName, JSC::PropertySlot&);
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestTypedefsPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure) : JSC::JSNonFinalObject(vm, structure) { }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

class JSTestTypedefsConstructor : public DOMConstructorObject {
private:
    JSTestTypedefsConstructor(JSC::Structure*, JSDOMGlobalObject*);
    void finishCreation(JSC::ExecState*, JSDOMGlobalObject*);

public:
    typedef DOMConstructorObject Base;
    static JSTestTypedefsConstructor* create(JSC::ExecState* exec, JSC::Structure* structure, JSDOMGlobalObject* globalObject)
    {
        JSTestTypedefsConstructor* ptr = new (NotNull, JSC::allocateCell<JSTestTypedefsConstructor>(*exec->heap())) JSTestTypedefsConstructor(structure, globalObject);
        ptr->finishCreation(exec, globalObject);
        return ptr;
    }

    static bool getOwnPropertySlot(JSC::JSObject*, JSC::ExecState*, JSC::PropertyName, JSC::PropertySlot&);
    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | JSC::ImplementsHasInstance | DOMConstructorObject::StructureFlags;
    static JSC::EncodedJSValue JSC_HOST_CALL constructJSTestTypedefs(JSC::ExecState*);
    static JSC::ConstructType getConstructData(JSC::JSCell*, JSC::ConstructData&);
};

// Functions

JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionFunc(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionSetShadow(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionMethodWithSequenceArg(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionNullableArrayArg(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionFuncWithClamp(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionImmutablePointFunction(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionStringArrayFunction(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionStringArrayFunction2(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionCallWithSequenceThatRequiresInclude(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionMethodWithException(JSC::ExecState*);
// Attributes

JSC::JSValue jsTestTypedefsUnsignedLongLongAttr(JSC::ExecState*, JSC::JSValue, JSC::PropertyName);
void setJSTestTypedefsUnsignedLongLongAttr(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsTestTypedefsImmutableSerializedScriptValue(JSC::ExecState*, JSC::JSValue, JSC::PropertyName);
void setJSTestTypedefsImmutableSerializedScriptValue(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsTestTypedefsConstructorTestSubObj(JSC::ExecState*, JSC::JSValue, JSC::PropertyName);
JSC::JSValue jsTestTypedefsAttrWithGetterException(JSC::ExecState*, JSC::JSValue, JSC::PropertyName);
void setJSTestTypedefsAttrWithGetterException(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsTestTypedefsAttrWithSetterException(JSC::ExecState*, JSC::JSValue, JSC::PropertyName);
void setJSTestTypedefsAttrWithSetterException(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsTestTypedefsStringAttrWithGetterException(JSC::ExecState*, JSC::JSValue, JSC::PropertyName);
void setJSTestTypedefsStringAttrWithGetterException(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsTestTypedefsStringAttrWithSetterException(JSC::ExecState*, JSC::JSValue, JSC::PropertyName);
void setJSTestTypedefsStringAttrWithSetterException(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsTestTypedefsConstructor(JSC::ExecState*, JSC::JSValue, JSC::PropertyName);

} // namespace WebCore

#endif
