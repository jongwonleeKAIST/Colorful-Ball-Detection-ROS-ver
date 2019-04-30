#ifndef BALL_DETECT_COLOR_ONLY_H
#define BALL_DETECT_COLOR_ONLY_H


#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui.hpp>
#include "core_msgs/ball_position.h"
#include "opencv2/opencv.hpp"
#include <visualization_msgs/Marker.h>
#include <std_msgs/ColorRGBA.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <sensor_msgs/Image.h>

#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace cv;
using namespace std;
using namespace sensor_msgs;
using namespace message_filters;


Mat buffer_color(480,640,CV_8UC3);
Mat buffer_depth(480,640,CV_16UC1);

ros::Publisher pub;
ros::Publisher pub_markers;

struct balls_info
{
    short int num_r;
    short int num_b;
    vector<Point2i>center_r;
    vector<Point2i>center_b;
    vector<int>radius_r;
    vector<int>radius_b;
    vector<short int>distance_r;
    vector<short int>distance_b;

};


balls_info ball_detect();
void pub_msgs(balls_info &ball_information);
void imageCallback(const sensor_msgs::ImageConstPtr& msg_color, const sensor_msgs::ImageConstPtr& msg_depth);

/* Declaration of functions that changes data types */
string intToString(int n);
string floatToString(float f);
void morphOps(Mat &thresh); // Declaration of functions that calculates the ball position from pixel position
vector<float> pixel2point_depth(Point2i pixel_center, int distance);
vector<float> pixel2point(Point2i pixel_center, int pixel_radius);
vector<float> transform_coordinate( vector<float> input );
string type2str(int type);
void remove_trashval(vector<Point2f> &center, vector<float> &radius, int pixel_radius);

/* trackbar part */
const int low_h_r=0, high_h_r=6, low_h2_r=167, high_h2_r=180;
const int low_s_r=90, low_v_r=102;
const int high_s_r=255, high_v_r=255;

const int low_h_b=91, low_s_b=247, low_v_b=47;
const int high_h_b=119, high_s_b=255, high_v_b=255;

const int lowThreshold_r = 100;
const int ratio_r = 3;
const int kernel_size_r = 3;

const int lowThreshold_b = 100;
const int ratio_b = 3;
const int kernel_size_b = 3;


/* setup default parameters */
const float fball_radius = 0.073;

/* Initialization of variable for camera calibration paramters >>change to our own value!!!! */
Mat distCoeffs;
float intrinsic_data[9] = {614.9002685546875, 0.0, 324.05169677734375, 0.0, 615.0999145507812, 236.6910858154297, 0.0, 0.0, 1.0};
float distortion_data[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

/* Initialization of variable for text drawing */
const double fontScale = 2;
const int thickness = 3;
const int iMin_tracking_ball_size = 10;
String text;

/*
-0.999632 0.0169639 -0.0211625 0.149423
0.0268748 0.514338 -0.857167 -0.0219367
-0.00365628 -0.85742 -0.514604 0.734038


Mat R_robottocboard = []
*/



#endif
