#include "dotpatternbuilder.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;




bool flag=true;
Mat pattern;

DotPatternBuilder::DotPatternBuilder()
{

}

 Mat DotPatternBuilder::builder(const int lineHeight,const int lineWidth, Point* pos)
 {
    //Add random noise and keep value constant throughout the runtime
    Mat patternTemplate(lineHeight*5,lineWidth,CV_32F,1);;
    if(flag){
        randn(patternTemplate,0,1);
        pattern=patternTemplate;
        flag=false;
    }
    //Taking copy of the original template
    patternTemplate=pattern.clone();

    int width=(Digits*(Dim_X+Blank_Line_Dim)+Blank_Line_Dim)*Scale_X;
    std::cout<<"width :"<<width<<std::endl;
    Mat tmp= Pattern(pos);
    return patternTemplate;
}

Mat DotPatternBuilder::Pattern(cv::Point* pos)
{
    int verticalPos=pos->x;
    int horizontalPos=pos->y;


    Mat tempLine, horLine,verLine;

    Mat breakLine(Dim_Y,Blank_Line_Dim,CV_32F,Scalar::all(0));


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

    Mat Line(Blank_Line_Dim*2,verLine.size().width,CV_32F,Scalar::all(0));

    vconcat(verLine,Line,tempLine);
    vconcat(tempLine,horLine,tempLine);

    namedWindow("test");
    resize(tempLine,tempLine,Size(),Scale_X,Scale_Y,INTER_NEAREST);
    std::cout<<tempLine.size().width<<std::endl;

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

