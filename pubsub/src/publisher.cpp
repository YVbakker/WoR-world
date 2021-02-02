/**
 * @file publisher.cpp
 * @author Yael Bakker (me@yael.fyi)
 * @brief 
 * @version 0.1
 * @date 2021-02-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
      : Node("minimal_publisher")
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    timer_ = this->create_wall_timer(
        2000ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  std::random_device device;
  static std::mt19937 generator(device());
  std::uniform_int_distribution<int> dist(0, 9);
  void timer_callback()
  {
    auto message = std_msgs::msg::UInt8();
    message.data = dist(generator);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", std::to_string(message.data));
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}