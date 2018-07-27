#ifndef __JPEG_ENCODER_HEADER__
#define __JPEG_ENCODER_HEADER__


class JpegEncoder
{
	//像素点结构体
	struct pixel
	{
		//像素R分量
		unsigned char R;
		//像素G分量
		unsigned char G;
		//像素B分量
		unsigned char B;
	};
	//量化系数结构体
	struct quantCoeff
	{
		//Y分量
		short Y;
		//Cb分量
		short Cb;
		//Cr分量
		short Cr;
	};
public:
	/** 清理数据 */
	void clean(void);

	/** 从BMP文件中读取文件，仅支持24bit，长度是8的倍数的文件 */
	bool readFromBMP(const char* fileName);

	/** 压缩到jpg文件中，quality_scale表示质量，取值范围(0,100), 数字越大压缩比例越高*/
	bool encodeToJPG(const char* fileName, int quality_scale);

private:
	int				m_width;
	int				m_height;
	unsigned char*	m_rgbBuffer;

	unsigned char	m_YTable[64];
	unsigned char	m_CbCrTable[64];

	struct BitString
	{
		int length;
		int value;
	};

	BitString m_Y_DC_Huffman_Table[12];
	BitString m_Y_AC_Huffman_Table[256];

	BitString m_CbCr_DC_Huffman_Table[12];
	BitString m_CbCr_AC_Huffman_Table[256];

private:
	void _initHuffmanTables(void);
	void _initCategoryAndBitcode(void);
	void _initQualityTables(int quality);
	void _computeHuffmanTable(const char* nr_codes, const unsigned char* std_table, BitString* huffman_table);
	BitString _getBitCode(int value);

	void _convertColorSpace(int xPos, int yPos, char* yData, char* cbData, char* crData);
	//新的颜色空间转换函数
	void convertColorSpace(pixel* curBlock, char* yData, char* cbData, char* crData);
	void _foword_FDC(const char* channel_data, short* fdc_data);
	void _doHuffmanEncoding(const short* DU, short& prevDC, const BitString* HTDC, const BitString* HTAC,
		BitString* outputBitString, int& bitStringCounts);

private:
	void _write_jpeg_header(FILE* fp);
	void _write_byte_(unsigned char value, FILE* fp);
	void _write_word_(unsigned short value, FILE* fp);
	void _write_bitstring_(const BitString* bs, int counts, int& newByte, int& newBytePos, FILE* fp);
	void _write_(const void* p, int byteSize, FILE* fp);

public:
	JpegEncoder();
	~JpegEncoder();

private:
	//行方向上的子块置乱
	void lineBlockScramble(int* conParams, pixel ** imageData);
	//列方向上的子块置乱
	void rowBlockScramble(int* conParams, pixel ** imageData);
	//计算分组置乱后的位置
	int getScrambleIndex(int originalIndex, int groupLength, int totalLength);
	//生成置乱秘钥流,返回一个数组
	int * getScrambleParams(double originalValue, double controlParam, int paramAmount, int paramSection);
	//行方向上的量化系数置乱
	void lineCoeffScramble(int* scrambleConParams, quantCoeff ** imageCoeff);
	//列方向上的量化系数置乱
	void rowCoeffScramble(int* scrambleConParams, quantCoeff ** imageCoeff);
};


#endif
