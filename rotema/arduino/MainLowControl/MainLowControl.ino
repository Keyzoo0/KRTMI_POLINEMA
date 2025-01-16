#include "imu.h"
#include "encoder.h"
#include <ros.h>
#include <geometry_msgs/Quaternion.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32MultiArray.h>

ros::NodeHandle nh;

geometry_msgs::Quaternion Motor_Velocity;
std_msgs::Float32 Imu_Angle;
std_msgs::Int32MultiArray Encoder_Velocity;


ros::Publisher motor_velocity_pub("motor_velocity", &Motor_Velocity);
ros::Publisher imu_angle_pub("imu_angle", &Imu_Angle);
ros::Publisher encoder_velocity_pub("encoder_velocity", &Encoder_Velocity);


void setup() {
  nh.initNode();
  nh.advertise(motor_velocity_pub);
  nh.advertise(encoder_velocity_pub);
  nh.advertise(imu_angle_pub);
  Encoder_Velocity.data_length = 2;
  Encoder_Velocity.data = (int*)malloc(2 * sizeof(int));
  setupIMU();
  setupEncoder() ;
  Serial.begin(57600);
}



void loop() {
  Encoder_Velocity.data[0] = Venc[0];  
  Encoder_Velocity.data[1] = Venc[1];  
  Motor_Velocity.x = rpm[1];
  Motor_Velocity.y = rpm[2];
  Motor_Velocity.z = rpm[3];
  Motor_Velocity.w = rpm[4];
  Imu_Angle.data = readIMU();
  motor_velocity_pub.publish(&Motor_Velocity);
  encoder_velocity_pub.publish(&Encoder_Velocity);
  imu_angle_pub.publish(&Imu_Angle);
  nh.spinOnce();
  delay(10); 
}
