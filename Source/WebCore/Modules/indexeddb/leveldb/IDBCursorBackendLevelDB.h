/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef IDBCursorBackendLevelDB_h
#define IDBCursorBackendLevelDB_h

#if ENABLE(INDEXED_DATABASE) && USE(LEVELDB)

#include "IDBBackingStoreLevelDB.h"
#include "IDBCursorBackendInterface.h"
#include "IDBDatabaseBackendLevelDB.h"
#include "IDBTransactionBackendLevelDB.h"
#include "SharedBuffer.h"
#include <wtf/OwnPtr.h>
#include <wtf/PassOwnPtr.h>
#include <wtf/RefPtr.h>

namespace WebCore {

class IDBKeyRange;

class IDBCursorBackendLevelDB : public IDBCursorBackendInterface {
public:
    static PassRefPtr<IDBCursorBackendLevelDB> create(PassRefPtr<IDBBackingStore::Cursor> cursor, IndexedDB::CursorType cursorType, IDBTransactionBackendLevelDB* transaction, int64_t objectStoreId)
    {
        return adoptRef(new IDBCursorBackendLevelDB(cursor, cursorType, IDBDatabaseBackendInterface::NormalTask, transaction, objectStoreId));
    }
    static PassRefPtr<IDBCursorBackendLevelDB> create(PassRefPtr<IDBBackingStore::Cursor> cursor, IndexedDB::CursorType cursorType, IDBDatabaseBackendInterface::TaskType taskType, IDBTransactionBackendLevelDB* transaction, int64_t objectStoreId)
    {
        return adoptRef(new IDBCursorBackendLevelDB(cursor, cursorType, taskType, transaction, objectStoreId));
    }
    virtual ~IDBCursorBackendLevelDB();

    // IDBCursorBackendInterface
    virtual void advance(unsigned long, PassRefPtr<IDBCallbacks>, ExceptionCode&);
    virtual void continueFunction(PassRefPtr<IDBKey>, PassRefPtr<IDBCallbacks>, ExceptionCode&);
    virtual void deleteFunction(PassRefPtr<IDBCallbacks>, ExceptionCode&);
    virtual void prefetchContinue(int numberToFetch, PassRefPtr<IDBCallbacks>, ExceptionCode&);
    virtual void prefetchReset(int usedPrefetches, int unusedPrefetches);
    virtual void postSuccessHandlerCallback() { }

    PassRefPtr<IDBKey> key() const { return m_cursor->key(); }
    PassRefPtr<IDBKey> primaryKey() const { return m_cursor->primaryKey(); }
    PassRefPtr<SharedBuffer> value() const { return (m_cursorType == IndexedDB::CursorKeyOnly) ? 0 : m_cursor->value(); }
    void close();

private:
    IDBCursorBackendLevelDB(PassRefPtr<IDBBackingStore::Cursor>, IndexedDB::CursorType, IDBDatabaseBackendInterface::TaskType, IDBTransactionBackendLevelDB*, int64_t objectStoreId);

    class CursorIterationOperation;
    class CursorAdvanceOperation;
    class CursorPrefetchIterationOperation;

    IDBDatabaseBackendInterface::TaskType m_taskType;
    IndexedDB::CursorType m_cursorType;
    const RefPtr<IDBDatabaseBackendLevelDB> m_database;
    const RefPtr<IDBTransactionBackendLevelDB> m_transaction;
    const int64_t m_objectStoreId;

    RefPtr<IDBBackingStore::Cursor> m_cursor; // Must be destroyed before m_transaction.
    RefPtr<IDBBackingStore::Cursor> m_savedCursor; // Must be destroyed before m_transaction.

    bool m_closed;
};

} // namespace WebCore

#endif // ENABLE(INDEXED_DATABASE) && USE(LEVELDB)

#endif // IDBCursorBackendLevelDB_h
