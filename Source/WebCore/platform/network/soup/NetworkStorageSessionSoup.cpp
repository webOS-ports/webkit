/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
 * Copyright (C) 2013 University of Szeged. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "NetworkStorageSession.h"

#include "ResourceHandle.h"
#include <wtf/MainThread.h>
#include <wtf/PassOwnPtr.h>
#include <wtf/text/StringConcatenate.h>

namespace WebCore {

NetworkStorageSession::NetworkStorageSession(SoupSession* session)
    : m_session(adoptGRef(session))
    , m_isPrivate(false)
{
}

static OwnPtr<NetworkStorageSession>& defaultSession()
{
    ASSERT(isMainThread());
    DEFINE_STATIC_LOCAL(OwnPtr<NetworkStorageSession>, session, ());
    return session;
}

NetworkStorageSession& NetworkStorageSession::defaultStorageSession()
{
    if (!defaultSession())
        defaultSession() = adoptPtr(new NetworkStorageSession(ResourceHandle::defaultSession()));
    return *defaultSession();
}

PassOwnPtr<NetworkStorageSession> NetworkStorageSession::createPrivateBrowsingSession(const String&)
{
    OwnPtr<NetworkStorageSession> session = adoptPtr(new NetworkStorageSession(ResourceHandle::createPrivateBrowsingSession()));
    session->m_isPrivate = true;

    return session.release();
}

void NetworkStorageSession::switchToNewTestingSession()
{
    // A null session will make us fall back to the default cookie jar, which is currently
    // the expected behavior for tests.
    defaultSession() = adoptPtr(new NetworkStorageSession(ResourceHandle::createTestingSession()));
}

}