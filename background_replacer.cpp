/*
Background Replacer with
Basic Background Subtraction
*/


#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

// Frame size constant
const int wh = 800;

int main()
{
    // Create video capture
    cv::VideoCapture cap(0);

    // Check the capture
    if (!cap.isOpened()){
        std::cerr << "Error Opening Webcam" << std::endl;
        return -1;
    }

    //Background Image
    cv::Mat bg_img = cv::imread("colesseum.jpg", cv::IMREAD_COLOR);
    cv::resize(bg_img, bg_img, cv::Size(wh, wh));

    // Take first frame as reference
    cv::Mat ref_img;
    cap >> ref_img;

    // Convert grayscale and resize
    cv::cvtColor(ref_img, ref_img, cv::COLOR_BGR2GRAY);
    cv::resize(ref_img, ref_img, cv::Size(wh, wh));

    // Define frame and frame_diff matrices
    cv::Mat src, frame, frame_diff;


    while(1)
    {
        // Write capture to the frame
        cap >> frame;
        frame.copyTo(src);

        cv::Mat imgout;
        bg_img.copyTo(imgout);

        if (frame.empty())
            break;

        // Resize src
        cv::resize(src, src, cv::Size(wh, wh));

        // Convert frame to grayscale and resize
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        cv::resize(frame, frame, cv::Size(wh, wh));

        // Take absolute difference of reference img and frame
        cv::absdiff(ref_img, frame, frame_diff);

        // Apply threshold
        cv::threshold(frame_diff, frame_diff, 30, 255, cv::THRESH_BINARY);

        // Apply fill on mask for gaps
        cv::floodFill(frame_diff, cv::Point(8, 8), cv::Scalar(255) ,0, cv::Scalar(), cv::Scalar(), 4 | cv::FLOODFILL_MASK_ONLY);

        src.copyTo(imgout, frame_diff);

        cv::imshow("Background Replacer", imgout);

        // Press "ESC" to exit
        char c=(char)cv::waitKey(27);
        if(c==27)
            break;

    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
