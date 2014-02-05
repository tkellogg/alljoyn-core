/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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
 ******************************************************************************/

#import "AnnounceHandlerAdapter.h"
#import "QASConvertUtil.h"
#import "QASAboutDataConverter.h"

AnnounceHandlerAdapter::AnnounceHandlerAdapter(id <QASAnnouncementListener> announcementListener)
{
	qasAnnouncementListener = announcementListener;
}

AnnounceHandlerAdapter::~AnnounceHandlerAdapter()
{
}

void AnnounceHandlerAdapter::Announce(uint16_t version, uint16_t port, const char *busName, const ObjectDescriptions& objectDescs, const AboutData& aboutData)
{
	NSMutableDictionary *qasAboutData;
    
    NSLog(@"[%@] [%@] Received an announcemet from %s ", @"DEBUG", @"AnnounceHandlerAdapter", busName);
        
	// Convert AboutData to QASAboutData
	qasAboutData = [QASAboutDataConverter convertToAboutDataDictionary:aboutData];
    
	[qasAnnouncementListener announceWithVersion:version port:port busName:[QASConvertUtil convertConstCharToNSString:busName] objectDescriptions:[QASAboutDataConverter convertToObjectDescriptionsDictionary:objectDescs] aboutData:&qasAboutData];
}