#ifndef __JPEG_ENCODER_HEADER__
#define __JPEG_ENCODER_HEADER__


class JpegEncoder
{
	//���ص�ṹ��
	struct pixel
	{
		//����R����
		unsigned char R;
		//����G����
		unsigned char G;
		//����B����
		unsigned char B;
	};
	//����ϵ���ṹ��
	struct quantCoeff
	{
		//Y����
		short Y;
		//Cb����
		short Cb;
		//Cr����
		short Cr;
	};
public:
	/** �������� */
	void clean(void);

	/** ��BMP�ļ��ж�ȡ�ļ�����֧��24bit��������8�ı������ļ� */
	bool readFromBMP(const char* fileName);

	/** ѹ����jpg�ļ��У�quality_scale��ʾ������ȡֵ��Χ(0,100), ����Խ��ѹ������Խ��*/
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
	//�µ���ɫ�ռ�ת������
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
	//�з����ϵ��ӿ�����
	void lineBlockScramble(int* conParams, pixel ** imageData);
	//�з����ϵ��ӿ�����
	void rowBlockScramble(int* conParams, pixel ** imageData);
	//����������Һ��λ��
	int getScrambleIndex(int originalIndex, int groupLength, int totalLength);
	//����������Կ��,����һ������
	int * getScrambleParams(double originalValue, double controlParam, int paramAmount, int paramSection);
	//�з����ϵ�����ϵ������
	void lineCoeffScramble(int* scrambleConParams, quantCoeff ** imageCoeff);
	//�з����ϵ�����ϵ������
	void rowCoeffScramble(int* scrambleConParams, quantCoeff ** imageCoeff);
};


#endif
