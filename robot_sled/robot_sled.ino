#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 135    // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 430    // this is the 'maximum' pulse length count (out of 4096)

#define map_angle(angle) map(angle, 0, 165, SERVOMIN, SERVOMAX)
//#define map_angle(angle) map(angle, 0, 165, SERVOMIN, SERVOMAX)
//#define map_angle(angle) map(angle, 0, 165, SERVOMIN, SERVOMAX)
//#define map_angle(angle) map(angle, 0, 165, SERVOMIN, SERVOMAX)

typedef enum {

  //left front leg
  servo_left_front_leg3 = 0,
  servo_left_front_leg2 = 1,
  servo_left_front_leg1 = 2,

  //left back leg
  servo_left_back_leg = 4,
  
  //right back leg
  servo_right_back_leg = 8,
  
  //right front leg
  servo_right_front_leg3 = 12,
  servo_right_front_leg2 = 13,
  servo_right_front_leg1 = 14,
  
}servo_name;

void setup() {
  
  // put your setup code here, to run once:
    pwm.begin();
    pwm.setPWMFreq(50);  // analog servos run at 50Hz updates

    //initialize servo angle


//前左脚
      pwm.setPWM(servo_left_front_leg3, 0, map_angle(160));
      pwm.setPWM(servo_left_front_leg2, 0, map_angle(10));
      pwm.setPWM(servo_left_front_leg1, 0, map_angle(15));//default
      //pwm.setPWM(servo_left_front_leg1, 0, map_angle(60));//turn right 90 degree

//後ろ右脚
     pwm.setPWM(servo_right_back_leg3, 0, map_angle(160));
     pwm.setPWM(servo_right_back_leg2, 0, map_angle(10));
     pwm.setPWM(servo_right_back_leg1, 0, map_angle(15));//default
     //pwm.setPWM(servo_right_back_leg1, 0, map_angle(105));//turn left 90 degree

//後ろ左脚
     pwm.setPWM(servo_left_back_leg3, 0, map_angle(160));
     pwm.setPWM(servo_left_back_leg2, 0, map_angle(10));
     pwm.setPWM(servo_left_back_leg1, 0, map_angle(150));

//前右脚
     pwm.setPWM(servo_right_front_leg3, 0, map_angle(160));
     pwm.setPWM(servo_right_front_leg2, 0, map_angle(10));
     pwm.setPWM(servo_right_front_leg1, 0, map_angle(150));

}

     //後ろ左脚、前左足
     //pwm.setPWM(servo_left_front_leg1, 0, map_angle(150));//default
     //pwm.setPWM(servo_left_front_leg1, 0, map_angle(60));//turn right 90 degree

     //後ろ右足、前右足
     //pwm.setPWM(servo_left_front_leg1, 0, map_angle(15));//default
     //pwm.setPWM(servo_right_back_leg1, 0, map_angle(105));//turn left 90 degree
      
void loop() {
  // put your main code here, to run repeatedly:

  front_legs_shrink();
  front_legs_expand();
  front_with_back_legs_move();
  back_legs_shrink();
  
}

void front_with_back_legs_move(){

  //前脚をちじめて
   pwm.setPWM(servo_left_front_leg2, 0, map_angle(10));
  delay(100);
 pwm.setPWM(servo_right_front_leg2, 0, map_angle(10));
 delay(1000);

 //後ろ脚を伸ばす
    pwm.setPWM(servo_left_front_leg2, 0, map_angle(10));
  delay(100);
 pwm.setPWM(servo_right_front_leg2, 0, map_angle(10));
 delay(1000);

 
}


void front_legs_shrink(){

  //脚を上げて
   pwm.setPWM(servo_left_front_leg3, 0, map_angle(90));
  delay(100);
 pwm.setPWM(servo_right_front_leg3, 0, map_angle(90));
 delay(1000);

 //脚をちじめて
   pwm.setPWM(servo_left_front_leg2, 0, map_angle(10));
  delay(100);
 pwm.setPWM(servo_right_front_leg2, 0, map_angle(10));
 delay(1000);
 
 //脚を降ろす
  pwm.setPWM(servo_left_front_leg3, 0, map_angle(160));
   delay(100);
 pwm.setPWM(servo_right_front_leg3, 0, map_angle(160));
  delay(1000);
  
}

