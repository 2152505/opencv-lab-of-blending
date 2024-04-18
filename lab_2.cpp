#include "lab_2.h"
#include "laplace_blending.h"
#include "linear_blending.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

void lab2()
{
  // Load images.
  // TODO: Load the images using cv::imread() and convert to 32-bit floating point images.
  // Using relative filenames such as "../tiger.png" should work.
  // Remember to rescale so that they have values in the interval [0, 1].
  // Hint: convertTo().
  cv::Mat img_1;
  showResult("Lab 2 - Image 1 original", img_1);

  cv::Mat img_2;
  showResult("Lab 2 - Image 2 original", img_2);

  // Construct weights.
  // TODO: Create a 32-bit, 3 channel floating point weight image.
  // The first half of the columns should be black (0.0f).
  // The last half of the columns should be white (1.0f).
  // Then make a ramp between these two halves.
  // Hint: Use cv::blur() to make the ramp.
  const int ramp_width = 5;
  cv::Mat weights;
  showResult("Lab 2 - Weights", weights);

  // Perform blending.
  // TODO: Finish linear_blending.cpp.
  cv::Mat lin_blend = linearBlending(img_1, img_2, weights);
  showResult("Lab 2 - Linear blend", lin_blend);

  // TODO: Finish laplace_blending.cpp.
  cv::Mat lap_blend = laplaceBlending(img_1, img_2, weights);
  showResult("Lab 2 - Laplace blend", lap_blend);

  // Show all results.
  // Press a key when finished.
  // If you close the windows, the program won't stop!
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
