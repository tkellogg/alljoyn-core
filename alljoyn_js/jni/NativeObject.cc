/*
 * Copyright (c) 2011-2013, AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include "NativeObject.h"

#include "TypeMapping.h"
#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_JS"

NativeObject::NativeObject(Plugin& plugin, NPObject* objectValue) :
    plugin(plugin),
    objectValue(NPN_RetainObject(objectValue))
{
    QCC_DbgTrace(("%s(objectValue=%p)", __FUNCTION__, objectValue));
    plugin->nativeObjects[this] = objectValue;
}

NativeObject::NativeObject(Plugin& plugin) :
    plugin(plugin),
    objectValue(NULL)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    NPVariant variant = NPVARIANT_VOID;
    if (NewObject(plugin, variant)) {
        objectValue = NPVARIANT_TO_OBJECT(variant);
        plugin->nativeObjects[this] = objectValue;
    } else {
        NPN_ReleaseVariantValue(&variant);
    }
}

NativeObject::~NativeObject()
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    plugin->nativeObjects.erase(this);
    Invalidate();
}

void NativeObject::Invalidate()
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    if (objectValue) {
        NPN_ReleaseObject(objectValue);
        objectValue = NULL;
    }
}

bool NativeObject::operator==(const NativeObject& that) const
{
    NPVariant a, b;
    OBJECT_TO_NPVARIANT(objectValue, a);
    OBJECT_TO_NPVARIANT(that.objectValue, b);
    return plugin->StrictEquals(a, b);
}
