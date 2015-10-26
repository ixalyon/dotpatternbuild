#ifndef DOTPATTERNBUILDER_H
#define DOTPATTERNBUILDER_H

#include <opencv2/opencv.hpp>

class DotPatternBuilder
{
public:
    typedef const int ConstInt;
    ConstInt Width_Unit=5;
    ConstInt Height_Unit=5;
    ConstInt Height_Unit_Line=3;
    ConstInt Number_Base=6;
    ConstInt Digits=4;
    ConstInt Dim_X = 4;
    ConstInt Dim_Y = 4;
    ConstInt Blank_Line_Dim = 1;
    ConstInt Scale_X = 10;
    ConstInt Scale_Y = 10;
    const bool Center_Pixel =false;

    DotPatternBuilder();
    cv::Mat builder(int,int,cv::Point*);
    cv::Mat patternMethod();
    cv::Mat Pattern(cv::Point*);
    cv::Mat numberToPattern(int,bool);
    void matFill(cv::Mat_<float>*);
};



#endif // DOTPATTERNBUILDER_H
