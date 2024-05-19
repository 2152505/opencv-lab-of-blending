#include "lab_2.h"
#include "laplace_blending.h"
#include "linear_blending.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#define mod_Line 0
#define mod_Circle 1

void lab2(){
  
  cv::Mat img_1 = cv::imread("../white_tiger.png", cv::IMREAD_COLOR);
  if (img_1.empty()) {
      std::cerr << "Error loading image 1\n";
      return;
  }
  img_1.convertTo(img_1, CV_32FC3, 1.0 / 255.0);
  showResult("Lab 2 - Image 1 original", img_1);

  cv::Mat img_2 = cv::imread("../lion.png", cv::IMREAD_COLOR);
  if (img_2.empty()) {
      std::cerr << "Error loading image 2\n";
      return;
  }
  img_2.convertTo(img_2, CV_32FC3, 1.0 / 255.0);
  showResult("Lab 2 - Image 2 original", img_2);

#if mod_Line
  const int ramp_width = 120;

  int cols = img_1.cols;
  int rows = img_1.rows;
  cv::Mat weights(rows, cols, CV_32FC3, cv::Scalar(0.0f,0.0f,0.0f));  
  for (int j = cols / 2; j < cols; ++j) {
      weights.col(j).setTo(cv::Scalar(1.0f,1.0f,1.0f));
  }
  int blur_size = ramp_width * 2 + 1;
  cv::blur(weights, weights, cv::Size(blur_size, blur_size));
  showResult("Lab 2 - Weights - line", weights);
 
  cv::Mat lin_blend = linearBlending(img_1, img_2, weights);
  showResult("Lab 2 - Linear blend", lin_blend);

  cv::Mat lap_blend = laplaceBlending(img_1, img_2, weights);
  showResult("Lab 2 - Laplace blend", lap_blend);

#endif

#if mod_Circle
  const int radius = 500;
  cv::Mat weights(1200,1200,CV_32FC3,cv::Scalar(0.0f ,0.0f ,0.0f));
  cv::Point center(weights.cols/2,weights.rows /2);
  cv::circle(weights,center, radius, cv::Scalar(255,255,255),-1);
  cv::Mat mask;
  weights.convertTo(mask, CV_32FC1 ,1.0 / 255.0);
  cv::Mat ramp;
  cv::blur(mask, ramp, cv::Size(500,500));
  showResult("Lab 2 - weights - circle", ramp);

  cv::Mat lin_blend = linearBlending(img_1, img_2, ramp);
  showResult("Lab 2 - Linear blend", lin_blend);

  cv::Mat lap_blend = laplaceBlending(img_1, img_2, ramp);
  showResult("Lab 2 - Laplace blend", lap_blend);

#endif
  cv::waitKey();
}



void showResult(const std::string& title, cv::Mat img)
{
  if (!img.empty())
  {
    cv::namedWindow(title, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
    cv::imshow(title, img);
  }
  else
  {
    std::cout << "\"" << title << "\" is not ready yet!\n";
  }
}
