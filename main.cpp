#include<opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include<vector>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

	// ��ȡRBGͼƬ��ת��Labģʽ
	Mat bgr_image = imread("test1.png");
	if (!bgr_image.rows){
		cout << "imread failed!"<< endl;
		return 0;
	}
	Mat lab_image;
	cvtColor(bgr_image, lab_image, CV_BGR2Lab);

	// ��ȡLͨ��
	vector<Mat> lab_planes(3);
	split(lab_image, lab_planes);

	// CLAHE �㷨
	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(4);
	Mat dst;
	clahe->apply(lab_planes[0], dst);
	dst.copyTo(lab_planes[0]);
	merge(lab_planes, lab_image);

	// �ָ�RGBͼ��
	Mat image_clahe;
	cvtColor(lab_image, image_clahe, CV_Lab2BGR);

	// ��ӡ���
	imshow("ԭʼͼƬ", bgr_image);
	imshow("CLAHE����", image_clahe);
	waitKey();

	return 0;
}