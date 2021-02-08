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
#include "tutorial_interfaces/msg/num.hpp"     
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<tutorial_interfaces::msg::Num>(          
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const tutorial_interfaces::msg::Num::SharedPtr msg) const       
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->num);              
  }
  rclcpp::Subscription<tutorial_interfaces::msg::Num>::SharedPtr subscription_;       
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}