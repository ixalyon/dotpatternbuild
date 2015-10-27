#ifndef DOTPATTERNBUILDER_H
#define DOTPATTERNBUILDER_H

#include <opencv2/opencv.hpp>

int extern Width_Unit;
int extern Height_Unit;
int extern Height_Unit_Line;
int extern Number_Base;
int extern Digits;
int extern Dim_X;
int extern Dim_Y;
int extern Blnk_Ln_Dim_X;
int extern Blnk_Ln_Dim_Y;
int extern Scale_X;
int extern Scale_Y;
int extern Scale_BL_Y;
bool extern Center_Pixel;


int extern LINE_WIDTH;
int extern LINE_HEIGHT;
int extern RULE_NUMBER;
int extern BLANK_HEIGHT;

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
