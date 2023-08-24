#include <cstdio>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"
using std::placeholders::_1;
class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      subscription_ = this->request<dynamixel_sdk_custom_interfaces::srv::GetPosition>(
      "get_position", 10, std::bind(&MinimalSubscriber::service, this, _1));
    }
  private:
    void service(const dynamixel_sdk_custom_interfaces::srv::GetPosition::Request response) const
    {
      RCLCPP_INFO(this->get_logger(), "Motor ID: %d, Motor Present POSITION: %d", message->id, message->position);
    }
    rclcpp::Subscription<dynamixel_sdk_custom_interfaces::srv::GetPosition>::SharedPtr subscription_;
};
int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}