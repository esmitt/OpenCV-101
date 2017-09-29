#include <cstdlib>
#include <opencv2/opencv.hpp>

#pragma comment (lib, "opencv_world330d.lib")
using namespace cv;

void Sharpen(const Mat& inputImage, Mat& outputImage)
{
	CV_Assert(inputImage.depth() == CV_8U);

	//const int nChannels = inputImage.channels();
	//outputImage.create(inputImage.size(), inputImage.type());

	//for (int j = 1; j < inputImage.rows - 1; j++) 
	//{
	//	const uchar* previous = inputImage.ptr<uchar>(j - 1);
	//	const uchar* current = inputImage.ptr<uchar>(j);
	//	const uchar* next = inputImage.ptr<uchar>(j + 1);

	//	uchar* output = outputImage.ptr<uchar>(j);

	//	for (int i = nChannels; i < nChannels * (inputImage.cols - 1); i++)
	//	{
	//		*output++ =saturate_cast<uchar>(5 * current[i]
	//			- current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
	//	}
	//}
	//other way
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
	filter2D(inputImage, outputImage, inputImage.depth(), kernel);
	circle(outputImage, Point(200, 200), 50, Scalar(255, 128, 0), 3, LINE_8);
	RNG rng(0xFFFFFFFF);
	putText(outputImage, "abrakadabra", Point(100, 100), rng.uniform(0, 8), 1, Scalar(128,128,0), 2);
}

void testSharpen(cv::Mat image)
{
	Mat output;
	Sharpen(image, output);
	cv::imshow("Sharpen", output);

	cv::Mat M(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));
	std::cout << "M =" << std::endl << M << std::endl << std::endl;
}

void testNegative(cv::Mat image)
{
	Mat output(image);
	for (int y = 0; y < image.rows; y++)
		for(int x = 0; x < image.cols; x++)
		{
			output.at<Vec3b>(Point(x, y)) = Vec3b(255, 255, 255) - image.at<Vec3b>(Point(x, y));
		}
	cv::imshow("Negative", output);
}

void filter(cv::Mat image)
{
	Mat output(image);
	Mat kernel = Mat::ones(5, 5, CV_32F) / (5 * 5);
	filter2D(image, output, image.depth(), kernel);
	cv::imshow("Filter", output);
}

int main()
{
	std::string strImageName("image.jpeg");	//set image name
	//cv::Mat image = cv::imread(strImageName, cv::IMREAD_COLOR); //read the file
	cv::Mat image = cv::imread(strImageName); //read the file

	if (image.empty())	//check for invalid input
		return EXIT_FAILURE;

	//cv::namedWindow("OpenCV Basic Example", cv::WINDOW_AUTOSIZE); //create a window for display
	cv::Mat gray_image;
	cv::cvtColor(image, gray_image, cv::COLOR_RGB2GRAY);
	
	//cv::imwrite("gray.png", gray_image);
	
	cv::imshow("Original", image);
	//cv::imshow("Grey", gray_image);
	//testSharpen(image);
	//testNegative(image);
	filter(image);
	cv::waitKey(0);		//wait to press any key
	return EXIT_SUCCESS;
}