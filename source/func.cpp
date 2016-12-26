//#include "func.h"

//bool readStringList(const string listname, vector<string>& list)
//{
//	list.resize(0);
//	FileStorage fs(listname, FileStorage::READ);
//	if (!fs.isOpened())
//		return false;

//	FileNode n = fs.getFirstTopLevelNode();
//	FileNodeIterator it = n.begin(), it_end = n.end();
//	for (; it != it_end; it++)
//		list.push_back((string)* it);

//	return true;
//}

//void readIntrinsicFile(string intrinsicFile, float& squareSize, Mat& intrinsic, Mat& discoeffs)
//{
//	FileStorage fs(intrinsicFile, FileStorage::READ);

//	fs["Square_Size"] >> squareSize;
//	fs["Camera_Matrix"] >> intrinsic;
//	fs["Distortion_Coefficients"] >> discoeffs;

//	fs.release();
//}

//void readStereoFile(string stereoFile, Size& imageSize, Mat& R1, Mat& R2, Mat& P1, Mat& P2, Mat& Q)
//{
//	FileStorage fs(stereoFile, FileStorage::READ);

//	fs["Image_Width"] >> imageSize.width;
//	fs["Image_Height"] >> imageSize.height;
//	fs["Q"] >> Q;
//	fs["R1"] >> R1 ;
//	fs["R2"] >> R2;
//	fs["P1"] >> P1;
//	fs["P2"] >> P2;
	
//	fs.release();
 	
//}
