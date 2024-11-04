#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>
#include <thread>
#include <cmath>

class TurtleController : public rclcpp::Node {
public:
    TurtleController() : Node("turtle_controller") {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    }

    void draw_logo() {
        turn(135);
        move_forward(sqrt(2));
        stop_turtle();

        turn(-225);
        move_forward(4);
        stop_turtle();

        turn(135);
        move_forward(2 * sqrt(2));
        stop_turtle();

        turn(-90);
        move_forward(2 * sqrt(2));
        stop_turtle();

        turn(135);
        move_forward(1.0);
        stop_turtle();

        turn(45);
        move_forward(sqrt(2));
        stop_turtle();

        turn(-90);
        move_forward(sqrt(2));
        stop_turtle();

        turn(45);
        move_forward(1.0);
        stop_turtle();

        turn(45);
        move_forward(3 * sqrt(2));
        stop_turtle();

        turn(135);
        move_forward(1.0);
        stop_turtle();

        turn(45);
        move_forward(3 * sqrt(2));
        stop_turtle();

        turn(-90);
        move_forward(2 * sqrt(2));
        stop_turtle();

        turn(-135);
        move_forward(1.0);
        stop_turtle();
    }

private:
    void move_forward(double distance) {
        auto message = geometry_msgs::msg::Twist();
        message.linear.x = 0.5;
        double time = distance / message.linear.x + 0.5;
        auto start_time = this->now();
        
        while ((this->now() - start_time).seconds() < time) {
            publisher_->publish(message);
            rclcpp::sleep_for(std::chrono::milliseconds(100));
        }
        stop_turtle();
    }

    void turn(double angle) {
        auto message = geometry_msgs::msg::Twist();
        message.angular.z = (angle > 0 ? 1.0 : -1.0) * 0.5;
        double time = abs(angle) / 30.0 + 0.5;
        auto start_time = this->now();
        
        while ((this->now() - start_time).seconds() < time) {
            publisher_->publish(message);
            rclcpp::sleep_for(std::chrono::milliseconds(100));
        }
        stop_turtle();
    }

    void stop_turtle() {
        auto message = geometry_msgs::msg::Twist();
        publisher_->publish(message);
        rclcpp::sleep_for(std::chrono::milliseconds(500));
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleController>();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    node->draw_logo();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
