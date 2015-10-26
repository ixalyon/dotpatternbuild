#ifndef DOTPATTERNBUILDER_H
#define DOTPATTERNBUILDER_H

#include <opencv2/opencv.hpp>

typedef const int extern ConstInt;
ConstInt Width_Unit=5;
ConstInt Height_Unit=5;
ConstInt Height_Unit_Line=3;
ConstInt Number_Base=6;
ConstInt Digits=3;
ConstInt Dim_X = 3;
ConstInt Dim_Y = 3;
ConstInt Blnk_Ln_Dim_X = 1;
ConstInt Blnk_Ln_Dim_Y = 2;
ConstInt Scale_X = 10;
ConstInt Scale_Y = 10;
const bool Center_Pixel =false;

class DotPatternBuilder
{
public:


    DotPatternBuilder();
    cv::Mat builder(int,int,cv::Point*);
    cv::Mat patternMethod();
    cv::Mat Pattern(cv::Point*);
    cv::Mat numberToPattern(int,bool);
    void matFill(cv::Mat_<float>*);
};



#endif // DOTPATTERNBUILDER_H
