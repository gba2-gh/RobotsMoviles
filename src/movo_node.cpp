
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"

float beta=2;
float ea; float c;
float w1;
float w2;

void movoCallback(const std_msgs::Float32MultiArray::ConstPtr& centro)
{
    ros::NodeHandle n; 

    std_msgs::Float32MultiArray msg_speeds;   
    std::vector<float>  cent;
    cent.resize(2);
    c=centro->data[0];
	if(c==0){
		ea=0;
 }else{
		ea=c-160;
 		}
	
	if(c>140 & c<180){
		w1=7.5;
		w2=7.5;}else{
  w1=0.85*(2/(1+pow(2.71,(-ea/beta))) -1);
    w2=-0.9*(2/(1+pow(2.71,(-ea/beta))) -1);
}	
//if(abs(w1)>0 & abs(w1)<0.20 & abs(w2)>0 & abs(w2)<0.20 ){w1=0.7;w2=0.7;}
//	if(abs(w1-abs(w2)) < 0.01){
//		w2=w1;

	//	}
			

    msg_speeds.data.resize(cent.size());
    ros::Publisher pub_color = n.advertise<std_msgs::Float32MultiArray>("/rotombot/hardware/motor_speeds", 1);
    ros::Rate loop(30);
    cent[0] = w1;
    cent[1] = w2;
    msg_speeds.data[0] = cent[0]; 
    msg_speeds.data[1] = cent[1];
	std::cout << "motor" << msg_speeds << std::endl;
    while(ros::ok())
       {
           pub_color.publish(msg_speeds);
           ros::spinOnce();
           loop.sleep();
       }
	//msg_speeds=Float32MultiArray();
	//ea=centro[0];
	//w=1*(2/(1+pow(2.71,(-ea/beta))) -1);
	//msg_speeds.data=[w,-w] ;
	//pub_movo.publish(motor);
	//ros::spinOnce();

}


int main(int argc, char** argv)
{
	std::cout << "Iniciando calculo..." << std::endl;
	ros::init(argc,	argv,  "movo");
	ros::NodeHandle n;

	//ros::Publisher pub_movo=n.advertise<std_msgs::Float32MultiArray>("/rotombot/hardware/motor_speeds",1);
	ros::Subscriber sub = n.subscribe("/rotombot/hardware/color", 10, movoCallback);
	ros::Rate loop(30);

	while(ros::ok())
    	{
        	ros::spinOnce();
        	loop.sleep();
    	}
}
