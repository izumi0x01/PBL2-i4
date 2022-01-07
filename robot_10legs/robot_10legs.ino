#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 135    // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 430    // this is the 'maximum' pulse length count (out of 4096)

#define map_leg1_angle(angle) map(angle, 0, 165, SERVOMIN, SERVOMAX)
#define map_front_leg2_angle(angle) map(angle, 15, 180, SERVOMIN, SERVOMAX)
#define map_front_leg3_angle(angle) map(angle, 180, 345, SERVOMIN, SERVOMAX)
#define map_back_leg2_angle(angle) map(angle, 0, 165, SERVOMIN, SERVOMAX)

typedef enum {

  //left front leg
  legLF3_pin = 0,
  legLF2_pin = 1,
  legLF1_pin = 2,

  //left back leg
  legLB3_pin = 4,
  legLB2_pin = 5,
  legLB1_pin = 6,
  
  //right back leg
  legRB3_pin = 8,
  legRB2_pin = 9,
  legRB1_pin = 10,
  
  //right front leg
  legRF3_pin = 12,
  legRF2_pin = 13,
  legRF1_pin = 14,
  
}servo_pin_num;

struct leg1_servo_angles {
  int straight;
  int lowerstraight;
  int middle;
  int lowerside;
  int side;
  int beyond_side;
};

struct front_leg2_servo_angles {
  int beyond_up;
  int up;
  int lower_up;
  int horizontal;
};

struct front_leg3_servo_angles {
  int horizontal;
  int down;
  int beyond_down;
};

struct back_leg2_servo_angles {
  int down; 
  int middle;
  int horizontal;
  int up;
};

leg1_servo_angles legLF1_angle  ={15, 45, 60, 75, 105, 150};
leg1_servo_angles legRF1_angle  ={150, 120, 105, 90, 60, 15};
leg1_servo_angles legLB1_angle  ={150, 120, 105, 90, 60, 15};
leg1_servo_angles legRB1_angle  ={15, 45, 60, 75, 105, 150};

front_leg2_servo_angles legLF2_angle  ={75, 90, 105, 180};
front_leg2_servo_angles legRF2_angle  ={75, 90, 105, 180};

front_leg3_servo_angles legLF3_angle  ={180, 270, 345};
front_leg3_servo_angles legRF3_angle  ={180, 270, 345};

back_leg2_servo_angles legLB2_angle  ={165, 110, 90, 0};
back_leg2_servo_angles legRB2_angle  ={165, 110, 90, 0};


void setup() {
  
    pwm.begin();
    pwm.setPWMFreq(50);  // analog servos run at 50Hz updates

    //if you want to set servo degree to zero , comment out here.
    //initialize_servo_degree();

    //front left leg state
    pwm.setPWM(legLF3_pin, 0, map_front_leg3_angle(legLF3_angle.horizontal));
    pwm.setPWM(legLF2_pin, 0, map_front_leg2_angle(legLF2_angle.beyond_up));
    pwm.setPWM(legLF1_pin, 0, map_leg1_angle(legLF1_angle.side));

    //front right leg state
    pwm.setPWM(legRF3_pin, 0, map_front_leg3_angle(legRF3_angle.horizontal));     
    pwm.setPWM(legRF2_pin, 0, map_front_leg2_angle(legRF2_angle.beyond_up));     
    pwm.setPWM(legRF1_pin, 0, map_leg1_angle(legRF1_angle.side));

    //back left leg state
    pwm.setPWM(legLB2_pin, 0, map_back_leg2_angle(legLB2_angle.up));
    pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.straight));
    
    //back right leg state
    pwm.setPWM(legRB2_pin, 0, map_back_leg2_angle(legRB2_angle.up));
    pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.straight));



}
      
