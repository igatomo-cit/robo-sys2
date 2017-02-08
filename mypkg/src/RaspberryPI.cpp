#include"ros/ros.h"
#include"geometry_msgs/Twist.h"

#define STEP 200
#define tread 158.7
#define diameter 31.75
const double MMPP = (diameter*M_PI)/STEP;
double linear;
double angular;
int dirty;


void cb(const geometry_msgs::Twist::ConstPtr& msg){

  linear = (msg->linear.x*10)/MMPP;
  angular = (tread*M_PI*((msg->angular.z*10)/360))/MMPP;

  if(((linear - floor(linear) > 0.5) && (angular == 0)) || (angular - floor(angular) > 0.5)){

    linear = ceil(linear);
    angular = ceil(angular);

  }
  if((linear - floor(linear) <= 0.5) || (angular - floor(angular) <= 0.5)){

    linear = floor(linear);
    angular = floor(angular);

  }

  dirty = 1;

}

int main(int argc, char **argv){

  ros::init(argc, argv, "RaspberryPI");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("turtle1/cmd_vel", 1, cb);

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("order", 1);

  ROS_INFO("START");

  while(ros::ok()){

    geometry_msgs::Twist msg;

    msg.linear.x = linear;
    msg.angular.z = angular;

    if(dirty == 1){

      if(linear > 0){
        ROS_INFO("UP");
      }
      if(linear < 0){
        ROS_INFO("DOWN");
      }
      if(angular > 0){
        ROS_INFO("LEFT");
      }
      if(angular < 0){
        ROS_INFO("RIGHT");
      }

      pub.publish(msg);

      dirty = 0;

    }

    ros::spinOnce();

  }

}
