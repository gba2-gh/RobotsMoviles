#include <opencv2/opencv.hpp>
#include "ros/ros.h"
#include "std_msgs/UInt8MultiArray.h"

void callback_img(const std_msgs::UInt8MultiArray::ConstPtr& msg)
{    cv::imshow("Minirobot Image", cv::imdecode(msg->data, 1));

//cv::Mat img_bgr = cv::imdecode(msg->data, 1);
//cv::Mat img_hsv;
//cv::Mat img_filtered;
//cv::cvtColor(img_bgr, img_gray, CV_BGR2HSV);
//cv::imshow("CV", img_hsv);
//cv::InRange(img_hsv, cv::Scalar(120, 20, 115), cv::Scalar(100,60,155), img_binary);
//cv::imShow("binary", img_binary)

//utilizar operadores morfologicos, (erosion y dilatacion), para eliminar ruido
	//crear funcion para comparar la matriz. TIPO ELIPSE
//cv::Mat kernel= cv::getStructuringElement(cv::MORPH_ELLIPSE, 	cv::size(5,5),cv::Point(2,2));

	//hacer operacion de erosion
// cv::erode(img_binary, img_filtered, kernel);

		//dilatar!!!
//cv::dilate(img_filtered,img_filtered,kernel);

// std::vector<cv::Point> positions; //arreglo de cv con las coordenadas de todos los pixeles de la mancha de color
//cv::findNonZero(img_filtered, positions);
// cv::Scalar centroid = cv::mean(positions);   //media


//cv::imshow("filtered", img_filtered);

//cv:Mat img_bgr = cv::imdecode(msg->data, 1);



}

int main(int argc, char** argv)
{
    std::cout << "Initializing compressed image visualizer..." << std::endl;
    ros::init(argc, argv, "compres_img_viz");
    ros::NodeHandle n;
    ros::Subscriber subCompressed = n.subscribe("/minirobot/hardware/img_compressed", 1, callback_img);
    ros::Rate loop(30);

    while(ros::ok() && cv::waitKey(10)!= 27)
    {
        ros::spinOnce();
        loop.sleep();
    }
}
