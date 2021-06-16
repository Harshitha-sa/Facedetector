#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int preloaded() {
	CascadeClassifier faceDetection;
	if (!faceDetection.load("C:\\Users\\Harshitha\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml")) {
		cout << "\n file not loaded properly";
		exit(0);
	}
	char path[100];
	cout << "\nEnter the image path for face detection: ";
	getchar();
	cin.getline(path, 100);
	Mat img = imread(path, IMREAD_UNCHANGED);

	if (img.empty())
		cout << "\n img is not loaded properly";
	else
	{
		cout << "\n img is found";
		cout << "\n img processing.....";

		vector<Rect> faces;
		faceDetection.detectMultiScale(img, faces);

		for (int i = 0; i < faces.size(); i++) {
			//Point pt1(faces[i].x + faces[i].y);
			//Point pt2((faces[i].x + faces[i].height), (faces[i].y + faces[i].width));
			//rectangle(img, pt1, pt2, Scalar(255, 255, 0), 2, 8, 0);
			Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			ellipse(img, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 255, 0), 2);
		}

		//imshow("facedetection.jpg", img);
		imwrite("E:\\trialproj\\output.jpg", img);
		String wn = "output";
		imshow(wn, img);
		waitKey(0);
		destroyWindow(wn);
		cout << "\n face detected";
	}
	return 0;
}
void webloaded() {
	CascadeClassifier face_detection;
	if (!face_detection.load("C:\\Users\\Harshitha\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml")) {
		cout << "file not loaded properly\n";
		exit(0);
	}
	VideoCapture cap(0);
	if (cap.isOpened() == false) {
		cout << "cannot open the video camera\n";
		cin.get();
		exit(0);
	}
	int frame_width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
	int frame_height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));

	Size frame_size(frame_width, frame_height);
	int frames_per_second = 10;

	VideoWriter oVideoWriter("D:/MyVideo.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), frames_per_second, frame_size, true);

	if (oVideoWriter.isOpened() == false) {
		cout << "cannot save the video to a file" << endl;
		cin.get();
		exit(0);
	}

	String window_name = "My camera feed";
	namedWindow(window_name);

	while (1)
	{
		Mat frame;
		bool isSuccess = cap.read(frame);
		if (isSuccess == false) {
			cout << "video cam disconnected" << endl;
			cin.get();
			break;
		}
		vector<Rect> faces;
		face_detection.detectMultiScale(frame, faces, 1.3, 5);
		for (int i = 0; i < faces.size(); i++)
		{
			//Point pt1(faces[i].x - 50 + faces[i].y - 100);
			//Point pt2((faces[i].x + faces[i].height) - 50, (faces[i].y + faces[i].width));
			//rectangle(frame, pt1, pt2, Scalar(255, 255, 0));
			Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 255, 0), 2);

		}
		oVideoWriter.write(frame);
		imshow(window_name, frame);
		if (waitKey(10) == 27) {
			cout << "escape key pressed by the user.Stop playing the video" << endl;
			getchar();
			oVideoWriter.release();
			destroyWindow(window_name);
			break;
		}
		oVideoWriter.release();
	}
}
int main() {
	int n;
	while (1) {
		cout << "   1. pre loaded face recognition\n";
		cout << "   2. web cam face recognition\n";
		cout << "   3.exit\n";
		cout << "   select any:";
		cin >> n;
		switch (n) {
		case 1:
			preloaded();
			break;
		case 2:
			webloaded();
			break;
		case 3:
			return 0;
			break;
		default:
			cout << "wrong choice \n";
		}
	}
	return 0;
}