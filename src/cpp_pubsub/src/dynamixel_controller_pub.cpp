#include <cstdio>
#include <memory>
#include <string>
#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"
#include "dynamixel_sdk_custom_interfaces/srv/get_position.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include "read_write_node.hpp"
using namespace std::chrono_literals;
class MinimalPublisher : public rclcpp::Node{
    public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    {
        publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 10);
        timer_ = this->create_wall_timer(
            100ms, std::bind(&MinimalPublisher::timer_callback, this));
    }
    private:
    void timer_callback()
    {
        int ID;
        int POSITION;
        std::cout << "Motor ID: ";
        std::cin >> ID;
        std::cout << "Motor POSITION: ";
        std::cin >> POSITION;
        auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();
        message.id = ID;
        message.position = POSITION;
        RCLCPP_INFO(this->get_logger(), "Publishing: Motor ID: %d, Motor POSITION: %d", message.id, message.position);
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr publisher_;
    size_t count_;
};
int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}