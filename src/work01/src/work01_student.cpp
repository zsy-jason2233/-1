#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class s : public rclcpp::Node {
public:
    s(std::string name) : Node(name) {
        RCLCPP_INFO(this->get_logger(),"大家好，我是%s",name.c_str());
        mingyue_s_ = this->create_subscription<std_msgs::msg::String>("mingyue",10,std::bind(&s::command_callback,this,std::placeholders::_1));
        mingyue_s2_=this->create_publisher<std_msgs::msg::String>("boat",10);
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mingyue_s_;
    void command_callback(const std_msgs::msg::String::SharedPtr msg) {
        if(msg->data == "mingyue")
        {
            RCLCPP_INFO(this->get_logger(),"我上课了，我要多做1Kg的船");
            std_msgs::msg::String message2;
            message2.data="boat";
            mingyue_s2_->publish(message2);
        }
    }
    //接收
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr mingyue_s2_;
    //传输
};

int main(int argc,char **argv) {
    rclcpp::init(argc,argv);
    auto node = std::make_shared<s>("waya");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}