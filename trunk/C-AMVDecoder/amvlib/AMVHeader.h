#ifndef __AMVHEADER_H__
#define __AMVHEADER_H__

#include <stdio.h>

typedef unsigned long  DWORD;
typedef unsigned short WORD;
typedef unsigned char  BYTE;
typedef DWORD          FOURCC;

#ifndef mmioFOURCC
#define mmioFOURCC( ch0, ch1, ch2, ch3 ) \
    ( (DWORD)(BYTE)(ch0) | ( (DWORD)(BYTE)(ch1) << 8 ) |    \
( (DWORD)(BYTE)(ch2) << 16 ) | ( (DWORD)(BYTE)(ch3) << 24 ) )
#endif

// AMV Data Structure - Start >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct _amv_main_header
{
	FOURCC fcc;					// ����Ϊ��amvh��
	DWORD size;					// �����ݽṹ�Ĵ�С�������������8 ���ֽ�
	DWORD dwMicroSecPerFrame;	// ��Ƶ֡���ʱ�䣨��΢��Ϊ��λ��
	BYTE reserved[28];			// ������������28 ���ֽ���Ϊ���ã�ȫ��Ϊ�㡣
/*	DWORD dwMaxBytesPerSec;		// ���AVI �ļ������������
	DWORD dwPaddingGranularity;	// ������������
	DWORD dwFlags;				// AVI�ļ���ȫ�ֱ�ǣ������Ƿ����������
	DWORD dwTotalFrames;		// ��֡��
	DWORD dwInitialFrames;		// Ϊ������ʽָ����ʼ֡�����ǽ�����ʽӦ��ָ��Ϊ0��
	DWORD dwStreams;			// ���ļ����������ĸ���
	DWORD dwSuggestedBufferSize; // �����ȡ���ļ��Ļ����С��Ӧ���������Ŀ飩
*/	DWORD dwWidth;				// ��Ƶͼ��Ŀ�������Ϊ��λ��
	DWORD dwHeight;				// ��Ƶͼ��ĸߣ�������Ϊ��λ��
	DWORD dwSpeed;				// ֡�ٶ� /��֡/��)
	DWORD reserve0;				// ֵ����1����;�������
	DWORD reserve1;				// ֵ����0����;�������
	BYTE dwTimeSec;				// ��ʱ�䣨�룩
	BYTE dwTimeMin;				// ��ʱ�䣨�֣�
	WORD dwTimeHour;			// ��ʱ�� ��Сʱ��
} AMVMainHeader;

typedef struct _amv_stream_header
{
    FOURCC fcc;					// ����Ϊ��strh��
    DWORD size;
	BYTE reserved[56];
/*	FOURCC fccType;				// �������ͣ���auds������Ƶ��������vids������Ƶ������
								//��mids����MIDI��������txts������������
	FOURCC fccHandler;			// ָ�����Ĵ����ߣ���������Ƶ��˵���ǽ�����
	DWORD dwFlags;				// ��ǣ��Ƿ�����������������ɫ���Ƿ�仯��
	WORD wPriority;				// �������ȼ������ж����ͬ���͵���ʱ���ȼ���ߵ�ΪĬ������
	WORD wLanguage;
	DWORD dwInitialFrames;		// Ϊ������ʽָ����ʼ֡��
	DWORD dwScale;				// �����ʹ�õ�ʱ��߶�
	DWORD dwRate;
	DWORD dwStart;				// ���Ŀ�ʼʱ��
	DWORD dwLength;				// ���ĳ��ȣ���λ��dwScale��dwRate �Ķ����йأ�
	DWORD dwSuggestedBufferSize; // ��ȡ��������ݽ���ʹ�õĻ����С
	DWORD dwQuality;			// �����ݵ�����ָ�꣨0 ~ 10,000��
	DWORD dwSampleSize;			// Sample �Ĵ�С
	struct {
		short int left;
		short int top;
		short int right;
		short int bottom;
	} rcFrame;					// ָ�����������Ƶ����������������Ƶ�������е���ʾλ��
								// ��Ƶ��������AMVMAINHEADER�ṹ�е�dwWidth ��dwHeight ����
*/
} AMVVideoStreamHeader;

typedef struct _amv_bitmap_info_header
{
    FOURCC fcc;					// ����Ϊ��strf��
	DWORD size;
	BYTE reserved[36];
/*	DWORD biWidth;
    DWORD biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    DWORD biXPelsPerMeter;
    DWORD biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
*/
} AMVBitmapInfoHeader;


typedef struct _amv_audio_stream_header
{
    FOURCC fcc;					// ����Ϊ��strh��
    DWORD size;
	BYTE reserved[48];
} AMVAudioStreamHeader;

typedef struct _amv_wave_format_ex
{
	FOURCC fcc;					// ����Ϊ��strf��
	DWORD size;
	WORD wFormatTag;			
	WORD nChannels;				// ������
	DWORD nSamplesPerSec;		// ������
	DWORD nAvgBytesPerSec;		// ÿ��ƽ���ֽ���
	WORD nBlockAlign;
	WORD wBitsPerSample;		// ����λ��
	WORD cbSize;
	WORD wSamplesPerBlock;
} AMVWaveFormatEx;


typedef struct _amv_info_struct
{
	FOURCC ccRIFF;
	DWORD riffSize;
	FOURCC riffName;
	FOURCC ccLIST;				// "LIST"
	DWORD listSize;
	FOURCC listType;			// "hdrl"
	AMVMainHeader main_header;	// listData
	
	//////////////// video header <start> ///////////////
	FOURCC ccLISTV;				// "LIST"
	DWORD listSizeV;
	FOURCC listTypeVStrl;		// "strl"
	AMVVideoStreamHeader vstream_header;	// listData
	AMVBitmapInfoHeader vinfo_header;	// listData
	//////////////// video header <end> /////////////////

	//////////////// audio header <start> ///////////////
	FOURCC ccLISTA;				// "LIST"
	DWORD listSizeA;
	FOURCC listTypeAStrl;		// "strl"
	AMVAudioStreamHeader astream_header;	// listData
	AMVWaveFormatEx ainfo_header;	// listData
	//////////////// audio header <end> /////////////////
} AMVHeader;



#endif /* __AMVHEADER_H__ */