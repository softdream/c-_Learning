#include <iostream>
#include <string> 
#include <fstream> 

#pragma pack(2)

namespace homework1 {
//bfType��2�ֽڣ��ļ����ͣ�
//bfSize��4�ֽڣ��ļ���С��
//bfReserved1��2�ֽڣ���������������Ϊ0��
//bfReserved2��2�ֽڣ���������������Ϊ0��
//bfOffBits��4�ֽڣ���ͷ��λͼ���ݵ�ƫ�ƣ�
struct BmpFileHeader {
	unsigned short bfType;
	unsigned long bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long bfOffBits;
};
typedef struct BmpFileHeader BmpFileHeader;

//biSize��4�ֽڣ���Ϣͷ�Ĵ�С����40��
//biWidth��4�ֽڣ�������Ϊ��λ˵��ͼ��Ŀ�ȣ�
//biHeight��4�ֽڣ�������Ϊ��λ˵��ͼ��ĸ߶ȣ�ͬʱ���Ϊ����˵��λͼ�����������ݱ�ʾ��ͼ������½ǵ����Ͻǣ������Ϊ��˵������
//biPlanes��2�ֽڣ�ΪĿ���豸˵����ɫƽ�������ܱ�����Ϊ1��
//biBitCount��2�ֽڣ�˵�������� / ��������ֵ��1��2��4��8��16��24��32��
//biCompression��4�ֽڣ�˵��ͼ���ѹ�����ͣ���õľ���0��BI_RGB������ʾ��ѹ����
//biSizeImages��4�ֽڣ�˵��λͼ���ݵĴ�С������BI_RGB��ʽʱ����������Ϊ0��
//biXPelsPerMeter����ʾˮƽ�ֱ��ʣ���λ������ / �ף��з���������
//biYPelsPerMeter����ʾ��ֱ�ֱ��ʣ���λ������ / �ף��з���������
//biClrUsed��˵��λͼʹ�õĵ�ɫ���е���ɫ��������Ϊ0˵��ʹ�����У�
//biClrImportant��˵����ͼ����ʾ����ҪӰ�����ɫ��������Ϊ0˵������Ҫ��
struct BmpFileInfoHeader {
	unsigned long biSize;
	unsigned long biWidth;
	unsigned long biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned long biCompression;
	unsigned long biSizeImages;
	long biXPelsPerMeter;
	long biYPelsPerMeter;
	unsigned long   biClrUsed;
	unsigned long   biClrImportant;
};
typedef struct BmpFileInfoHeader BmpFileInfoHeader;

/* ����BmpͼƬ���� */
class myBmpMap {
	typedef struct {
		unsigned char rgb;
	}EightBitRGB;
	typedef struct {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	}TweentyFourBitRGB;
public:
	myBmpMap( int height_, int width_, int colorType_ ): height(height_),
														width(width_),
														colorType(colorType_)
	{
		initParam();
	}
	myBmpMap() : height(100),
				width(100),
				colorType(1)
	{
		initParam();
	}
	~myBmpMap() {}

	void generateBMP( std::string type )
	{
		std::ofstream outfile;
		outfile.open( "./worktest1.bmp", std::ios::out|std::ios::binary | std::ios::app);
		if (!outfile.is_open()) {
			std::cerr << "Open File Faile ..." << std::endl;
			exit(-1);
		}
		std::cout << "bmpHeader size = " << sizeof(BmpFileHeader) << " bmpInfoHeader size = " << sizeof(bmpInfoHeader) << std::endl;
		unsigned char *header = new unsigned char[ sizeof(bmpHeader) + sizeof(bmpInfoHeader) ];
		memset( header, 0, sizeof(header) );
		memcpy( header, &bmpHeader, sizeof(bmpHeader));
		memcpy( &header[sizeof(bmpHeader)], &bmpInfoHeader, sizeof(bmpInfoHeader));

		/*for (int i = 0; i < 54; i++) {
			outfile << header[i];
		}*/
		outfile.write( (const char*)header, 54 );
		delete[] header;

		if (!type.compare("blackwhite")) {
			std::cout << "write a black white picture ..." << std::endl;
			EightBitRGB *data = new EightBitRGB[width * height];
			int i = 0;
			for (; i < width * height * 0.5; i++) {
				data[i].rgb = 0;
				//outfile << data[i].rgb;
			}
			for (; i < width * height; i++) {
				data[i].rgb = 255;
				//outfile << data[i].rgb;
			}


			delete[] data;
		}
		
		outfile.close();
	}

private:
	void initParam()
	{
		int Size = width * height * colorType;
		bmpHeader.bfType = 0X4d42;
		bmpHeader.bfSize = Size + sizeof(BmpFileHeader) + sizeof(BmpFileInfoHeader);
		std::cout << "bmpHeader.bfsize = " << bmpHeader.bfSize << std::endl;
		bmpHeader.bfReserved1 = 0;
		bmpHeader.bfReserved2 = 0;
		bmpHeader.bfOffBits = bmpHeader.bfSize - Size;

		bmpInfoHeader.biSize = sizeof(BmpFileInfoHeader);
		bmpInfoHeader.biWidth = width;
		bmpInfoHeader.biHeight = height;
		bmpInfoHeader.biPlanes = 1;
		bmpInfoHeader.biBitCount = colorType * 8;
		bmpInfoHeader.biCompression = 0;
		bmpInfoHeader.biSizeImages = Size;
		bmpInfoHeader.biXPelsPerMeter = 0;
		bmpInfoHeader.biYPelsPerMeter = 0;
		bmpInfoHeader.biClrUsed = 0;
		bmpInfoHeader.biClrImportant = 0;
	}
private:
	BmpFileHeader bmpHeader;
	BmpFileInfoHeader bmpInfoHeader;
	int height;
	int width;
	int colorType;
};

}

int main()
{
	homework1::myBmpMap bmp( 100, 100, 1 );
	bmp.generateBMP( "blackwhite" );
	return 0;
}