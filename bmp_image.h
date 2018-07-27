class BmpImage
{
public:
	int getImageHeight();
	int getImageWidth();
private:
	//图像高度
	int imageHeight;
	//图像宽度
	int imageWidth;
	//图像像素数据
	unsigned char imageData[512][512];
};
