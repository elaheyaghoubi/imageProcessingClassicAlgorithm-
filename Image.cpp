#include "Image.hpp"

Image::Image(int option)
{

    switch (option)
    {
    // -- Kernel Menu
    case 1:
        MenuKernel();
        break;

    //-- image thresholding
    case 2:
        imageThresholding();
        break;

    //-- bit plane slicing for image
    case 3:
        imageReader();
        imageBitPlane();
        imageDisplay();
        break;

    //-- bit plane slicing for webcam
    case 4:
        webcamDisplay();
        webcamBitPlane(Mod);
        break;
    }
}

void Image::MenuKernel()
{

    cout << "\n Enter Your Choice \n";
    cout << " 1 -> Popular Kernels\n 2-> Manual Set Kernel \n ";
    cin >> ChoiceKernelMoD;
    switch (ChoiceKernelMoD)
    {
    case 1:
        PopularKernel();
        break;
    default:
        cout << "\n Your Number is false \n";
        break;
    }
}
void Image::PopularKernel()
{

    size = 3;
    ChoiceConvolvemulti = -1;
    cout << "\n 1->Identity Kernel\n 2-> Edge detection \n 3-> Sharpen Kernel \n 4-> Box Blur \n";
    cin >> PopKernel;
    switch (PopKernel)
    {
    case 1:
        kernel = (Mat_<uchar>(3, 3) << 0, 0, 0,
                  0, 1, 0,
                  0, 0, 0);
        break;
    case 2:
        kernel = (Mat_<uchar>(3, 3) << -1, -1, -1,
                  -1, 8, -1,
                  -1, -1, -1);
        break;
    case 3:
        kernel = (Mat_<uchar>(3, 3) << 0, -1, 0,
                  -1, 5, -1,
                  0, -1, 0);
        break;
    case 4:
        kernel = (Mat_<uchar>(3, 3) << 1, 1, 1,
                  1, 1, 1,
                  1, 1, 1);
        ratio = (double)1 / 9;
        break;
    default:
        break;
    }
}

int Image::imageThresholding()
{

    VideoCapture camera(0);
    Mat image;
    namedWindow("Binary", WINDOW_AUTOSIZE);
    int threshold = size;
    createTrackbar("Threshold", "Binary", &threshold, 255);
    while (1)
    {
        camera >> image;
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        Mat binary = makebinary(gray, threshold);
        imshow("Binary", binary);
        char a = waitKey(33);
        if (a == 27)
        {
            break;
        }
    }
    return 0;
}

Mat Image::makebinary(Mat image, int threshold)
{

    Mat result(image.size(), CV_8UC1);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if (image.at<uchar>(i, j) > threshold)
            {
                result.at<uchar>(i, j) = 255; // Make pixel white
            }
            else
            {
                result.at<uchar>(i, j) = 0; // Make pixel black
            }
        }
    }
    return result;
}

void Image::loadImage(string picturePath)
{

    image = imread(picturePath, 0);
    cout << "input size : " << image.rows << "x" << image.cols << endl;
}

void Image::applyFilter()
{

    Mat src((image.rows - size + 1), (image.cols - size + 1), image.type());
    int dx = size / 2;
    int dy = size / 2;
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            sumIndex = 0;
            if (ChoiceConvolvemulti == 1)
            {
                for (int k = 0; k < matrix.size(); k++)
                {
                    for (int l = 0; l < matrix[k].size(); l++)
                    {

                        int x = j - dx + l;
                        int y = i - dy + k;
                        if (x >= 0 && x < src.cols && y >= 0 && y < src.rows)
                        {
                            sumIndex += matrix[k][l] * image.at<uchar>(y, x) * ratio;
                        }
                    }
                }
            }
            if (ChoiceConvolvemulti == -1)
            {

                for (int k = 0; k < size; k++)
                {
                    for (int l = 0; l < size; l++)
                    {
                        int x = j - dx + l;
                        int y = i - dy + k;
                        if (x >= 0 && x < src.cols && y >= 0 && y < src.rows)
                        {
                            sumIndex += kernel.at<uchar>(k, l) * image.at<uchar>(y, x) * ratio;
                        }
                    }
                }
            }
            src.at<uchar>(i, j) = saturate_cast<uchar>(sumIndex);
        }
    }
    cout << "output size : " << src.rows << "x" << src.cols << endl;
    imshow("Output", src);
    waitKey(0);
    destroyAllWindows();
}

void Image::decimalToBinary(int number)
{

    for (int i = 0; i < 8; i++)
        binary[i] = 0;
    int i = 0;
    while (number != 0)
    {
        binary[i] = number % 2;
        number = number / 2;
        i++;
    }
}

void Image::imageReader()
{
    srcImage = imread("test.jpeg", 0);
}

void Image::imageBitPlane()
{

    for (int k = 0; k < 8; k++)
    {

        decimal[k].create(srcImage.size(), CV_8UC1);
    }

    int rowNumber = srcImage.rows;
    int colNumber = srcImage.cols;
    Mat slicer(srcImage.rows, srcImage.cols, CV_8UC1);

    // int first, second;
    // cout << "enter the levels" << endl;
    // cin >> first >> second;

    for (int i = 0; i < rowNumber; i++)
    {
        for (int j = 0; j < colNumber; j++)
        {

            int number = srcImage.at<uchar>(i, j);
            decimalToBinary(number);

            for (int k = 0; k < 8; k++)
            {
                decimal[k].at<uchar>(i, j) = binary[k] * 255;
                // slicer.at<uchar>(i, j) = binary[first] * pow(2 , first) + binary[second] * pow(2 , second);
            }
        }
    }
    // for (int i = 0; i < slicer.rows; i++){
    //     for (int j = 0; j < slicer.cols; j++){
    //     }
    // }
    // imshow("slicer", slicer);
}

