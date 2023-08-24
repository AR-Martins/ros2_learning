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
      subscription_ = this->create_subscription<dynamixel_sdk_custom_interfaces::msg::SetPosition>(
      "set_position", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }
  private:
    void topic_callback(const dynamixel_sdk_custom_interfaces::msg::SetPosition::SharedPtr message) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard-> Motor ID: %d, Motor POSITION: %d", message->id, message->position);
    }
    rclcpp::Subscription<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr subscription_;
};
int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}