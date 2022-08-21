#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Configs.hpp"
class Image {
    private:
        Mat kernel;
        Mat image;
        Mat makebinary(Mat,int);
        Mat padding(Mat , int , int , string );
        Mat define_kernel(int , int , string );
        uchar sumIndex;
        vector<vector<int>> matrix;
        int initial_value = 1;
        double ratio = 1 ;
        int size = 10;
        int threshold = 10;
        int Mode;
        int ChoiceKernelMoD;
        int ChoiceConvolvemulti ;
        int PopKernel;
        int binary[8];
        int Mod;
        Mat srcImage;
        Mat decimal[8];
        Mat temp;
        int number;
        int pic[8];
        double alpha;


        
    public:
        Image(int);
        void loadImage(string);
        void applyFilter();
        void setKernel();
        void MenuKernel();
        void PopularKernel(); 
        void ZeroKernel();
        void convolve(Mat , Mat &, int , int , string , string );
        void ConvolveGuassianBlur();
        int  imageThresholding();
        void decimalToBinary(int number);
        void imageReader();
        void imageBitPlane();
        void webcamBitPlane(int );
        void webcamDisplay();
        void imageDisplay();
    
};

#endif // IMAGE_HPP