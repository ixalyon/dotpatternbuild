#include "dotpatternbuilder.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <sstream>

using namespace cv;

int  Width_Unit=5;
int  Height_Unit=5;
int  Height_Unit_Line=3;
int  Number_Base=18;
int  Digits=3;
int  Dim_X = 3;
int  Dim_Y = 3;
int  Blnk_Ln_Dim_X = 1;
int  Blnk_Ln_Dim_Y = 3;
int  Scale_X = 3;
int  Scale_Y = 3;
int  Scale_BL_Y = 5;
bool Center_Pixel =true;
int  width=(Digits*(Dim_X+Blnk_Ln_Dim_X)+Blnk_Ln_Dim_X*4)*Scale_X;
int  height=(Dim_Y)*Scale_Y/*+Blnk_Ln_Dim_Y*/;
int  LINE_WIDTH=(1000/width)*width;
//int  LINE_WIDTH=((Dim_Y+LINE_HEIGHT*2+BLANK_HEIGHT)*Scale_Y+4)*RULE_NUMBER/10*7;
int  BLANK_HEIGHT=20;
int  RULE_NUMBER = LINE_WIDTH/7*10/((Dim_Y+LINE_HEIGHT*2+BLANK_HEIGHT)*Scale_Y+4);






bool flag=true;
Mat pattern;

DotPatternBuilder::DotPatternBuilder()
{
    std::cout<<"width :  "<<BLANK_HEIGHT<<std::endl;

}

void DotPatternBuilder::showImage()
{

    int roiHeight=0,upperB=4,lowerB=2;
    Mat pattern;
    Mat lineBlank(BLANK_HEIGHT*Scale_Y,LINE_WIDTH,CV_32F,Scalar(1));
    Mat lineBlack(LINE_HEIGHT*/*(Scale_Y!=1?Scale_Y-1:*/Scale_Y/*)*/,LINE_WIDTH,CV_32F,Scalar(0));

    Mat image = lineBlack.clone();
    roiHeight=image.size().height;
    roiLines(image.rowRange(0,lowerB));

    for (int i = 0; i < RULE_NUMBER; ++i) {
        pattern = builder(LINE_WIDTH,i*LINE_WIDTH/width);
        vconcat(image,pattern,image);
        vconcat(image,lineBlack,image);
        roiHeight=image.size().height;
        roiLines(image.rowRange(roiHeight-lowerB,roiHeight));
        vconcat(image,lineBlank,image);
//        if(i==RULE_NUMBER-1)
//            continue;
        roiHeight=image.size().height;
        vconcat(image,lineBlack,image);
        roiLines(image.rowRange(roiHeight,roiHeight+lowerB));
    }
    for (int i = 0; i < LINE_WIDTH/width; ++i)
    {
//        Mat roi(image,Rect(width*i,0,width,height));
//        roiLines(roi.colRange(roi.size().width-3,roi.size().width));
        roiLines(image.colRange(width*i,width*i+2));
    }
    imshow( "Display", image );
    imwrite("pattern.png",image*255);
    imwrite("pattern.bmp",image*255);
    imwrite("pattern.pbm",image*255);

//   return image;
}

 Mat DotPatternBuilder::builder(const int lineWidth, int pos)
 {
//     std::cout<<pos<<std::endl;
     Mat tmp;

    //Add random noise and keep value constant throughout the runtime

     Mat patternTemplate(height,lineWidth,CV_32F,1);

     if(flag){
//         randn(patternTemplate,0,1);
         pattern=patternTemplate;
         flag=false;
     }
     //Taking copy of the original template
     patternTemplate=pattern.clone();


     for (int i = 0; i < lineWidth/width; ++i) {
//         pos=i;
         tmp= Pattern(pos+i);
         if(i==lineWidth/width){

             Mat roi(patternTemplate,Rect(width*i,0,lineWidth-width*i,height));
             Mat tmps(tmp,Rect(0,0,lineWidth-width*i,height));
             tmps.copyTo(roi);
             roiLines(roi.colRange(1,2));
             continue;
         }

         Mat roi(patternTemplate,Rect(width*i,0,width,height));
//        std::cout<<lineWidth-width*i<<" "<<height<<std::endl;
         tmp.copyTo(roi);
//         roiLines(roi.colRange(roi.size().width-3,roi.size().width-2));
//         roiLines(roi.colRange(roi.size().width-3,roi.size().width));
//         roiLines(roi.colRange(2,3));
//         roiLines(roi.colRange(0,1));

     }

     return patternTemplate;
}

void DotPatternBuilder::roiLines(Mat tmp){
    tmp=1;
}

Mat DotPatternBuilder::Pattern(int pos)
{
    int verticalPos=pos;

    Mat tempLine, verLine;

    Mat breakLine(Dim_Y,Blnk_Ln_Dim_X,CV_32F,Scalar::all(0));

    verLine=breakLine.clone();
    hconcat(verLine,breakLine,verLine);
    for (int i = Digits-1; i > -1; --i) {
        tempLine=numberToPattern(verticalPos/std::pow(Number_Base,i));
        hconcat(verLine,tempLine ,verLine);
        hconcat(verLine,breakLine,verLine);
        verticalPos%=(int)std::pow(Number_Base,i);
    }
    hconcat(verLine,breakLine,verLine);
    hconcat(verLine,breakLine,verLine);



    Mat Line(Blnk_Ln_Dim_Y,verLine.size().width*Scale_X,CV_32F,Scalar::all(0));
    resize(verLine,verLine,Size(),Scale_X,Scale_Y,INTER_NEAREST);

    return verLine;

}

Mat DotPatternBuilder::numberToPattern(int value)
{
    Mat_<float_t> Line = Mat::eye(Dim_Y, Dim_X, CV_32F);
    if(!Center_Pixel)
        Line(1,1)=0;
    if(value>7)
    {
        flip(Line,Line,0);
        value%=8;
    }
    if(value==0)
        return Line;
    value--;

    int val[]={0,1,  1,2,  2,1,  1,0};

    value*=2;
    Line(val[value%8],val[value%8+1])=1;

    if(value>6){
        value+=6;
        Line(val[value%8],val[value%8+1])=1;
    }

    return Line;
}

