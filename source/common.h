#pragma once

#include <direct.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

//C++ header
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include <limits>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

template<typename T>
std::string type2string(T num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}

template<typename T>
T string2type(std::string str)
{
	std::stringstream stream;

	int num = 0;
	stream << str;
	stream >> num;

	return num;	
}

