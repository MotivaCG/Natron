//  Natron
//
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
/*
 *Created by Alexandre GAUTHIER-FOICHAT on 6/1/2012.
 *contact: immarespond at gmail dot com
 *
 */

#include "Engine/FrameEntry.h"
#include "Engine/FrameParams.h"

using namespace Natron;


FrameKey::FrameKey()
: KeyHelper<U64>()
, _time(0)
, _treeVersion(0)
, _exposure(0)
, _lut(0)
, _bitDepth(0)
, _channels(0)
, _view(0)
, _textureRect()
{}


FrameKey::FrameKey(SequenceTime time,U64 treeVersion,double exposure,
         int lut,int bitDepth,int channels,int view,const TextureRect& textureRect):
KeyHelper<U64>()
,_time(time)
,_treeVersion(treeVersion)
,_exposure(exposure)
,_lut(lut)
,_bitDepth(bitDepth)
,_channels(channels)
,_view(view)
,_textureRect(textureRect)
{
    
}

void FrameKey::fillHash(Hash64* hash) const {
    hash->append(_time);
    hash->append(_treeVersion);
    hash->append(_exposure);
    hash->append(_lut);
    hash->append(_bitDepth);
    hash->append(_channels);
    hash->append(_view);
    hash->append(_textureRect.x1);
    hash->append(_textureRect.y1);
    hash->append(_textureRect.x2);
    hash->append(_textureRect.y2);
    hash->append(_textureRect.w);
    hash->append(_textureRect.h);
    hash->append(_textureRect.closestPo2);
}

bool FrameKey::operator==(const FrameKey& other) const {
    return  _time == other._time &&
    _treeVersion == other._treeVersion &&
    _exposure == other._exposure &&
    _lut == other._lut &&
    _bitDepth == other._bitDepth &&
    _channels == other._channels &&
    _view == other._view &&
    _textureRect == other._textureRect;
}

FrameKey FrameEntry::makeKey(SequenceTime time,U64 treeVersion,double exposure,
                        int lut,int bitDepth,int channels,int view,const TextureRect& textureRect){
    return FrameKey(time,treeVersion,exposure,lut,bitDepth,channels,view,textureRect);
}

boost::shared_ptr<const FrameParams> FrameEntry::makeParams(const RectI rod,int bitDepth,int texW,int texH)
{
    return boost::shared_ptr<const FrameParams>(new FrameParams(rod,bitDepth,texW,texH));
}
