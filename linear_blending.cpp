//#include "linear_blending.h"

//cv::Mat linearBlending(const cv::Mat& img_1, const cv::Mat& img_2, const cv::Mat& weights)
//{
  // TODO: Blend the two images according to the weights: result = weights*img_1 + (1-weights)*img_2
  // No need to loop through all pixels!
  // Hint: https://docs.opencv.org/3.3.1/d1/d10/classcv_1_1MatExpr.html
  //return cv::Mat();
//}

#include "linear_blending.h"

cv::Mat linearBlending(const cv::Mat& img_1, const cv::Mat& img_2, const cv::Mat& weights) {
    cv::Mat result;
    cv::Mat inv_weights = cv::Scalar(1.0f,1.0f,1.0f) - weights;  // Calculate (1 - weights)

    // Perform element-wise multiplication according to the formula
    cv::multiply(img_1,weights, result);
    cv::Mat temp;
    cv::multiply(img_2, inv_weights, temp);
    cv::add(result,temp,result);  // Add the results of the multiplication

    return result;
}


