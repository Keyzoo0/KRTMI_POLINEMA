#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Float32.h>


int rpm1 , rpm2 ;
float axle_lenght = 0.255; //25,5 cm 
float r_wheel = 0.05;
float cal_xdot = 0.01,
      cal_ydot = 0.01;
float imu_angle = 0 ;
float xpos , ypos ,zpos;
geometry_msgs::Quaternion Motor_Velocity;


float d2r(int degree){
  float radians = degree * 0.0174533;
  return radians;
}
void orientationCallback(const geometry_msgs::Quaternion::ConstPtr& msg)
{
    Motor_Velocity = *msg;
}

void imuAngleCallback(const std_msgs::Float32::ConstPtr& msg)
{
    imu_angle = msg->data;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "RobotPositionNode");
    ros::NodeHandle nh;
    ros::Publisher position_pub = nh.advertise<geometry_msgs::Vector3>("/robot_position", 10);
    ros::Subscriber orientation_sub = nh.subscribe("/motor_velocity", 10, orientationCallback);
    ros::Subscriber imu_angle_sub = nh.subscribe("/imu_angle", 10, imuAngleCallback);
    geometry_msgs::Vector3 robot_position;
    robot_position.x = 0.0;
    robot_position.y = 0.0;
    robot_position.z = 0.0;
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        rpm1 = Motor_Velocity.x;
        rpm2 = Motor_Velocity.y;

        float xdot = 0, ydot = 0 ;
        double dt = 0.1; // Time step corresponding to 10 Hz
        xdot = r_wheel * (
            (cos(imu_angle) * (
                cos(d2r(45.)) * rpm1 +
                cos(d2r(135.)) * rpm2
            )) +
            (sin(imu_angle) * (
                sin(d2r(45)) * rpm1 +
                sin(d2r(135)) * rpm2
            ))
        );

        ydot = r_wheel * (
            (-sin(imu_angle) * (
                cos(d2r(45.)) * rpm1 +
                cos(d2r(135.)) * rpm2
            )) +
            (cos(imu_angle) * (
                sin(d2r(45)) * rpm1 +
                sin(d2r(135)) * rpm2
            ))
        );

        xdot = xdot * cal_xdot;
        ydot = ydot * cal_ydot;

        xpos += xdot*dt;
        ypos += ydot*dt;
        zpos = imu_angle;

        robot_position.x = xpos;
        robot_position.y = ypos;
        robot_position.z = zpos;
       
        position_pub.publish(robot_position);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
