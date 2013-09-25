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

#ifndef JSTestNamedConstructor_h
#define JSTestNamedConstructor_h

#include "DOMConstructorWithDocument.h"
#include "JSDOMBinding.h"
#include "TestNamedConstructor.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class JSTestNamedConstructor : public JSDOMWrapper {
public:
    typedef JSDOMWrapper Base;
    static JSTestNamedConstructor* create(JSC::Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestNamedConstructor> impl)
    {
        JSTestNamedConstructor* ptr = new (NotNull, JSC::allocateCell<JSTestNamedConstructor>(globalObject->vm().heap)) JSTestNamedConstructor(structure, globalObject, impl);
        ptr->finishCreation(globalObject->vm());
        return ptr;
    }

    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    static bool getOwnPropertySlot(JSC::JSObject*, JSC::ExecState*, JSC::PropertyName, JSC::PropertySlot&);
    static void destroy(JSC::JSCell*);
    ~JSTestNamedConstructor();
    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

    static JSC::JSValue getConstructor(JSC::ExecState*, JSC::JSGlobalObject*);
    static JSC::JSValue getNamedConstructor(JSC::ExecState*, JSC::JSGlobalObject*);
    TestNamedConstructor* impl() const { return m_impl; }
    void releaseImpl() { m_impl->deref(); m_impl = 0; }

    void releaseImplIfNotNull()
    {
        if (m_impl) {
            m_impl->deref();
            m_impl = 0;
        }
    }

private:
    TestNamedConstructor* m_impl;
protected:
    JSTestNamedConstructor(JSC::Structure*, JSDOMGlobalObject*, PassRefPtr<TestNamedConstructor>);
    void finishCreation(JSC::VM&);
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | JSC::InterceptsGetOwnPropertySlotByIndexEvenWhenLengthIsNotZero | Base::StructureFlags;
};

class JSTestNamedConstructorOwner : public JSC::WeakHandleOwner {
public:
    virtual bool isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown>, void* context, JSC::SlotVisitor&);
    virtual void finalize(JSC::Handle<JSC::Unknown>, void* context);
};

inline JSC::WeakHandleOwner* wrapperOwner(DOMWrapperWorld*, TestNamedConstructor*)
{
    DEFINE_STATIC_LOCAL(JSTestNamedConstructorOwner, jsTestNamedConstructorOwner, ());
    return &jsTestNamedConstructorOwner;
}

inline void* wrapperContext(DOMWrapperWorld* world, TestNamedConstructor*)
{
    return world;
}

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, TestNamedConstructor*);
TestNamedConstructor* toTestNamedConstructor(JSC::JSValue);

class JSTestNamedConstructorPrototype : public JSC::JSNonFinalObject {
public:
    typedef JSC::JSNonFinalObject Base;
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    static JSTestNamedConstructorPrototype* create(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestNamedConstructorPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestNamedConstructorPrototype>(vm.heap)) JSTestNamedConstructorPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestNamedConstructorPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure) : JSC::JSNonFinalObject(vm, structure) { }
protected:
    static const unsigned StructureFlags = Base::StructureFlags;
};

class JSTestNamedConstructorConstructor : public DOMConstructorObject {
private:
    JSTestNamedConstructorConstructor(JSC::Structure*, JSDOMGlobalObject*);
    void finishCreation(JSC::ExecState*, JSDOMGlobalObject*);

public:
    typedef DOMConstructorObject Base;
    static JSTestNamedConstructorConstructor* create(JSC::ExecState* exec, JSC::Structure* structure, JSDOMGlobalObject* globalObject)
    {
        JSTestNamedConstructorConstructor* ptr = new (NotNull, JSC::allocateCell<JSTestNamedConstructorConstructor>(*exec->heap())) JSTestNamedConstructorConstructor(structure, globalObject);
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
};

class JSTestNamedConstructorNamedConstructor : public DOMConstructorWithDocument {
public:
    typedef DOMConstructorWithDocument Base;

    static JSTestNamedConstructorNamedConstructor* create(JSC::ExecState* exec, JSC::Structure* structure, JSDOMGlobalObject* globalObject)
    {
        JSTestNamedConstructorNamedConstructor* constructor = new (NotNull, JSC::allocateCell<JSTestNamedConstructorNamedConstructor>(*exec->heap())) JSTestNamedConstructorNamedConstructor(structure, globalObject);
        constructor->finishCreation(exec, globalObject);
        return constructor;
    }

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

    DECLARE_INFO;

private:
    JSTestNamedConstructorNamedConstructor(JSC::Structure*, JSDOMGlobalObject*);
    static JSC::EncodedJSValue JSC_HOST_CALL constructJSTestNamedConstructor(JSC::ExecState*);
    static JSC::ConstructType getConstructData(JSC::JSCell*, JSC::ConstructData&);
    void finishCreation(JSC::ExecState*, JSDOMGlobalObject*);
};

// Attributes

JSC::JSValue jsTestNamedConstructorConstructor(JSC::ExecState*, JSC::JSValue, JSC::PropertyName);

} // namespace WebCore

#endif
