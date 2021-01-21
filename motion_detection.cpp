/*
Motion Detection with
Basic Background Subtraction
Video source : webcam
*/

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>



int main()
{
    // Create video capture
    cv::VideoCapture cap(0);

    // Check the capture
    if (!cap.isOpened()){
        std::cout << "Error Opening Video Stream" << std::endl;
        return -1;
    }

    // Take first frame as background
    cv::Mat bg;
    cap >> bg;

    // Convert grayscale and resize
    cv::cvtColor(bg, bg, cv::COLOR_BGR2GRAY);
    cv::resize(bg, bg, cv::Size(400, 400));

    // Define frame and frame_diff matrices
    cv::Mat src, frame, frame_diff;

    while(1){

        // Write capture to the frame
        cap >> frame;
        frame.copyTo(src);

        // Check frame
        if(frame.empty()){
            break;
        }

        // Resize src
        cv::resize(src, src, cv::Size(400, 400));

        // Convert frame to grayscale and resize
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        cv::resize(frame, frame, cv::Size(400, 400));

        // Take absolute difference of background img and frame
        cv::absdiff(bg, frame, frame_diff);

        // Apply threshold
        cv::threshold(frame_diff, frame_diff, 50, 255, cv::THRESH_BINARY);

        // Find contours
        std::vector<std::vector<cv::Point> > contours;
        cv::findContours(frame_diff, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );

        // Create and draw rectangles
        std::vector<cv::Rect> boundRect(contours.size());
        for (std::size_t i = 0; i < contours.size(); i++){
            boundRect[i] = cv::boundingRect(contours[i]);
            cv::rectangle(src, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0,255,0), 2);
        }

        // Show frames
        cv::namedWindow("Difference Window");
        cv::imshow("Difference Window", frame_diff);

        cv::namedWindow("Detection Window");
        cv::imshow("Detection Window", src);

        // Press "ESC" to exit
        char c=(char)cv::waitKey(27);
        if(c==27)
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
