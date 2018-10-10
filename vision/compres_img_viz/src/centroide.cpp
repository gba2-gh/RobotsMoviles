#include <opencv2/opencv.hpp>
#include "ros/ros.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/Float32MultiArray.h"

void callback_img(const std_msgs::UInt8MultiArray::ConstPtr& msg\
)
{
    cv::Mat img_hsv;
    cv::Mat img_binary;
    cv::Mat img_filtered;
    cv::Mat img_bgr = cv::imdecode(msg->data,1 );
    cv::imshow("Rotombot Camera", img_bgr);//cv::imdecode(msg->data, 1));
    cv::cvtColor(img_bgr, img_hsv, CV_BGR2HSV);
    cv::imshow("Gris", img_hsv);
//    cv::inRange(img_hsv,cv::Scalar(140,80,230),cv::Scalar(170,250,250),i\
//mg_binary);
   cv::inRange(img_hsv,cv::Scalar(90,45,160),cv::Scalar(170,250,250),i\
mg_binary);

    cv::imshow("Imagen Binaria", img_binary);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Siz\
e(5,5),cv::Point(2,2));
    cv::erode(img_binary, img_filtered, kernel);
    cv::dilate(img_filtered,img_filtered, kernel);
    cv::imshow("Filtro", img_filtered);
    std::vector<cv::Point> positions;
    cv::findNonZero(img_filtered, positions);
    cv::Scalar centroid = cv::mean(positions);
    std::cout << "Centroide: " << centroid << std::endl;

    ros::NodeHandle n;

std_msgs::Float32MultiArray msg_color;
    std::vector<float>  centro_color;
    centro_color.resize(2);
    msg_color.data.resize(centro_color.size());
    ros::Publisher pub_color = n.advertise<std_msgs::Float32MultiArray>("\
/rotombot/hardware/color", 1);
    ros::Rate loop(30);
    centro_color[0] = centroid[0];
    centro_color[1] = centroid[1];
    msg_color.data[0] = centro_color[0];
    msg_color.data[1] = centro_color[1];
    while(ros::ok() && cv::waitKey(10)!= 27)
       {
           pub_color.publish(msg_color);
           ros::spinOnce();
           loop.sleep();
       }
}
int main(int argc, char** argv)
{
    std::cout << "Initializing compressed image visualizer..." << std::en\
dl;
    ros::init(argc, argv, "compres_img_viz");
    ros::NodeHandle n;

    ros::Subscriber subCompressed = n.subscribe("/rotombot/hardware/img_c\
ompressed", 1, callback_img);
    ros::Rate loop(30);

    while(ros::ok() && cv::waitKey(10)!= 27)
    {
        ros::spinOnce();
        loop.sleep();
    }
}


