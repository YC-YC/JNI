/*
 * WMAID3Parser.h
 *
 *  Created on: 2016-1-11
 *      Author: guoxs
 */

#ifndef _WMA_ID3_PARSER_H_
#define _WMA_ID3_PARSER_H_

#include "CommDef.h"
#include "BaseID3Parser.h"

/*************************************************************************
+--------------------------------------------------------------+
|      Header (30 bytes)   HeadFlag:16; HeadSize:8;            |
|                          HeadCount:4; Reserve:2;             |
+--------------------------------------------------------------+
|      Frames (1....n)                                         |
+--------------------------------------------------------------+

// 所有的TAG信息存放在标准帧和扩展帧中，其他帧可以不予考虑
// 所有的信息都是UNICODE编码
// 标准帧结构
+--------------------------------------------------------------+
|      Header (24 bytes)   HeadFlag:16; HeadSize:8;            |
+--------------------------------------------------------------+
|      标题信息大小（2 bytes）								   |
+--------------------------------------------------------------+
|      艺术家信息大小（2 bytes）                                					   |
+--------------------------------------------------------------+
|      版权信息大小（2 bytes）                                  					   |
+--------------------------------------------------------------+
|      备注信息大小（2 bytes）                                  					   |
+--------------------------------------------------------------+
|      未知信息大小（2 bytes）                                  					   |
+--------------------------------------------------------------+
|      标题信息内容(0x00 0x00结束)                              |
+--------------------------------------------------------------+
|      艺术家信息内容(0x00 0x00结束)                            |
+--------------------------------------------------------------+
|      版权信息内容(0x00 0x00结束)                              |
+--------------------------------------------------------------+
|      备注信息内容(0x00 0x00结束)                              |
+--------------------------------------------------------------+
|      未知信息内容(0x00 0x00结束)                              |
+--------------------------------------------------------------+
// 扩展帧结构
+--------------------------------------------------------------+
|      Header (24 bytes)   HeadFlag:16; HeadSize:8;            |
+--------------------------------------------------------------+
|      扩展信息个数EXNO（2 bytes）                              				   |
+--------------------------------------------------------------+
|      EXINFO (1....EXNO)                                      |
+--------------------------------------------------------------+
// 每个扩展信息EXINFO结构
+--------------------------------------------------------------+
|      EXINFO NAME Size (2 bytes)   扩展信息名字大小            		   |
+--------------------------------------------------------------+
|      扩展信息名称                                             							   |
+--------------------------------------------------------------+
|      标志FLAG   (2 bytes)                             		   |
+--------------------------------------------------------------+
|      值的大小   (2 bytes)                            		   |
+--------------------------------------------------------------+
|      实际的值   (图片格式参考ID3V2.3)                       	   |
+--------------------------------------------------------------+

当扩展信息名字为WMFSDKVersion时，这个值表示的是这个WMA文件的版本；
当扩展信息名字为WM/AlbumTitle时，这个值代表的就是专辑名；
当扩展信息名字为WM/Genre时，这个值代表的就是流派；
下面再来看看那个标志Flag，这个基本上是没什么用的（通常值为0），
对WM/TrackNumber和WM/Track这两个扩展信息名字有用，
当Flag为3的时候后面的值（也就是曲目信息）是以4个字节的整数的形式表示，
当Flag为0的时候，曲目信息是以普通的字符串形式表示的。

Author
Copyright
Description
Rating
Title
WM/AlbumArtist
WM/AlbumCoverURL
WM/AlbumTitle
WM/AudioFileURL
WM/AudioSourceURL
WM/AuthorURL
WM/BeatsPerMinute
WM/Category
WM/Composer
WM/Conductor
WM/ContentDistributor
WM/ContentGroupDescription
WM/Director
WM/DVDID
WM/EncodedBy
WM/EncodingSettings
WM/EncodingTime
WM/Genre
WM/GenreID
WM/InitialKey
WM/ISRC
WM/Language
WM/Lyrics
WM/Lyrics_Synchronised
WM/MCDI
WM/MediaClassPrimaryID
WM/MediaClassSecondaryID
WM/MediaCredits
WM/MediaIsDelay
WM/MediaIsFinale
WM/MediaIsLive
WM/MediaIsPremiere
WM/MediaIsRepeat
WM/MediaIsSAP
WM/MediaIsSubtitled
WM/MediaIsStereo
WM/MediaNetworkAffiliation
WM/MediaOriginalBroadcastDateTime
WM/MediaOriginalChannel
WM/MediaStationCallSign
WM/MediaStationName
WM/ModifiedBy
WM/Mood
WM/OriginalAlbumTitle
WM/OriginalArtist
WM/OriginalFilename
WM/OriginalLyricist
WM/OriginalReleaseTime
WM/OriginalReleaseYear
WM/ParentalRating
WM/ParentalRatingReason
WM/PartOfSet
WM/Period
WM/Picture
WM/Producer
WM/PromotionURL
WM/Provider
WM/ProviderCopyright
WM/ProviderRating
WM/ProviderStyle
WM/Publisher
WM/RadioStationName
WM/RadioStationOwner
WM/SharedUserRating
WM/SubTitle
WM/SubTitleDescription
WM/Text
WM/ToolName
WM/ToolVersion
WM/Track
WM/TrackNumber
WM/UniqueFileIdentifier
WM/UserWebURL
WM/WMCollectionGroupID
WM/WMCollectionID
WM/WMContentID
WM/Writer
WM/Year

WMFSDKVersion
WMFSDKNeeded
IsVBR
*************************************************************************/

