#include "dotpatternbuilder.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int  Width_Unit=5;
int  Height_Unit=5;
int  Height_Unit_Line=3;
int  Number_Base=6;
int  Digits=3;
int  Dim_X = 3;
int  Dim_Y = 3;
int  Blnk_Ln_Dim_X = 1;
int  Blnk_Ln_Dim_Y = 2;
int  Scale_X = 10;
int  Scale_Y = 10;
bool Center_Pixel =false;



bool flag=true;
Mat pattern;

DotPatternBuilder::DotPatternBuilder()
{

}

 Mat DotPatternBuilder::builder(const int lineHeight,const int lineWidth, Point* pos)
 {
     Mat tmp;
     int width=(Digits*(Dim_X+Blnk_Ln_Dim_X)+Blnk_Ln_Dim_X)*Scale_X;
     int height=(Dim_Y*2+Blnk_Ln_Dim_Y)*Scale_Y;
    //Add random noise and keep value constant throughout the runtime

     Mat patternTemplate(height,lineWidth,CV_32F,1);

     if(flag){
//         randn(patternTemplate,0,1);
         pattern=patternTemplate;
         flag=false;
     }
     //Taking copy of the original template
     patternTemplate=pattern.clone();


     for (int i = 0; i <= lineWidth/width; ++i) {
         pos->y=i;
         tmp= Pattern(pos);
         if(i==lineWidth/width){

             Mat roi(patternTemplate,Rect(width*i,0,lineWidth-width*i,height));
             Mat tmps(tmp,Rect(0,0,lineWidth-width*i,height));
             tmps.copyTo(roi);
             continue;
         }
         Mat roi(patternTemplate,Rect(width*i,0,width,height));
        std::cout<<lineWidth-width*i<<" "<<height<<std::endl;
         tmp.copyTo(roi);

     }

     return patternTemplate;
}

Mat DotPatternBuilder::Pattern(cv::Point* pos)
{
    int verticalPos=pos->x;
    int horizontalPos=pos->y;


    Mat tempLine, horLine,verLine;

    Mat breakLine(Dim_Y,Blnk_Ln_Dim_X,CV_32F,Scalar::all(0));


    verLine=breakLine.clone();
    for (int i = Digits-1; i > -1; --i) {
        tempLine=numberToPattern(verticalPos/std::pow(Number_Base,i),true);
        hconcat(verLine,tempLine ,verLine);
        hconcat(verLine,breakLine,verLine);
        verticalPos%=(int)std::pow(Number_Base,i);
    }

    horLine=breakLine.clone();
    for (int i = Digits-1; i > -1; --i) {
        tempLine=numberToPattern(horizontalPos/std::pow(Number_Base,i),true);
        hconcat(horLine,tempLine ,horLine);
        hconcat(horLine,breakLine,horLine);
        horizontalPos%=(int)std::pow(Number_Base,i);
    }

    Mat Line(Blnk_Ln_Dim_Y,verLine.size().width,CV_32F,Scalar::all(0));
//    resize(Line,Line,Size(),Scale_X,Blnk_Ln_Dim_Y,INTER_NEAREST);
//    resize(verLine,verLine,Size(),Scale_X,Scale_Y,INTER_NEAREST);
//    resize(horLine,horLine,Size(),Scale_X,Scale_Y,INTER_NEAREST);


    vconcat(verLine,Line,tempLine);
    vconcat(tempLine,horLine,tempLine);
    resize(tempLine,tempLine,Size(),Scale_X,Scale_Y,INTER_NEAREST);
    namedWindow("test");


//    std::cout<<tmp.row(0)<<std::endl;
//    std::cout<<tmp.row(1)<<std::endl;
//    std::cout<<tmp.row(2)<<std::endl;



    imshow("test",tempLine);
//    multiply(tmp,255,tmp);
//    imwrite("img.jpg",tmp);
    return tempLine;

}

Mat DotPatternBuilder::numberToPattern(int value,bool isVerticalLine)
{
    Mat_<float_t> Line = Mat::eye(Dim_Y, Dim_X, CV_32F);
    if(!isVerticalLine)
        flip(Line,Line,0);

    if(Center_Pixel)
        Line(1,1)=0;
    int val[]={0,1,1,2,2,1,1,0};

    value*=2;
    Line(val[value%8],val[value%8+1])=1;

    if(value>6){
        value+=4;
        Line(val[value%8],val[value%8+1])=1;
    }
//    std::cout<<"value :"<<value<<std::endl;

    return Line;
}

