class BmpImage
{
public:
	int getImageHeight();
	int getImageWidth();
private:
	//ͼ��߶�
	int imageHeight;
	//ͼ����
	int imageWidth;
	//ͼ����������
	unsigned char imageData[512][512];
};
