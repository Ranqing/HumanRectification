#include "../../Qing/qing_common.h"
#include "../../Qing/qing_dir.h"
#include "../../Qing/qing_io.h"
#include "../../Qing/qing_string.h"

int main(int argc, char * argv[])
{
    cout << "Usage: " << argv[0] << "../../../HumanDatas_20160711/Humans ../../../HumanDatas_20160711/Calib_Results A01 A02" << endl;
    cout << endl;
    if(argc < 5)
	{
        cout << "invalid arguments." << endl;
		return 0; 
	}

    string imageFolder =  argv[1];
    string calibFolder =  argv[2];
    cout << calibFolder << endl;
    cout << imageFolder << endl;
    string cam0 = argv[3];
    string cam1 = argv[4];
    string fn0 = imageFolder + "/imagelist_" + cam0 + ".txt";
    string fn1 = imageFolder + "/imagelist_" + cam1 + ".txt";
    vector<string> imageNames0(0), imageNames1(0);
    qing_read_txt(fn0, imageNames0);
    qing_read_txt(fn1, imageNames1);
    cout << "read image names done." << endl;

    string outfolder0 = "./" + cam0 + "/";
    string outfolder1 = "./" + cam1 + "/";
    string infoFolder = "./" + cam0 + cam1 + "_infos";
    qing_create_dir(outfolder0);
    qing_create_dir(outfolder1);
    qing_create_dir(infoFolder);
    cout << outfolder0 << endl;
    cout << outfolder1 << endl;
    cout << infoFolder << endl;

    string calibFile0 = calibFolder + "/calib_" + cam0 + ".yml";
    string calibFile1 = calibFolder + "/calib_" + cam1 + ".yml";
    string stereoFile = calibFolder + "/stereo_" + cam0 + cam1 + ".yml";
    Mat camera_matrix0, dist_coeffs0;
    Mat camera_matrix1, dist_coeffs1;
    Mat R0(3, 3, CV_64F);
    Mat R1(3, 3, CV_64F);
    Mat P0(3, 4, CV_64F);
    Mat P1(3, 4, CV_64F);
    Mat Q(4, 4, CV_64F);
    Size imageSize;
    qing_read_intrinsic_yml(calibFile0, camera_matrix0, dist_coeffs0);
    qing_read_intrinsic_yml(calibFile1, camera_matrix1, dist_coeffs1);
    qing_read_stereo_yml(stereoFile, R0, R1, P0, P1, Q, imageSize);
    cout << "read calib files done. " << endl;
    cout << "camera_matrix0: " << camera_matrix0 << endl;
    cout << "camera_matrix1: " << camera_matrix1 << endl;
    cout << "dist_coeffs0: " << dist_coeffs0 << endl;
    cout << "dist_coeffs1: " << dist_coeffs1 << endl;


    Mat mapx0 = Mat::zeros(imageSize, CV_32F);
    Mat mapy0 = Mat::zeros(imageSize, CV_32F);
    Mat mapx1 = Mat::zeros(imageSize, CV_32F);
    Mat mapy1 = Mat::zeros(imageSize, CV_32F);

    initUndistortRectifyMap(camera_matrix0, dist_coeffs0, R0, P0, imageSize, CV_32FC1, mapx0, mapy0);
    initUndistortRectifyMap(camera_matrix1, dist_coeffs1, R1, P1, imageSize, CV_32FC1, mapx1, mapy1);

    int nframes ;

    nframes = imageNames0.size();
    for(int i = 0; i < nframes; ++i)
    {
        string filename0 = imageFolder + "/" + cam0 + "/" + imageNames0[i];
        Mat view0 = imread(filename0, 1), new_view0;
        if(view0.data == NULL)
        {
            cerr << "failed to open " << filename0 << endl;
            continue;
        }
        remap(view0, new_view0, mapx0, mapy0, CV_INTER_LINEAR);

        string savefn = outfolder0 + imageNames0[i];
        imwrite(savefn, new_view0);
        cout << i << '\t';
        cout << savefn << endl;
    }

    nframes = imageNames1.size();
    for(int i = 0; i < nframes; ++i)
    {
        string filename1 = imageFolder + "/" + cam1 + "/" + imageNames1[i];
        Mat view1 = imread(filename1, 1), new_view1;
        if(view1.data == NULL)
        {
            cerr << "failed to open " << filename1 << endl;
            continue;
        }
        remap(view1, new_view1, mapx1, mapy1, CV_INTER_LINEAR);

        string savefn = outfolder1 + imageNames1[i];
        imwrite(savefn, new_view1);
        cout << i << '\t';
        cout << savefn << endl;
    }

    //generate stereo_.info
# if 0
    nframes = max(imageNames0.size(), imageNames1.size());
    for(int i = 0; i < nframes; ++i)
    {
        cout << i << '\t';
        savefn =  infoFolder + "/" + cam0 + cam1 + "_" + int2FormatString(i, 4, '0') + ".info";
        cout << savefn << endl;

        //if the number of images in two stereo cameras are not the same, then this will be wrong
        qing_write_stereo_info(savefn, i, cam0, cam1, imageSize, Point2f(0.f,0.f), Point2f(0.f, 0.f), 240.0f, 0.f, Q);
    }
# endif

    return 1;
}