// 定义帧类型
enum WMA_FRAMESTYLE_T {
	WMA_FRAMESTYLE_STANDARD,   // 标准帧
	WMA_FRAMESTYLE_EXTEND,     // 扩展帧
	WMA_FRAMESTYLE_UNKNOWN,    // 未知帧
};

// 定义帧标识类型ID(暂未用到那么多)
enum WMA_FRAMEID_T {
	// 基础类型标准帧中的内容
	WMA_FRAMEID_AUTHOR = 0,
	WMA_FRAMEID_COPYRIGHT,
	WMA_FRAMEID_DESCRIPTION,
	WMA_FRAMEID_RATING,
	WMA_FRAMEID_TITLE,

	// 其他类型按字母排序
	WMA_FRAMEID_ALBUMARTIST,
	WMA_FRAMEID_ALBUMCOVERURL,
	WMA_FRAMEID_ALBUMTITLE,
	WMA_FRAMEID_AUDIOFILEURL,
	WMA_FRAMEID_AUDIOSOURCEURL,
	WMA_FRAMEID_AUTHORURL,
	WMA_FRAMEID_BPMT,       // WM/BeatsPerMinute
	WMA_FRAMEID_CATEGORY,
	WMA_FRAMEID_COMPOSER,
	WMA_FRAMEID_CONDUCTOR,
	WMA_FRAMEID_CONTENTDISTRIBUTOR,
	WMA_FRAMEID_CGDPN, // WM/ContentGroupDescription
	WMA_FRAMEID_DIRECTOR,
	WMA_FRAMEID_DVDID,
	WMA_FRAMEID_ENCODEDBY,
	WMA_FRAMEID_ENCODINGSETTINGS,
	WMA_FRAMEID_ENCODINGTIME,
	WMA_FRAMEID_GENRE,
	WMA_FRAMEID_GENREID,
	WMA_FRAMEID_INITIALKEY,
	WMA_FRAMEID_ISRC,
	WMA_FRAMEID_LANGUAGE,
	WMA_FRAMEID_LYRICS,
	WMA_FRAMEID_LYRICSSYNC, // WM/Lyrics_Synchronised
	WMA_FRAMEID_MCDI,
	WMA_FRAMEID_MCPID, // WM/MediaClassPrimaryID
	WMA_FRAMEID_MCSID, // WM/MediaClassSecondaryID
	WMA_FRAMEID_MDACREDITS, // WM/MediaCredits
	WMA_FRAMEID_MDAISDELAY,   // WM/MediaIsDelay
	WMA_FRAMEID_MDAISFINALE,  // WM/MediaIsFinale
	WMA_FRAMEID_MDAISLIVE,    // WM/MediaIsLive
	WMA_FRAMEID_MDAISPREMIERE,  // WM/MediaIsPremiere
	WMA_FRAMEID_MDAISREPEAT,    // WM/MediaIsRepeat
	WMA_FRAMEID_MDAISSAP,       // WM/MediaIsSAP
	WMA_FRAMEID_MDAISSUBTITLED,  // WM/MediaIsSubtitled
	WMA_FRAMEID_MDAISSTEREO,     // WM/MediaIsStereo
	WMA_FRAMEID_MDANETWORKAFFILIATION,  // WM/MediaNetworkAffiliation
	WMA_FRAMEID_MDAORIGINALBDT,         // WM/MediaOriginalBroadcastDateTime
	WMA_FRAMEID_MDAORIGINALCHANNEL,     // WM/MediaOriginalChannel
	WMA_FRAMEID_MDASTATIONCALLSIGN,     // WM/MediaStationCallSign
	WMA_FRAMEID_MDASTATIONNAME,         // WM/MediaStationName
	WMA_FRAMEID_MODIFIEDBY,
	WMA_FRAMEID_MOOD,
	WMA_FRAMEID_ORIGALBUMTITLE,     // WM/OriginalAlbumTitle
	WMA_FRAMEID_ORIGARTIST,         // WM/OriginalArtist
	WMA_FRAMEID_ORIGFILENAME,       // WM/OriginalFilename
	WMA_FRAMEID_ORIGLYRICIST,       // WM/OriginalLyricist
	WMA_FRAMEID_ORIGRELEASETIME,    // WM/OriginalReleaseTime
	WMA_FRAMEID_ORIGRELEASEYEAR,    // WM/OriginalReleaseYear
	WMA_FRAMEID_PARENTALRATING,
	WMA_FRAMEID_PARENTALRATINGREASON,    // WM/ParentalRatingReason
	WMA_FRAMEID_PARTOFSET,
	WMA_FRAMEID_PERIOD,
	WMA_FRAMEID_PICTURE,
	WMA_FRAMEID_PRODUCER,
	WMA_FRAMEID_PROMOTIONURL,
	WMA_FRAMEID_PROVIDER,
	WMA_FRAMEID_PROVIDERCPYRIGHT,
	WMA_FRAMEID_PROVIDERRATING,
	WMA_FRAMEID_PROVIDERSTYLE,
	WMA_FRAMEID_PUBLISHER,
	WMA_FRAMEID_RADIOSTATIONNAME,
	WMA_FRAMEID_RADIOSTATIONOWNER,
	WMA_FRAMEID_SHAREUSERRATING,
	WMA_FRAMEID_SUBTITLE,
	WMA_FRAMEID_SUBTITLEDESCRIPTION,
	WMA_FRAMEID_TEXT,
	WMA_FRAMEID_TOOLNAME,
	WMA_FRAMEID_TOOLVERSION,
	WMA_FRAMEID_TRACK,
	WMA_FRAMEID_TRACKNUMBER,
	WMA_FRAMEID_UNIQUEFILEIDENTIFIER,
	WMA_FRAMEID_USERWEBURL,
	WMA_FRAMEID_WMCOLLECTIONGROUPID,
	WMA_FRAMEID_WMCOLLECTIONID,
	WMA_FRAMEID_CONTENTID,
	WMA_FRAMEID_WRITER,
	WMA_FRAMEID_YEAR,

