#include "laplace_blending.h"
#include "linear_blending.h"
#include "opencv2/imgproc.hpp"

std::vector<cv::Mat, std::allocator<cv::Mat>> constructGaussianPyramid(const cv::Mat& img)
{
  // Construct the pyramid starting with the original image.
  std::vector<cv::Mat> pyr;
  pyr.push_back(img.clone());

  // Add new downscaled images to the pyramid
  // until image width is <= 16 pixels
  while(pyr.back().cols > 16)
  {
    // TODO: Add the next level in the pyramid.
    // Hint cv::pyrDown(...)
    cv::Mat down;
    cv::pyrDown(pyr.back(), down);  // Downscale the image
    pyr.push_back(down);  // Add to the pyramid
  }

  return pyr;
}


std::vector<cv::Mat> constructLaplacianPyramid(const cv::Mat& img)
{
  // TODO: Use constructGaussianPyramid() to construct a laplacian pyramid.
  // Hint: cv::pyrUp(...)
  std::vector<cv::Mat> gPyr = constructGaussianPyramid(img);
    std::vector<cv::Mat> lPyr;
    for (size_t i = 0; i < gPyr.size() - 1; ++i) {
        cv::Mat up;
        cv::pyrUp(gPyr[i+1], up, gPyr[i].size());  // Upscale the next level
        cv::Mat l = gPyr[i] - up;  // Subtract the upscaled image from the current level
        lPyr.push_back(l);
    }
    lPyr.push_back(gPyr.back());  // The smallest level is added as is
    return lPyr;
}

cv::Mat collapsePyramid(const std::vector<cv::Mat>& pyr)
{
  // TODO: Collapse the pyramid.
  cv::Mat current = pyr.back();  // Start from the smallest image in the pyramid
    for (int i = pyr.size() - 2; i >= 0; --i) {
        cv::Mat up;
        cv::pyrUp(current, up, pyr[i].size());  // Upscale the current image
        current = up + pyr[i];  // Add to the current level
    }
    return current;
}

cv::Mat laplaceBlending(const cv::Mat& img_1, const cv::Mat& img_2, const cv::Mat& weights)
{
  std::vector<cv::Mat> weights_pyr = constructGaussianPyramid(weights);
    std::vector<cv::Mat> img_1_pyr = constructLaplacianPyramid(img_1);
    std::vector<cv::Mat> img_2_pyr = constructLaplacianPyramid(img_2);

    std::vector<cv::Mat> blend_pyr(img_1_pyr.size());
    for (size_t i = 0; i < img_1_pyr.size(); ++i) {
        blend_pyr[i] = linearBlending(img_1_pyr[i], img_2_pyr[i], weights_pyr[i]);
    }

    return collapsePyramid(blend_pyr);
}
