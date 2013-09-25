/*
 * Copyright (C) 2006, 2013 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef Pasteboard_h
#define Pasteboard_h

#include "DragImage.h"
#include "KURL.h"
#include <wtf/Noncopyable.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

#if PLATFORM(GTK)
typedef struct _GtkClipboard GtkClipboard;
#endif

#if PLATFORM(QT)
#include <QMimeData>
#endif

#if PLATFORM(WIN)
#include "COMPtr.h"
#include "WCDataObject.h"
#include <objidl.h>
#include <windows.h>
typedef struct HWND__* HWND;
#endif

// FIXME: This class uses the DOM and makes calls to Editor.
// It should be divested of its knowledge of the frame and editor.

namespace WebCore {

class DataObjectGtk;
class DocumentFragment;
class DragData;
class Element;
class Frame;
class Node;
class Range;
class SharedBuffer;

enum ShouldSerializeSelectedTextForClipboard { DefaultSelectedTextType, IncludeImageAltTextForClipboard };

// For writing to the pasteboard. Generally sorted with the richest formats on top.

struct PasteboardWebContent {
#if !(PLATFORM(EFL) || PLATFORM(GTK) || PLATFORM(IOS) || PLATFORM(QT) || PLATFORM(WIN))
    bool canSmartCopyOrDelete;
    RefPtr<SharedBuffer> dataInWebArchiveFormat;
    RefPtr<SharedBuffer> dataInRTFDFormat;
    RefPtr<SharedBuffer> dataInRTFFormat;
    String dataInStringFormat;
    Vector<String> clientTypes;
    Vector<RefPtr<SharedBuffer>> clientData;
#endif
};

struct PasteboardURL {
    KURL url;
    String title;
#if PLATFORM(MAC) && !PLATFORM(IOS)
    String userVisibleForm;
#endif
};

struct PasteboardImage {
#if !(PLATFORM(EFL) || PLATFORM(GTK) || PLATFORM(IOS) || PLATFORM(QT) || PLATFORM(WIN))
    PasteboardURL url;
#endif
    RefPtr<Image> image;
#if !(PLATFORM(EFL) || PLATFORM(GTK) || PLATFORM(IOS) || PLATFORM(QT) || PLATFORM(WIN))
    RefPtr<SharedBuffer> resourceData;
    String resourceMIMEType;
#endif
};

// For reading from the pasteboard.

class PasteboardWebContentReader {
public:
    virtual ~PasteboardWebContentReader() { }

#if !(PLATFORM(EFL) || PLATFORM(GTK) || PLATFORM(IOS) || PLATFORM(QT) || PLATFORM(WIN))
    virtual bool readWebArchive(PassRefPtr<SharedBuffer>) = 0;
    virtual bool readFilenames(const Vector<String>&) = 0;
    virtual bool readHTML(const String&) = 0;
    virtual bool readRTFD(PassRefPtr<SharedBuffer>) = 0;
    virtual bool readRTF(PassRefPtr<SharedBuffer>) = 0;
    virtual bool readImage(PassRefPtr<SharedBuffer>, const String& type) = 0;
    virtual bool readURL(const KURL&, const String& title) = 0;
#endif
    virtual bool readPlainText(const String&) = 0;
};

struct PasteboardPlainText {
    String text;
#if PLATFORM(MAC) && !PLATFORM(IOS)
    bool isURL;
#endif
};

class Pasteboard {
    WTF_MAKE_NONCOPYABLE(Pasteboard); WTF_MAKE_FAST_ALLOCATED;
public:
    ~Pasteboard();

    static PassOwnPtr<Pasteboard> createForCopyAndPaste();
    static PassOwnPtr<Pasteboard> createPrivate(); // Temporary pasteboard. Can put data on this and then write to another pasteboard with writePasteboard.

    bool hasData();
    Vector<String> types();
    String readString(const String& type);

    bool writeString(const String& type, const String& data);
    void clear();
    void clear(const String& type);

    void read(PasteboardPlainText&);
    void read(PasteboardWebContentReader&);

    void write(const PasteboardURL&);
    void write(const PasteboardImage&);
    void write(const PasteboardWebContent&);

    Vector<String> readFilenames();
    bool canSmartReplace();

    void writeMarkup(const String& markup);
    enum SmartReplaceOption { CanSmartReplace, CannotSmartReplace };
    void writePlainText(const String&, SmartReplaceOption); // FIXME: Two separate functions would be clearer than one function with an argument.
    void writePasteboard(const Pasteboard& sourcePasteboard);

#if ENABLE(DRAG_SUPPORT)
    static PassOwnPtr<Pasteboard> createForDragAndDrop();
    static PassOwnPtr<Pasteboard> createForDragAndDrop(const DragData&);

    void setDragImage(DragImageRef, const IntPoint& hotSpot);
#endif

#if PLATFORM(GTK) || PLATFORM(IOS) || PLATFORM(QT) || PLATFORM(WIN)
    PassRefPtr<DocumentFragment> documentFragment(Frame*, PassRefPtr<Range>, bool allowPlainText, bool& chosePlainText); // FIXME: Layering violation.
    void writeSelection(Range*, bool canSmartCopyOrDelete, Frame*, ShouldSerializeSelectedTextForClipboard = DefaultSelectedTextType); // FIXME: Layering violation.
#endif

#if PLATFORM(GTK) || PLATFORM(QT) || PLATFORM(WIN)
    void writeImage(Node*, const KURL&, const String& title); // FIXME: Layering violation.
#endif

#if PLATFORM(GTK)
    static PassOwnPtr<Pasteboard> create(PassRefPtr<DataObjectGtk>);
    static PassOwnPtr<Pasteboard> create(GtkClipboard*);
    PassRefPtr<DataObjectGtk> dataObject() const;
#endif

#if PLATFORM(GTK) || PLATFORM(QT)
    static PassOwnPtr<Pasteboard> createForGlobalSelection();
#endif

#if PLATFORM(IOS)
    void setFrame(Frame*); // FIXME: Layering violation.

    void writeImage(Node*, Frame*); // FIXME: Layering violation.
    void writePlainText(const String&, Frame*); // FIXME: Layering violation.

    static NSArray* supportedPasteboardTypes();
#endif

#if PLATFORM(MAC) && !PLATFORM(IOS)
    explicit Pasteboard(const String& pasteboardName);
    static PassOwnPtr<Pasteboard> create(const String& pasteboardName);

    const String& name() const { return m_pasteboardName; }
#endif

#if PLATFORM(QT)
    static PassOwnPtr<Pasteboard> create(const QMimeData* readableClipboard = 0, bool isForDragAndDrop = false);

    QMimeData* clipboardData() const { return m_writableData; }
    void invalidateWritableData() const { m_writableData = 0; }
    bool isForDragAndDrop() const { return m_isForDragAndDrop; }
    bool isForCopyAndPaste() const { return !m_isForDragAndDrop; }
#endif

#if PLATFORM(WIN)
    COMPtr<IDataObject> dataObject() const { return m_dataObject; }
    void setExternalDataObject(IDataObject*);
    void writeURLToWritableDataObject(const KURL&, const String&);
    COMPtr<WCDataObject> writableDataObject() const { return m_writableDataObject; }
    void writeImageToDataObject(Element*, const KURL&); // FIXME: Layering violation.
#endif

private:
    Pasteboard();

#if PLATFORM(GTK)
    Pasteboard(PassRefPtr<DataObjectGtk>);
    Pasteboard(GtkClipboard*);
#endif

#if PLATFORM(IOS)
    PassRefPtr<DocumentFragment> documentFragmentForPasteboardItemAtIndex(Frame*, int index, bool allowPlainText, bool& chosePlainText); // FIXME: Layering violation.
#endif

#if PLATFORM(QT)
    Pasteboard(const QMimeData* , bool);

    const QMimeData* readData() const;
#endif

#if PLATFORM(WIN)
    explicit Pasteboard(IDataObject*);
    explicit Pasteboard(WCDataObject*);
    explicit Pasteboard(const DragDataMap&);

    void finishCreatingPasteboard();
    void writeRangeToDataObject(Range*, Frame*); // FIXME: Layering violation.
    void writeURLToDataObject(const KURL&, const String&);
    void writePlainTextToDataObject(const String&, SmartReplaceOption);
#endif

#if PLATFORM(GTK)
    RefPtr<DataObjectGtk> m_dataObject;
    GtkClipboard* m_gtkClipboard;
#endif

#if PLATFORM(IOS)
    Frame* m_frame; // FIXME: Layering violation.
    long m_changeCount;
#endif

#if PLATFORM(MAC) && !PLATFORM(IOS)
    String m_pasteboardName;
    long m_changeCount;
#endif

#if PLATFORM(QT)
    bool m_selectionMode;
    const QMimeData* m_readableData;
    mutable QMimeData* m_writableData;
    bool m_isForDragAndDrop;
#endif

#if PLATFORM(WIN)
    HWND m_owner;
    COMPtr<IDataObject> m_dataObject;
    COMPtr<WCDataObject> m_writableDataObject;
    DragDataMap m_dragDataMap;
#endif
};

#if PLATFORM(IOS)
extern NSString *WebArchivePboardType;
#endif

#if PLATFORM(MAC) && !PLATFORM(IOS)
extern const char* const WebArchivePboardType;
extern const char* const WebURLNamePboardType;
#endif

#if !(PLATFORM(GTK) || PLATFORM(QT))

inline Pasteboard::~Pasteboard()
{
}

#endif

} // namespace WebCore

#endif // Pasteboard_h
