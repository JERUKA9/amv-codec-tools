/*
 * CopyRight (C) 2007, SangWei(swkyer@gmail.com), Wuhan, Hubei, China.
 * All Rights Reserved.
 * 
 * FileName:
 * Description:
 *
 */
#ifndef __AMVDEC_H__
#define __AMVDEC_H__

//#include "AMVHeader.h"

#ifdef WIN32
	#ifdef AMVLIB_EXPORTS
		#define AMVLIB_API __declspec(dllexport)
	#else
		#define AMVLIB_API __declspec(dllimport)
	#endif
#else	/* Linux */
	#define AMVLIB_API
#endif

//for C linkage
#ifdef __cplusplus
extern "C" {
#endif
	
typedef struct _amv_important_header_data
{
	unsigned int dwMicroSecPerFrame;	// ֡��ʱ������΢�λ
	unsigned int dwWidth;				// ��Ƶͼ��Ŀ�������Ϊ��λ��
	unsigned int dwHeight;				// ��Ƶͼ��ĸߣ�������Ϊ��λ��
	unsigned int dwSpeed;				// ֡�ٶ� /��֡/��)
	unsigned int dwTimeSec;				// ��ʱ�䣨�룩
	unsigned int dwTimeMin;				// ��ʱ�䣨�֣�
	unsigned int dwTimeHour;			// ��ʱ�� ��Сʱ��
	
	unsigned short wFormatTag;
	unsigned short nChannels;			// ��Ƶͨ����
	unsigned int nSamplesPerSec;		// ��Ƶ������
	unsigned int nAvgBytesPerSec;
	unsigned short nBlockAlign;
	unsigned short wBitsPerSample;		// ����λ��
	unsigned short cbSize;
	unsigned short wSamplesPerBlock;
} AMVInfo;


typedef struct _frame_buffer_struct
{
	unsigned char *videobuff;
	unsigned char *audiobuff;
	unsigned int videobufflen; 
	unsigned int audiobufflen;
	int framenum;
} FRAMEBUFF;

typedef struct _video_buffer_struct
{
	unsigned char *fbmpdat;
	unsigned int len;
} VIDEOBUFF;

#define AUDIO_FILE_TYPE_PCM			0
#define AUDIO_FILE_TYPE_ADPCM_IMA	1
typedef struct _audio_buffer_struct
{
	short *audiodata;
	unsigned int len;
} AUDIOBUFF;


typedef struct _amv_decode_struct
{
	char *amvfilename;
	
	int opened;

	long dataseekpos;
	long fileseekpos;

	AMVInfo amvinfo;

	unsigned int currentframe;
	unsigned int totalframe;
	FRAMEBUFF framebuf;
	
	VIDEOBUFF videobuf;
	AUDIOBUFF audiobuf;
} AMVDecoder;


AMVLIB_API AMVDecoder *AmvOpen(const char *amvname);
AMVLIB_API void AmvClose(AMVDecoder *amv);

AMVLIB_API int AmvReadNextFrame(AMVDecoder *amv);
AMVLIB_API int AmvRewindFrameStart(AMVDecoder *amv);

AMVLIB_API int AmvVideoDecode(AMVDecoder *amv);
AMVLIB_API int AmvAudioDecode(AMVDecoder *amv);

AMVLIB_API int AmvCreateJpegFileFromFrameBuffer(AMVDecoder *amv, const char *dirname);
AMVLIB_API int AmvCreateJpegFileFromBuffer(AMVInfo *amvinfo, 
										   FRAMEBUFF *framebuf, 
										   const char *filename);
AMVLIB_API int AmvConvertJpegFileToBmpFile(const char *jpgname, const char *bmpname);

AMVLIB_API int AmvCreateWavFileFromAmvFile(AMVDecoder *amv, int type, const char *wavfile);

//for C linkage
#ifdef __cplusplus
	}
#endif

#endif /* __AMVDEC_H__ */