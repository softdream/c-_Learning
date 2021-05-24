#include<opencv2/opencv.hpp>
#include<iostream>
#include <vector>

#define RADIUS_BIAS 20
#define SHIFT_BIAS 10

#define PI 3.1415926

std::vector<cv::Mat> roiVec;

void RGB2HSV(double red, double green, double blue, double& hue, double& saturation, double& intensity)
{

	double r, g, b;
	double h, s, i;

	double sum;
	double minRGB, maxRGB;
	double theta;

	r = red / 255.0;
	g = green / 255.0;
	b = blue / 255.0;

	minRGB = ((r < g) ? (r) : (g));
	minRGB = (minRGB < b) ? (minRGB) : (b);

	maxRGB = ((r > g) ? (r) : (g));
	maxRGB = (maxRGB > b) ? (maxRGB) : (b);

	sum = r + g + b;
	i = sum / 3.0;

	if (i < 0.001 || maxRGB - minRGB < 0.001)
	{

		h = 0.0;
		s = 0.0;
	}
	else
	{
		s = 1.0 - 3.0*minRGB / sum;
		theta = sqrt((r - g)*(r - g) + (r - b)*(g - b));
		theta = acos((r - g + r - b)*0.5 / theta);
		if (b <= g)
			h = theta;
		else
			h = 2 * PI - theta;
		if (s <= 0.01)
			h = 0;
	}

	hue = (int)(h * 180 / PI);
	saturation = (int)(s * 100);
	intensity = (int)(i * 100);
}

void fillHole(const cv::Mat srcBw, cv::Mat &dstBw)
{
	cv::Size m_Size = srcBw.size();
	cv::Mat Temp = cv::Mat::zeros(m_Size.height + 2, m_Size.width + 2, srcBw.type());
	srcBw.copyTo(Temp(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1)));

	cv::floodFill(Temp, cv::Point(0, 0), cv::Scalar(255));

	cv::Mat cutImg;
	Temp(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1)).copyTo(cutImg);

	dstBw = srcBw | (~cutImg);
}

//�ж�rect1��rect2�Ƿ��н���  
bool isInside(cv::Rect rect1, cv::Rect rect2)
{
	cv::Rect t = rect1&rect2;
	if (rect1.area() > rect2.area())
	{
		return false;
	}
	else
	{
		if (t.area() != 0)
			return true;
	}
}

