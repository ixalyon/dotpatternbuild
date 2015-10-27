#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "dotpatternbuilder.h"

using namespace std;
using namespace cv;

int  LINE_WIDTH(500);
int  LINE_HEIGHT( 2);
int  RULE_NUMBER (10);
int  BLANK_HEIGHT (20);

void showImage();



int x = 0;
int y = 0;
void on_trackbar( int, void* )
{
 showImage();
}

int main( )
{
//    namedWindow( "Display window", CV_WINDOW_AUTOSIZE );

    showImage();



    createTrackbar("X", "test", &x, 300,on_trackbar);

    createTrackbar("Y", "test", &y, 215,on_trackbar);
    on_trackbar( x, 0 );
    on_trackbar( y, 0 );
    DotPatternBuilder dbp;
    Mat pattern = dbp.builder(LINE_HEIGHT,LINE_WIDTH,new cv::Point(x,y));

    waitKey(0);              // Wait for a keystroke in the window
    return 0;
}

void showImage()
{

    DotPatternBuilder dbp;
    Mat pattern;
    Mat lineBlank(BLANK_HEIGHT ,LINE_WIDTH,CV_32F,Scalar(1));
    Mat lineBlack(LINE_HEIGHT,LINE_WIDTH,CV_32F,Scalar(0));
    Mat lineWhite(LINE_HEIGHT,LINE_WIDTH,CV_32F,Scalar(0.5));

    Mat image = lineBlank.clone();

    for (int i = 0; i < RULE_NUMBER; ++i) {
        pattern = dbp.builder(LINE_HEIGHT,LINE_WIDTH,new cv::Point(i,0));
        Mat roi=pattern.rowRange(pattern.size().height/2-1,pattern.size().height/2+1);
        roi=1;
        vconcat(image,lineBlack,image);
        vconcat(image,pattern,image);
        vconcat(image,lineBlack,image);
        vconcat(image,lineBlank,image);
    }
    imshow( "Display window", image );
    stringstream ss;
    ss<<"pattern"<<Scale_X<<"X"<<Scale_Y<<".png";
    string s=ss.str();
    imwrite(s,image*255);

//   return image;
}