	WMA_FRAMEID_SDKVERSION, // WMFSDKVersion
	WMA_FRAMEID_SDKNEEDED,  // WMFSDKNeeded
	WMA_FRAMEID_ISVBR,      // IsVBR

	////////////////////////////////////////////////////////////////////
	WMA_FRAMEID_UNKNOWN, 	// 未知
};

// 定义WMA文件头标识
typedef struct {
	BYTE flag[16];		// 固定的16个字节内容表示是否WMA文件
} S_WMA_HEAD_FLAG;

// 定义WMA文件头大小
typedef struct {
	BYTE size[8];		// 8个字节表示大小（由后向前存储数据）
} S_WMA_HEAD_SIZE;

// 定义WMA文件头结构
typedef struct {
	S_WMA_HEAD_FLAG headFlag;      	// WMA文件标识
	S_WMA_HEAD_SIZE headSize;	   	// WMA文件头大小
	UINT headCount;  				// 帧数
	BYTE reserve[2];				// 保留
} S_WMA_HEAD_INFO;

// 定义帧头标识
typedef struct {
	BYTE flag[16];   	// 固定的16个字节表示帧类型
} S_WMA_FRAME_HEAD_FLAG;

// 定义帧大小
typedef struct {
	BYTE size[8];     // 8个字节表示帧大小（由后向前存储数据）
} S_WMA_FRAME_HEAD_SIZE;

