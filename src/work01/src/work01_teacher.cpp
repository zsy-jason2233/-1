#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class t:public rclcpp::Node{
public:
    t(std::string name):Node(name){
        RCLCPP_INFO(this->get_logger(),"大家好，我是%s",name.c_str());
        mingyue_t_=this->create_publisher<std_msgs::msg::String>("mingyue",10);
        mingyue_t2_ = this->create_subscription<std_msgs::msg::String>("boat",10,std::bind(&t::command_callback,this,std::placeholders::_1));
        timer_=this->create_wall_timer(std::chrono::milliseconds(5000),std::bind(&t::timer_callback,this));
    }
private:
    void timer_callback(){
        i++;
        std_msgs::msg::String message1;
        message1.data="mingyue";
        RCLCPP_INFO(this->get_logger(),"不想上课的老师 第%d次上工程设计课",i)   ;
        mingyue_t_->publish(message1);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr mingyue_t_;
    int i=0,j=0;
    //传输
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mingyue_t2_;
    void command_callback(const std_msgs::msg::String::SharedPtr msg) {
        if(msg->data == "boat")
        j++;
        RCLCPP_INFO(this->get_logger(),"我们做的船负重达到%dKg ",j);
    }
    //接收 
};
//定义名字 开启节点 
int main(int argc,char **argv) {
    rclcpp::init(argc,argv);
    auto node = std::make_shared<t>("niluo");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}