int main(int agrc, char** agrv)
{
	cv::Mat src1, dst;
	src1 = cv::imread("5.jpg");
	cv::resize(src1, src1, cv::Size(600, 600));
	cv::imshow("ԭͼ", src1);
	//src1.copyTo(dst);

	cv::cvtColor(src1, dst, cv::COLOR_BGR2HSV);
	cv::imshow( "HSV", dst );

	//ֱ��ͼ���⻯
	std::vector<cv::Mat> hsvSplit;
	cv::split(dst, hsvSplit);
	//cv::equalizeHist(hsvSplit[0], hsvSplit[0]);
	//cv::equalizeHist(hsvSplit[1], hsvSplit[1]);
	cv::equalizeHist(hsvSplit[2], hsvSplit[2]);
	cv::merge(hsvSplit, dst);
	cv::imshow("���⻯", dst);

	cv::cvtColor( dst, dst, cv::COLOR_HSV2BGR );
	cv::imshow("���⻯֮��", dst);
	/*cv::Mat imgThresholded;
	cv::inRange(dst, cv::Scalar(150, 70, 50), cv::Scalar(180, 255, 220), imgThresholded); //Threshold the image
	//cv::inRange(dst, cv::Scalar(50, 50, 50), cv::Scalar(255, 255, 250), imgThresholded); //Threshold the image
	cv::imshow( "��ɫ��ȡ1",imgThresholded );*/

	//��ɫɫ�ʷָ�
	int width = dst.cols;//ͼ����  
	int height = dst.rows;//ͼ��߶�  
	double B = 0.0, G = 0.0, R = 0.0, H = 0.0, S = 0.0, V = 0.0;
	cv::Mat matRgb = cv::Mat::zeros(dst.size(), CV_8UC1);
	int x, y; //ѭ��  
	for (y = 0; y < height; y++){
		for (x = 0; x < width; x++){
			// ��ȡBGRֵ  
			B = dst.at<cv::Vec3b>(y, x)[0];
			G = dst.at<cv::Vec3b>(y, x)[1];
			R = dst.at<cv::Vec3b>(y, x)[2];
			RGB2HSV(R, G, B, H, S, V);
			//��ɫ��Χ  
			if ((H >= 330 && H <= 360 || H >= 0 && H <= 10) && S >= 21 && S <= 100 && V > 16 && V < 99) {//H���ܵ���10��H���ܴ���344,S���ܸ���21��V���ܱ�{
				matRgb.at<uchar>(y, x) = 255;
			}
		}
	}
	cv::imshow("��ɫ��ȡ", matRgb);


	//������ (ȥ��һЩ���)
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
	cv::morphologyEx(matRgb, matRgb, cv::MORPH_OPEN, element);

	cv::imshow("������", matRgb);
	//�ղ��� (����һЩ��ͨ��)
	cv::Mat element2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
	cv::morphologyEx(matRgb, matRgb, cv::MORPH_CLOSE, element2);
	cv::imshow("�ղ���", matRgb);

	fillHole(matRgb, matRgb);//���    
	cv::imshow("���", matRgb);

	cv::Mat matRgbCopy;
	matRgb.copyTo(matRgbCopy);

	//������
	std::vector<std::vector<cv::Point>>contours; //����    
	std::vector<cv::Vec4i> hierarchy;//�ֲ�    
	findContours(matRgb, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));//Ѱ������    
	std::vector <std::vector < cv::Point >> contours_poly(contours.size());  //���ƺ�������㼯    
	std::vector<cv::Rect> boundRect(contours.size());  //��Χ�㼯����С����vector    
	std::cout << "����������contours size = " << contours.size() << std::endl;
	//������
	for (int i = 0; i < contours.size(); i++){
		approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true); //�Զ�����������ʵ����ƣ�contours_poly[i]������Ľ��Ƶ㼯    
		boundRect[i] = cv::boundingRect(cv::Mat(contours_poly[i])); //���㲢���ذ�Χ�����㼯����С����       
	}

	//����ȡ������������ȥ�룬ɸѡ����ͨ��־
	cv::Mat drawing = cv::Mat::zeros(matRgb.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++){
		cv::Rect rect = boundRect[i];
		//���Ƚ���һ�������ƣ�ɸѡ������

		//�����������ڲ��������ž��Σ��򽫱�������С����ȡ��
		bool inside = false;
		for (int j = 0; j < contours.size(); j++){
			cv::Rect t = boundRect[j];
			if (rect == t)
				continue;
			else if (isInside(rect, t)){
				inside = true;
				break;
			}
		}
		if (inside)
			continue;

		//�߿������  
		float ratio = (float)rect.width / (float)rect.height;
		std::cout << "��߱��ʣ�ratio = " << ratio << std::endl;
		//�����������       
		float Area = (float)rect.width * (float)rect.height;
		std::cout << "���������area = " << Area << std::endl;
		float dConArea = (float)contourArea(contours[i]);
		float dConLen = (float)arcLength(contours[i], 1);
		if (dConArea < 700)
			continue;
		if (ratio > 1.3 || ratio < 0.4)
			continue;
		if (Area < 10000)
			continue;
		//������ʶ���
		cv::Scalar color = (0, 0, 255);//������    
		drawContours(drawing, contours_poly, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		rectangle(src1, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);

		cv::imshow("����", drawing);

		//Harris�ǵ��⣬ȥ��������������
		cv::Mat grayImg, dstImg, normImg, scaledImg;
		cvtColor(drawing, grayImg, cv::COLOR_BGR2GRAY);
		cv::cornerHarris(grayImg, dstImg, 2, 3, 0.04);

		//��һ����ת��
		cv::normalize(dstImg, normImg, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
		cv::convertScaleAbs(normImg, scaledImg);

		int harrisNum = 0;
		for (int j = 0; j < normImg.rows; j++){
			for (int i = 0; i < normImg.cols; i++){
				if ((int)normImg.at<float>(j, i) > 160){
					cv::circle(scaledImg, cv::Point(i, j), 4, cv::Scalar(0, 10, 255), 2, 8, 0);
					harrisNum++;
				}
			}
		}
		if (harrisNum > 33)//���ǵ���Ŀ����33������Դ�����
			continue;

		cv::imshow("���", src1);
		//imwrite("G:\\courseStudy\\opencv\\homework1\\homework-1\\result1.jpg", srcImg);//�������յļ��ʶ����  
	}


	cv::waitKey(0);
	return 1;
}