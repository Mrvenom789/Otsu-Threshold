#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    //replace path with path to your image
    cv::Mat image = cv::imread("path/to/image", cv::IMREAD_GRAYSCALE);

    int row = image.rows;
    int column = image.cols;

    //get the number of pixels of the image
    int pixels = row * column;
    float weight = 1.0/pixels;

    int bins = 256;
    float range[] = {0, 256};
    const float* histRange = {range};

    //initialize variables
    int thresh = 0;
    int opt_value = 0;

    //create array
    int arr[256];

    for(int i = 0; i < 256; i++){
        arr[i] = i;
    }

    cv::Mat hist;
    cv::calcHist(&image, 1, 0, cv::Mat(), hist, 1, &bins, &histRange, true, false);

    for(int t = 1; t < 255; t++){
        //assign values for foreground and background elements
        float b = 0, f = 0;
        for(int i = 0; i < t; i++){
            b += hist.at<float>(i);
        }

        for(int j = t; j < 255; j++){
            f += hist.at<float>(j);
        }

        //weighted foreground and background elements
        float wb = b * weight;
        float wf = f * weight;
        float mwb = 0, mwf = 0;

        if(b > 0){
            //sum value
            float bSum = 0;
            for(int i = 0; i < t; i++){
                bSum += arr[i] * hist.at<float>(i);
            }

            //mean value
            mwb = bSum / b;
        }

        if(f > 0){
            //sum value
            float fSum = 0;
            for(int j = t; j < 255; j++){
                fSum += arr[j] * hist.at<float>(j);
            }
            //mean value
            mwf = fSum / f;
        }

        //define value
        float value = wb * wf * pow((mwb - mwf), 2);

        if(value > opt_value){
            thresh = t;
            opt_value = value;
        }
    }

    //set the values in the image to 255 or 0
    cv::Mat result = image.clone(); 
    result.setTo(255, image > thresh);
    result.setTo(0, image < thresh);

    cv::imshow("Display Image", result);

    cv::waitKey(0);
    return 0;
}