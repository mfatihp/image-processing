#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <string>



int main()
{
    // Image location
    std::string image_loc = "leaf.jpg";

    // Target split matrix
    cv::Mat bgr[3];

    // Outputs
    cv::Mat gray_av, gray_w;

    // Read image
    cv::Mat image = cv::imread(image_loc, cv::IMREAD_COLOR);

    // Split channels
    cv::split(image, bgr);

    // Color Averages
    gray_av = (bgr[0] + bgr[1] + bgr[2])/3;

    // Weighted Colors
    // 0.21 R + 0.72 G + 0.07 B
    gray_w = (bgr[0]*0.07 + bgr[1]*0.72 + bgr[2]*0.21);

    //Show all three images
    cv::imshow("Original", image);
    cv::imshow("Color Averages", gray_av);
    cv::imshow("Weighted Colors", gray_w);

    cv::waitKey(0);

    return 0;
}