//here is movement of creepgates
void loop() {

delay(2000);


//// //後ろ脚の第1関節を後ろに回転させてみる
// pwm.setPWM(legRB1_pin, 0 , map_leg1_angle(legRB1_angle.side));
// pwm.setPWM(legLB1_pin, 0 , map_leg1_angle(legLB1_angle.side));
// delay(1000);
// pwm.setPWM(legLB2_pin, 0 , map_back_leg2_angle(legLB2_angle.down));
// pwm.setPWM(legRB2_pin, 0 , map_back_leg2_angle(legRB2_angle.down));
// delay(1000);
//
// pwm.setPWM(legRB1_pin, 0 , map_leg1_angle(legRB1_angle.straight));
// pwm.setPWM(legLB1_pin, 0 , map_leg1_angle(legLB1_angle.straight));
// delay(1000);
// pwm.setPWM(legLB2_pin, 0 , map_back_leg2_angle(legLB2_angle.horizontal));
// pwm.setPWM(legRB2_pin, 0 , map_back_leg2_angle(legRB2_angle.horizontal));
// delay(1000);
//
// pwm.setPWM(legLB2_pin, 0 , map_back_leg2_angle(legLB2_angle.up));
// pwm.setPWM(legRB2_pin, 0 , map_back_leg2_angle(legRB2_angle.up));
// delay(1000);
 
delay(2000);
////前脚が階段の先につく


//前左脚が横にある
pwm.setPWM(legLF1_pin, 0, map_leg1_angle(legLF1_angle.side));
delay(500);


//前右脚が横にある
pwm.setPWM(legRF1_pin, 0, map_leg1_angle(legRF1_angle.side));
delay(500);


//前左脚が階段を乗り越えるために足が持ち上がる
pwm.setPWM(legLF2_pin, 0, map_front_leg2_angle(legLF2_angle.beyond_up));
delay(500);
pwm.setPWM(legLF3_pin, 0, map_front_leg3_angle(legLF3_angle.beyond_down));
delay(500);


//前左脚を前に持っていく
pwm.setPWM(legLF1_pin, 0, map_leg1_angle(legLF1_angle.straight));
delay(500);
pwm.setPWM(legLF3_pin, 0, map_front_leg3_angle(legLF3_angle.down));
delay(500);


//前左脚が降りる
pwm.setPWM(legLF3_pin, 0, map_front_leg3_angle(legLF3_angle.horizontal));
delay(500);
pwm.setPWM(legLF2_pin, 0, map_front_leg2_angle(legLF2_angle.horizontal));
delay(500);



//前右脚を階段を乗り越えるために足が持ち上がる
pwm.setPWM(legRF2_pin, 0, map_front_leg2_angle(legRF2_angle.beyond_up));  
delay(500);
pwm.setPWM(legRF3_pin, 0, map_front_leg3_angle(legRF3_angle.beyond_down)); 
delay(500);


//前右脚を前に持っていく
pwm.setPWM(legRF1_pin, 0, map_leg1_angle(legRF1_angle.straight));
delay(500);
pwm.setPWM(legRF3_pin, 0, map_front_leg3_angle(legRF3_angle.down));
delay(500);

//前右足が降りる
pwm.setPWM(legRF3_pin, 0, map_front_leg3_angle(legRF3_angle.horizontal));
delay(500);
pwm.setPWM(legRF2_pin, 0, map_front_leg2_angle(legRF2_angle.horizontal));
delay(500);


////前脚が階段の先につく
delay(1000);

pwm.setPWM(legLB2_pin, 0 , map_back_leg2_angle(legLB2_angle.down));
pwm.setPWM(legRB2_pin, 0 , map_back_leg2_angle(legRB2_angle.down));
delay(1000);

//前脚の第3関節を引き寄せる
pwm.setPWM(legLF3_pin, 0, map_front_leg3_angle(legLF3_angle.beyond_down));
pwm.setPWM(legRF3_pin, 0, map_front_leg3_angle(legRF3_angle.beyond_down));
delay(1000);

// //後ろ脚を前に押し出す
// pwm.setPWM(legLB1_pin, 0 , map_leg1_angle(legLB1_angle.beyond_side));
// pwm.setPWM(legLB1_pin, 0 , map_leg1_angle(legLB1_angle.beyond_side));
// pwm.setPWM(legRB2_pin, 0 , map_back_leg2_angle(legRB2_angle.horizontal));
// pwm.setPWM(legRB2_pin, 0 , map_back_leg2_angle(legRB2_angle.horizontal));
// delay(1000);

// //後ろ脚を下にして機体を持ち上げる


//前脚の第2関節の引き寄せ
pwm.setPWM(legLF2_pin, 0, map_front_leg2_angle(legLF2_angle.beyond_up));
pwm.setPWM(legRF2_pin, 0, map_front_leg2_angle(legRF2_angle.beyond_up));
delay(1000);

// //後ろ脚の第1関節を後ろに回転させてみる
// pwm.setPWM(legRB1_pin, 0 , map_leg1_angle(legRB1_angle.side));
// pwm.setPWM(legLB1_pin, 0 , map_leg1_angle(legLB1_angle.side));
// delay(1000);
 pwm.setPWM(legLB2_pin, 0 , map_back_leg2_angle(legLB2_angle.up));
 pwm.setPWM(legRB2_pin, 0 , map_back_leg2_angle(legRB2_angle.up));
 delay(1000);

//前脚の引き寄せ
// pwm.setPWM(legLF2_pin, 0, map_front_leg2_angle(legLF2_angle.horizontal));
// pwm.setPWM(legLF3_pin, 0, map_front_leg3_angle(legLF3_angle.beyond_down));
// pwm.setPWM(legRF2_pin, 0, map_front_leg2_angle(legRF2_angle.horizontal));
// pwm.setPWM(legRF3_pin, 0, map_front_leg3_angle(legRF3_angle.beyond_down));
// delay(10000);

//pwm.setPWM(legLB2_pin, 0 , map_back_leg2_angle(legLB2_angle.up));
//pwm.setPWM(legRB2_pin, 0 , map_back_leg2_angle(legRB2_angle.up));
//delay(1000);

// ////前脚を引き寄せないといけない
// //一度前脚を引き寄せる？

// //3回ループ

// /* 胴体を上げる 前脚を引き寄せる　後ろ脚を回転させて後ろ脚で階段を乗り越える　→　胴体を上げる　前脚を引き寄せる　後ろ脚を回転させて後ろ脚で階段を乗り越える */


// //胴体を上げる（後ろ脚の第3関節を90度に第２関節を垂直に第１関節は横より前に）
//   pwm.setPWM(legLB3_pin, 0, map_leg3_angle(legLB3_angle.down));
//   pwm.setPWM(legLB2_pin, 0, map_leg2_angle(legLB2_angle.horaizontal));
//   pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.beyondside));

//   pwm.setPWM(legRB3_pin, 0, map_leg3_angle(legRB3_angle.down));
//   pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.horaizontal));
//   pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.beyondside));

// //前脚を引き寄せると同時に後ろ脚を横方向に
//   pwm.setPWM(legLF3_pin, 0, map_leg3_angle(legLF3_angle.middle));
//   pwm.setPWM(legLF2_pin, 0, map_leg2_angle(legLF2_angle.middle));
//   pwm.setPWM(legLF1_pin, 0, map_leg1_angle(legLF1_angle.straight));

//   pwm.setPWM(legRF3_pin, 0, map_leg3_angle(legRF3_angle.middle));     
//   pwm.setPWM(legRF2_pin, 0, map_leg2_angle(legRF2_angle.middle));     
//   pwm.setPWM(legRF1_pin, 0, map_leg1_angle(legRF1_angle.straight));

//   pwm.setPWM(legLB3_pin, 0, map_leg3_angle(legLB3_angle.down));
//   pwm.setPWM(legLB2_pin, 0, map_leg2_angle(legLB2_angle.horaizontal));
//   pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.side));

//   pwm.setPWM(legRB3_pin, 0, map_leg3_angle(legRB3_angle.down));
//   pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.horaizontal));
//   pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.side));

// //胴体を降ろす
//   pwm.setPWM(legLB3_pin, 0, map_leg3_angle(legLB3_angle.middle));
//   pwm.setPWM(legLB2_pin, 0, map_leg2_angle(legLB2_angle.middle));
//   pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.side));

//   pwm.setPWM(legRB3_pin, 0, map_leg3_angle(legRB3_angle.middle));
//   pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.middle));
//   pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.side));

// //後ろ脚を回転させて後ろ脚で階段を乗り越える
// //後ろ左脚を持ち上げる
// pwm.setPWM(legLB2_pin, 0, map_leg2_angle(legLB2_angle.aboveup));  
// pwm.setPWM(legLB3_pin, 0, map_leg3_angle(legLB3_angle.abovedown)); 

// //左脚を回転させる、横より前に持っていく
//   pwm.setPWM(legLB3_pin, 0, map_leg3_angle(legLB3_angle.middle));
//   pwm.setPWM(legLB2_pin, 0, map_leg2_angle(legLB2_angle.middle));
//   pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.beyondside));

// //後ろ右脚を持ち上げる
// pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.aboveup));  
// pwm.setPWM(legRB3_pin, 0, map_leg3_angle(legRB3_angle.abovedown)); 

// //右脚を回転させる、横より前に持っていく
//   pwm.setPWM(legRB3_pin, 0, map_leg3_angle(legRB3_angle.middle));
//   pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.middle));
//   pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.beyondside));

// //前脚を伸ばす
//   pwm.setPWM(legLF3_pin, 0, map_leg3_angle(legLF3_angle.horaizontal));
//   pwm.setPWM(legLF2_pin, 0, map_leg2_angle(legLF2_angle.horaizontal));
//   pwm.setPWM(legLF1_pin, 0, map_leg1_angle(legLF1_angle.straight));

//   pwm.setPWM(legRF3_pin, 0, map_leg3_angle(legRF3_angle.horaizontal));     
//   pwm.setPWM(legRF2_pin, 0, map_leg2_angle(legRF2_angle.horaizontal));     
//   pwm.setPWM(legRF1_pin, 0, map_leg1_angle(legRF1_angle.straight));

}


void initialize_servo_degree(){
  while(true){
    //front left leg state
    pwm.setPWM(legLF3_pin, 0, map_front_leg3_angle(legLF3_angle.horizontal));
    pwm.setPWM(legLF2_pin, 0, map_front_leg2_angle(legLF2_angle.horizontal));
    pwm.setPWM(legLF1_pin, 0, map_leg1_angle(legLF1_angle.straight));

    //front right leg state
    pwm.setPWM(legRF3_pin, 0, map_front_leg3_angle(legRF3_angle.horizontal));     
    pwm.setPWM(legRF2_pin, 0, map_front_leg2_angle(legRF2_angle.horizontal));     
    pwm.setPWM(legRF1_pin, 0, map_leg1_angle(legRF1_angle.straight));

    //back left leg state
    pwm.setPWM(legLB2_pin, 0, map_back_leg2_angle(legLB2_angle.horizontal));
    pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.straight));
    
    //back right leg state
    pwm.setPWM(legRB2_pin, 0, map_back_leg2_angle(legRB2_angle.horizontal));
    pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.straight));

    delay(1000);
    }
}
