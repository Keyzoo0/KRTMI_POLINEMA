#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Int32.h>

class TaskNavigator {
public:
    TaskNavigator() {
        // Publisher untuk /nav_goal
        nav_goal_pub_ = nh_.advertise<geometry_msgs::Vector3>("/nav_goal", 10);

        // Subscriber untuk /task_index
        task_index_sub_ = nh_.subscribe("/task_index", 10, &TaskNavigator::taskIndexCallback, this);
    }

    void taskIndexCallback(const std_msgs::Int32::ConstPtr& msg) {
        ROS_INFO("Received task index: %d", msg->data);
        int index = (int)msg->data;
        index = 0 ;
        // Generate a navigation goal based on the task index
        geometry_msgs::Vector3 nav_goal;
        
        // switch(index){
        //     case 0 :
                nav_goal.x = 20; // Example: scale x by task index
                nav_goal.y = 0; // Example: scale y by task index
                nav_goal.z = 0; // Assume z is always 0 for 2D navigation
        //         break;
        //     default :
        //         nav_goal.x = 20; // Example: scale x by task index
        //         nav_goal.y = 0; // Example: scale y by task index
        //         nav_goal.z = 0; // Assume z is always 0 for 2D navigation
        //         break;

        // }

        // Publish the navigation goal
        nav_goal_pub_.publish(nav_goal);

        ROS_INFO("Published nav goal: [x: %f, y: %f, z: %f]", nav_goal.x, nav_goal.y, nav_goal.z);
    }

private:
    ros::NodeHandle nh_;
    ros::Publisher nav_goal_pub_;
    ros::Subscriber task_index_sub_;
};

int main(int argc, char** argv) {
    // Inisialisasi ROS node
    ros::init(argc, argv, "RobotNavigationNode");

    // Membuat instance TaskNavigator
    TaskNavigator task_navigator;

    // Menjalankan loop ROS
    ros::spin();

    return 0;
}