void Image::webcamBitPlane(int Mod)
{

    VideoCapture cap(0);
    int level = 0;

    if (Mod == 1)
    {
        namedWindow("slicing");
        createTrackbar("level", "slicing", &level, 7);
    }

    while (true)
    {

        cap >> image;
        cvtColor(image, srcImage, COLOR_RGB2GRAY);
        imshow("src", srcImage);

        for (int k = 0; k < 8; k++)
        {
            decimal[k].create(srcImage.size(), CV_8UC1);
        }

        int rowNumber = srcImage.rows;
        int colNumber = srcImage.cols;

        for (int i = 0; i < rowNumber; i++)
        {
            for (int j = 0; j < colNumber; j++)
            {
                int num = srcImage.at<uchar>(i, j);
                decimalToBinary(num);
                for (int k = 0; k < 8; k++)
                    decimal[k].at<uchar>(i, j) = binary[k] * 255;
            }
        }
        if (Mod == 1)
        {
            char hey = waitKey(1);
            if (hey == int(' '))
            {
                imwrite("Scr.png", decimal[level]);
            }
            imshow("slicing", decimal[level]);
        }
        if (Mod == 2)
        {
            for (int i = 0; i < number - 1; i++)
            {
                alpha = 1.0 / (i + 2);
                temp = Mat(decimal[1].size(), CV_8UC1);
                addWeighted(decimal[pic[i]], 1.0 - alpha, decimal[pic[i + 1]], alpha, 0.0, temp);
                decimal[pic[i + 1]] = temp;
            }
            
            char hey = waitKey(1);
            if (hey == int(' '))
            {
                imwrite("Screenshot.png", temp);
            }

            imshow("linear blend", temp);
        }

        if (waitKey(5) >= 0)
            break;
    }
}

void Image::webcamDisplay()
{
    int flag;
    cout << "1 -> Single bit plane.\n2 -> multiple blendin.";
    cin >> flag;
    switch (flag)
    {
    case 1:
        webcamBitPlane(1);
        break;
    case 2:
        cout << "enter the number of slices:\n";
        cin >> number;
        cout << "select the levels [0-7]." << endl;
        for (int i = 0; i < number; i++)
        {
            cin >> pic[i];
        }
        webcamBitPlane(2);
        break;

    default:
        break;
    }
}
void Image::imageDisplay()
{
    
    char flag;
    Mat dst1, dst2, dst3, dst4, dst5;
    int firstLevel, secondLevel, thirdLevel, fourthLevel, fifthLevel;

    double alpha = 0.5;
    double beta;
    beta = (1.0 - alpha);

    cout << "1-> Single bit plane.\n2->select slices." << endl;
    cin >> flag;

    switch (flag)
    {
    case '1':
        for (int k = 0; k < 8; k++)
        {
            imshow("level" + std::to_string(k), decimal[k]);
        }
        imshow("src", srcImage);
        break;

    case '2':
        char count;
        cout << "enter the number of slices: " << endl;
        cin >> count;

        cout << "select the levels [0-7]" << endl;

        switch (count)
        {

        case '2':

            cin >> firstLevel >> secondLevel;

            addWeighted(decimal[firstLevel], alpha, decimal[secondLevel], beta, 0.0, dst1);

            imshow("Linear Blend", dst1);
            break;

        case '3':

            cin >> firstLevel >> secondLevel >> thirdLevel;

            addWeighted(decimal[firstLevel], alpha, decimal[secondLevel], beta, 0.0, dst1);
            addWeighted(dst1, alpha, decimal[thirdLevel], beta, 0.0, dst2);

            imshow("Linear Blend", dst2);
            break;

        case '4':

            cin >> firstLevel >> secondLevel >> thirdLevel >> fourthLevel;

            addWeighted(decimal[firstLevel], alpha, decimal[secondLevel], beta, 0.0, dst1);
            addWeighted(decimal[thirdLevel], alpha, decimal[fourthLevel], beta, 0.0, dst2);
            addWeighted(dst1, alpha, dst2, beta, 0.0, dst3);

            imshow("Linear Blend", dst3);
            break;

        case '5':

            cin >> firstLevel >> secondLevel >> thirdLevel >> fourthLevel >> fifthLevel;

            addWeighted(decimal[firstLevel], alpha, decimal[secondLevel], beta, 0.0, dst1);
            addWeighted(decimal[thirdLevel], alpha, decimal[fourthLevel], beta, 0.0, dst2);
            addWeighted(dst1, alpha, dst2, beta, 0.0, dst3);
            addWeighted(dst3, alpha, dst2, beta, 0.0, dst4);

            imshow("Linear Blend", dst4);
            break;

        case '6':

            cin >> firstLevel >> secondLevel >> thirdLevel >> fourthLevel >> fifthLevel;

            addWeighted(srcImage, alpha, decimal[firstLevel], beta, 0.0, dst1);
            addWeighted(decimal[secondLevel], alpha, decimal[thirdLevel], beta, 0.0, dst2);
            addWeighted(decimal[fourthLevel], alpha, decimal[fifthLevel], beta, 0.0, dst3);
            addWeighted(dst1, alpha, dst2, beta, 0.0, dst4);
            addWeighted(dst3, alpha, dst4, beta, 0.0, dst5);

            imshow("Linear Blend", dst5);
            break;
        }
    }

    waitKey(0);
}