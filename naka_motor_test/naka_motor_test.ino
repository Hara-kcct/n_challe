#include "Cytron_MD13S.h"
#include"ps3i2clib.h"
//#include<cout.h>

#include <ros.h>
#include <geometry_msgs/Twist.h>

MD13S lmo(6, 5); //(PWM_PIN,invert_PIN)
MD13S rmo(8,7);
PS3I2C ps(0x73);
int lp=1500,rp=1500;

void messageCb(const geometry_msgs::Twist& twist) {
  const float linear_x = twist.linear.x;
  const float angle_z = twist.angular.z;
  rmo.writeMicroseconds(1500+300*(linear_x-angle_z));
  // ここ１５００じゃない
  // lmo.writeMicroseconds(15000-300*(linear_x+angle_z));
  lmo.writeMicroseconds(1500-300*(linear_x+angle_z));
}

ros::NodeHandle nh;
//ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb);
ros::Subscriber<geometry_msgs::Twist> sub("/ypspur_ros/cmd_vel", &messageCb);
void setup() {
  analogWriteFrequency(6, 20000);
  analogWriteFrequency(8, 20000);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  nh.initNode();
  nh.subscribe(sub);
  
  // ps.set();
  // put your setup code here, to run once:
  lmo.set();
  rmo.set();
}

void loop() {
  // put your main code here, to run repeatedly:
  //ps.update();
  //rmo.writeMicroseconds(map(ps.A_Ry(),255,0,1200,1800));
  //lmo.writeMicroseconds(map(ps.A_Ly(),0,255,1200,1800));
   nh.spinOnce();
  //cout<<"L="<<lp<<","<<"R="<<rp<<endl;
  //cout<<ps.A_Ly()<<","<<ps.A_Ry()<<endl;
}