// 定义帧头结构
typedef struct {
	S_WMA_FRAME_HEAD_FLAG frameFlag;
	S_WMA_FRAME_HEAD_SIZE frameSize;
} S_WMA_FRAME_HEAD_INFO;

// 定义解析值的类型
enum WMA_ATTRSTYLE_T {
	WMA_ATTRSTYLE_TXT = 0, // 字符串属性
	WMA_ATTRSTYLE_VAL,     // 值属性
};

class CWMAID3Parser: public CBaseID3Parser {
protected:
	virtual bool HandleParseID3(FILE *pWMAFile, S_ID3_INFO *pID3Info);
	virtual bool HandleParseID3Pic(FILE *pWMAFile, S_PIC_INFO *pPicInfo);

private:
	// 根据文件头结构判断是否WMA文件
	bool BeWMAFile(const S_WMA_HEAD_FLAG &headFlag);

	// 计算头大小
	UINT GetHeadSize(const S_WMA_HEAD_SIZE &headSize);

	// 得到帧的大小
	UINT GetFrameSize(const S_WMA_FRAME_HEAD_SIZE &frameSize);

	// 得到帧类型
	WMA_FRAMESTYLE_T GetFrameStyle(const S_WMA_FRAME_HEAD_FLAG &frameFlag);

	// 判断两个帧头标识是否相等
	bool BeSameFrameFlag(const S_WMA_FRAME_HEAD_FLAG &firstFlag, const S_WMA_FRAME_HEAD_FLAG &secondFlag);

	// 计算由2个字节拼接成的整数大小
	UINT CalUInt16Val(const BYTE *pByteBuf, int bufSize);

	// 计算由4个字节拼接成的整数大小
	UINT CalUInt32Val(const BYTE *pByteBuf, int bufSize);

	// 解析帧数据
	bool ParseFrameData(const BYTE *pFrameData, UINT dataLen, int frameNum, S_ID3_INFO *pID3Info, S_PIC_INFO *pPicInfo);

	// 得到帧头信息
	bool GetFrameHeadInfo(const BYTE *pFrameData, UINT dataLen, S_WMA_FRAME_HEAD_INFO &frameHead);

	// 解析标准帧数据
	bool ParseStandardFrame(const BYTE *pItemFrameData, UINT frameSize, S_ID3_INFO *pID3Info);

	// 解析扩展帧数据(扩展帧里才有图片数据)
	bool ParseExtendFrame(const BYTE *pItemFrameData, UINT frameSize, S_ID3_INFO *pID3Info, S_PIC_INFO *pPicInfo);

	// 解析图片帧数据
	bool ParsePicFrame(const BYTE *pPicFrameData, UINT frameSize, S_PIC_INFO *pPicInfo);
};

#endif /* _WMA_ID3_PARSER_H_ */
