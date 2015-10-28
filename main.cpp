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

int  LINE_WIDTH(510);
int  LINE_HEIGHT( 2);
int  RULE_NUMBER (20);
int  BLANK_HEIGHT (40);

void showImage();



int x = 1;
int y = 1;

void on_trackbar( int, void* )
{
//    Scale_X=x;
//    Scale_Y=y;
    DotPatternBuilder dbp;
    Mat pattern = dbp.Pattern(new Point(x,0));
    imshow("Display",pattern);

//    showImage();
}

int main( )
{
    namedWindow( "Display", CV_WINDOW_AUTOSIZE );

//    showImage();



    createTrackbar("X", "Display", &x, 16,on_trackbar);

//    createTrackbar("Y", "Display", &y, 10,on_trackbar);
    on_trackbar( x, 0);
//    on_trackbar( y, 0 );



    waitKey(0);              // Wait for a keystroke in the window
    return 0;
}

void showImage()
{

    DotPatternBuilder dbp;
    Mat pattern;
    Mat lineBlank(BLANK_HEIGHT*Scale_Y,LINE_WIDTH,CV_32F,Scalar(1));
    Mat lineBlack(LINE_HEIGHT*(Scale_Y!=1?Scale_Y-1:Scale_Y),LINE_WIDTH,CV_32F,Scalar(0));
    Mat lineWhite(1,LINE_WIDTH,CV_32F,Scalar(1));
    Mat lineTinyBlack(1,LINE_WIDTH,CV_32F,Scalar(0));

    Mat image = lineBlack.clone();
    vconcat(image,lineWhite,image);

    for (int i = 0; i < RULE_NUMBER; ++i) {
        pattern = dbp.builder(LINE_HEIGHT,LINE_WIDTH,new cv::Point(i,0));
        Mat roi=pattern.rowRange(pattern.size().height/2,pattern.size().height/2+1);
        roi=1;
        vconcat(image,lineTinyBlack,image);
        vconcat(image,pattern,image);
        vconcat(image,lineTinyBlack,image);
        vconcat(image,lineWhite,image);
        vconcat(image,lineBlack,image);
        vconcat(image,lineBlank,image);
        vconcat(image,lineBlack,image);
        vconcat(image,lineWhite,image);
    }
    imshow( "Display", image );
    stringstream ss;
    ss<<"pattern"<<Scale_X<<"X"<<Scale_Y<<".pbm";
    string s=ss.str();
    imwrite(s,image*255);

//   return image;
}
