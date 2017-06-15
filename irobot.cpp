#include <ros/ros.h>
#include <signal.h>
#include <geometry_msgs/Twist.h>
 
ros::Publisher cmdVelPub;
 
void shutdown(int sig)
{
    cmdVelPub.publish(geometry_msgs::Twist());
    ROS_INFO("exbot example move cpp ended!");
    ros::shutdown();
}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "exbotxi_example_move");
    std::string topic = "cmd_vel";
    ros::NodeHandle node;
    cmdVelPub = node.advertise<geometry_msgs::Twist>(topic, 1);
    ros::Rate loopRate(50);
    signal(SIGINT, shutdown);
    ROS_INFO("exbot_example_move cpp start...");
 
    int rate = 50;
    double linear_speed = 0.2;
    double goal_distance = 1.0;
    double linear_duration = goal_distance / linear_speed;
 
    double angular_speed = 1.0;
    double goal_angle = 3.14/ 2.0;
    double angular_duration = goal_angle / angular_speed;
 
    geometry_msgs::Twist speed;
    //while(ros::ok())
    for(int i=0; i<1; i++)
    {
        speed = geometry_msgs::Twist();    
         
        int ticks = int(linear_duration * rate);
        speed.linear.x = linear_speed;
        //speed.angular.z = angular_speed;
         
        int t = 0;
        for(t=0; t<ticks; t++)
        {
            cmdVelPub.publish(speed);
            loopRate.sleep();
            //sleep(1);
        }
        //在旋转前停止机器人行走
        speed = geometry_msgs::Twist();
        cmdVelPub.publish(geometry_msgs::Twist());
        sleep(1);
        //loopRate.sleep();
 
        speed.angular.z = angular_speed;
        ticks = int(goal_angle * rate);
        for(t=0; t<ticks; t++)
        {
            cmdVelPub.publish(speed);
            loopRate.sleep();
        }
 
        cmdVelPub.publish(geometry_msgs::Twist());
        loopRate.sleep();
    }
 
    return 0;
}
