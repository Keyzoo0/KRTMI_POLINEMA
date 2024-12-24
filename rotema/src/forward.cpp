#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char** argv) {
    // Inisialisasi node ROS
    ros::init(argc, argv, "quaternion_publisher");
    ros::NodeHandle nh;

    // Buat publisher
    ros::Publisher quaternion_pub = nh.advertise<geometry_msgs::Quaternion>("forward_speed", 10);

    // Set rate publikasi
    ros::Rate loop_rate(20); // 20 Hz = 50 ms per loop

    // Variabel untuk menyimpan nilai x dan y
    int x = 0;
    int y = 0;

    while (ros::ok()) {
        // Buat quaternion menggunakan tf2
        tf2::Quaternion q;
        q.setRPY(1.0, 0.5, 0.0); // Roll, Pitch, Yaw dalam radian

        // Konversi tf2::Quaternion ke geometry_msgs::Quaternion
        geometry_msgs::Quaternion quaternion_msg;
        quaternion_msg.x = x;
        quaternion_msg.y = y;
        quaternion_msg.z = q.z();
        quaternion_msg.w = q.w();

        // Publikasikan quaternion
        quaternion_pub.publish(quaternion_msg);

        // Log informasi
        ROS_INFO("Published Quaternion: [x: %f, y: %f, z: %f, w: %f]",
                 quaternion_msg.x, quaternion_msg.y, quaternion_msg.z, quaternion_msg.w);

        // Tingkatkan nilai x dan y
        x++;
        y++;

        // Reset ke 0 jika sudah mencapai 255
        if (x > 255) x = 0;
        if (y > 255) y = 0;

        // Tunggu sesuai rate
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
