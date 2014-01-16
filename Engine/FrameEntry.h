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

#ifndef NATRON_ENGINE_FRAMEENTRY_H_
#define NATRON_ENGINE_FRAMEENTRY_H_

#include <QtCore/QObject>

#include "Global/GlobalDefines.h"

#include "Engine/Cache.h"
#include "Engine/ChannelSet.h"
#include "Engine/Format.h"
#include "Engine/TextureRect.h"

class Hash64;

namespace Natron{
    
    
    class FrameKey : public KeyHelper<U64>{
    public:
        SequenceTime _time;
        U64 _treeVersion;
        double _zoomFactor;
        double _exposure;
        int _lut;
        int _bitDepth;
        int _channels;
        int _view;
        RectI _dataWindow;//RoD
        Format _displayWindow;
        TextureRect _textureRect; // texture rectangle definition (bounds in the original image + width and height)
        
        
        FrameKey()
		: KeyHelper<U64>()
        , _time(0)
        , _treeVersion(0)
        , _zoomFactor(0)
        , _exposure(0)
        , _lut(0)
        , _bitDepth(0)
        , _channels(0)
        , _view(0)
        , _dataWindow()
        , _displayWindow()
        , _textureRect()
        {}
        
        FrameKey(KeyHelper<U64>::hash_type hash)
		: KeyHelper<U64>(hash)
        , _time(0)
        , _treeVersion(0)
        , _zoomFactor(0)
        , _exposure(0)
        , _lut(0)
        , _bitDepth(0)
        , _channels(0)
        , _view(0)
        , _dataWindow()
        , _displayWindow()
        , _textureRect()
        {}
        
        FrameKey(SequenceTime time,U64 treeVersion,double zoomFactor,double exposure,
                 int lut,int bitDepth,int channels,int view,
                 const RectI& dataWindow,const Format& displayWindow,const TextureRect& textureRect):
        KeyHelper<U64>()
        ,_time(time)
        ,_treeVersion(treeVersion)
        ,_zoomFactor(zoomFactor)
        ,_exposure(exposure)
        ,_lut(lut)
        ,_bitDepth(bitDepth)
        ,_channels(channels)
        ,_view(view)
        ,_dataWindow(dataWindow)
        ,_displayWindow(displayWindow)
        ,_textureRect(textureRect)
        {
            
        }
        
        void fillHash(Hash64* hash) const {
            hash->append(_time);
            hash->append(_treeVersion);
            hash->append(_zoomFactor);
            hash->append(_exposure);
            hash->append(_lut);
            hash->append(_bitDepth);
            hash->append(_channels);
            hash->append(_view);
            hash->append(_dataWindow.left());
            hash->append(_dataWindow.right());
            hash->append(_dataWindow.top());
            hash->append(_dataWindow.bottom());
            hash->append(_displayWindow.left());
            hash->append(_displayWindow.right());
            hash->append(_displayWindow.top());
            hash->append(_displayWindow.bottom());
            double ap = _displayWindow.getPixelAspect();
            hash->append(ap);
            hash->append(_textureRect.x);
            hash->append(_textureRect.y);
            hash->append(_textureRect.r);
            hash->append(_textureRect.t);
            hash->append(_textureRect.w);
            hash->append(_textureRect.h);
        }
        
        bool operator==(const FrameKey& other) const {
            return  _time == other._time &&
                    _treeVersion == other._treeVersion &&
                    _zoomFactor == other._zoomFactor &&
                    _exposure == other._exposure &&
                    _lut == other._lut &&
                    _bitDepth == other._bitDepth &&
                    _channels == other._channels &&
                    _view == other._view &&
                    _dataWindow == other._dataWindow &&
                    _displayWindow == other._displayWindow &&
                    _textureRect == other._textureRect;
        }
    };
}

namespace boost {
    namespace serialization {
        
        template<class Archive>
        void serialize(Archive & ar, Natron::FrameKey & f, const unsigned int version)
        {
            (void)version;
            ar & f._time;
            ar & f._treeVersion;
            ar & f._zoomFactor;
            ar & f._exposure;
            ar & f._lut;
            ar & f._bitDepth;
            ar & f._channels;
            ar & f._view;
            ar & f._dataWindow;
            ar & f._displayWindow;
            ar & f._textureRect;
        }
    }
}

namespace Natron{
    class FrameEntry : public CacheEntryHelper<U8,FrameKey>
    {
        
    public:
        
        FrameEntry(const FrameKey& params,size_t size,int cost,std::string path = std::string())
        :CacheEntryHelper<U8,FrameKey>(params,size,cost,path)
        {
        }
        
        FrameEntry(const FrameKey& params,const std::string& path)
        :CacheEntryHelper<U8,FrameKey>(params,path)
        {
        }
      
        ~FrameEntry(){ }
        
        static FrameKey makeKey(SequenceTime time,U64 treeVersion,double zoomFactor,double exposure,
                                int lut,int bitDepth,int channels,int view,
                                const RectI& dataWindow,const Format& displayWindow,const TextureRect& textureRect){
            return FrameKey(time,treeVersion,zoomFactor,exposure,lut,bitDepth,channels,view,dataWindow,displayWindow,textureRect);
        }
        
        U8* data() const {return _data.writable();}
        
    };
    
    
}


#endif // NATRON_ENGINE_FRAMEENTRY_H_