void front_legs_expand(){

    //脚を上げて
   pwm.setPWM(servo_left_front_leg3, 0, map_angle(90));
  delay(100);
 pwm.setPWM(servo_right_front_leg3, 0, map_angle(90));
 delay(1000);

 //脚を伸ばして
   pwm.setPWM(servo_left_front_leg2, 0, map_angle(75));
  delay(100);
 pwm.setPWM(servo_right_front_leg2, 0, map_angle(75));
 delay(1000);

 //脚を降ろす
  pwm.setPWM(servo_left_front_leg3, 0, map_angle(160));
   delay(100);
 pwm.setPWM(servo_right_front_leg3, 0, map_angle(160));
  delay(1000);
  
}

void back_legs_shrink(){

      //脚を上げて
   pwm.setPWM(servo_left_back_leg3, 0, map_angle(90));
  delay(100);
 pwm.setPWM(servo_right_back_leg3, 0, map_angle(90));
 delay(1000);

 //脚を伸ばして
   pwm.setPWM(servo_left_back_leg2, 0, map_angle(10));
  delay(100);
 pwm.setPWM(servo_right_back_leg2, 0, map_angle(10));
 delay(1000);

 //脚を降ろす
  pwm.setPWM(servo_left_back_leg3, 0, map_angle(160));
   delay(100);
 pwm.setPWM(servo_right_back_leg3, 0, map_angle(160));
  delay(1000);
  
}

void back_legs_expand(){

      //脚を上げて
   pwm.setPWM(servo_left_back_leg3, 0, map_angle(90));
  delay(100);
 pwm.setPWM(servo_right_back_leg3, 0, map_angle(90));
 delay(1000);

 //脚を伸ばして
   pwm.setPWM(servo_left_back_leg2, 0, map_angle(75));
  delay(100);
 pwm.setPWM(servo_right_back_leg2, 0, map_angle(75));
 delay(1000);

 //脚を降ろす
  pwm.setPWM(servo_left_back_leg3, 0, map_angle(160));
   delay(100);
 pwm.setPWM(servo_right_back_leg3, 0, map_angle(160));
  delay(1000);
  
}

//////
void front_legs_move_forward(){



//前脚を進行方向に、あげて、伸ばしながら、前面におく

//脚を上げる
 pwm.setPWM(servo_left_front_leg3, 0, map_angle(90));
  delay(100);
 pwm.setPWM(servo_right_front_leg3, 0, map_angle(90));
 delay(1000);
 
//脚を前に
 pwm.setPWM(servo_right_front_leg1, 0, map_angle(150));
 delay(100);
 pwm.setPWM(servo_left_front_leg1, 0, map_angle(15));
 delay(1000);


 //降ろす
 pwm.setPWM(servo_left_front_leg3, 0, map_angle(160));
   delay(100);
 pwm.setPWM(servo_right_front_leg3, 0, map_angle(160));
  delay(1000);



}

void back_legs_move_forward(){

}

void front_legs_move_side(){

   //脚を上げる
   pwm.setPWM(servo_left_front_leg3, 0, map_angle(90));
    delay(100);
   pwm.setPWM(servo_right_front_leg3, 0, map_angle(90));
   delay(1000);

    //まずは、左右前脚をサイドに90度固定しておく。初期位置とする
   pwm.setPWM(servo_right_front_leg1, 0, map_angle(60));
   delay(100);
   pwm.setPWM(servo_left_front_leg1, 0, map_angle(105));
   delay(1000);
  
   //降ろす
   pwm.setPWM(servo_left_front_leg3, 0, map_angle(160));
     delay(100);
   pwm.setPWM(servo_right_front_leg3, 0, map_angle(160));
    delay(1000);

}

void back_legs_move_side(){

}
