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

#include <rclcpp/rclcpp.hpp>
#include "tutorial_interfaces/msg/op_num.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
      : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<tutorial_interfaces::msg::OpNum>("topic", 10);
    //write message every 2s
    timer_ = this->create_wall_timer(2000ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  std::string op[3] = {"plus", "min", "keer"};
  void timer_callback()
  {
    auto message = tutorial_interfaces::msg::OpNum();
    size_t num = this->count_++;
    message.op = op[num%3];
    message.num = num;
    RCLCPP_INFO(this->get_logger(), "Publishing: %s %d", message.op.c_str() ,message.num);
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<tutorial_interfaces::msg::OpNum>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}