/**
 * @file subscriber.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include "tutorial_interfaces/msg/op_num.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
      : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<tutorial_interfaces::msg::OpNum>(
        "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  int numTotal = 0;
  void topic_callback(const tutorial_interfaces::msg::OpNum::SharedPtr msg)
  {
    std::string op = msg->op;
    int num = msg->num;
    //proper way to do this would be through an enum and switch case but don't feel like dealing with that now
    if(op == "plus")
    {
      numTotal += num;
    }
    else if(op == "min")
    {
      numTotal -= num;
    }
    else if(op == "keer")
    {
      numTotal *= num;
    }
    RCLCPP_INFO(this->get_logger(), "The number is now: '%d'", numTotal);
  }
  rclcpp::Subscription<tutorial_interfaces::msg::OpNum>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}