#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "dotpatternbuilder.h"

using namespace std;
using namespace cv;


int  LINE_HEIGHT( 2);
int  RULE_NUMBER (20);
int  BLANK_HEIGHT (30);

void showImage();



int x = 1;
int y = 1;

void on_trackbar( int, void* )
{
//    Scale_X=x;
//    Scale_Y=y;
    DotPatternBuilder dbp;
//    Mat pattern = dbp.Pattern(x);

//    imshow("test",pattern);

    dbp.showImage();
}

int main( )
{
    namedWindow( "test", CV_WINDOW_AUTOSIZE );

//    showImage();

    namedWindow("Display");

    createTrackbar("X", "Display", &x, 500,on_trackbar);

//    createTrackbar("Y", "Display", &y, 10,on_trackbar);
    on_trackbar( x, 0);
//    on_trackbar( y, 0 );



    waitKey(0);              // Wait for a keystroke in the window
    return 0;
}


