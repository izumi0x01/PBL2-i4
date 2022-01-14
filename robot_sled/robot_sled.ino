 #include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 135    // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 430    // this is the 'maximum' pulse length count (out of 4096)

#define map_angle(angle) map(angle, 0, 165, SERVOMIN, SERVOMAX)

typedef enum {

  //left front leg
  legLF3_pin = 0,
  legLF2_pin = 1,
  legLF1_pin = 2,

  //left back leg
  legLB_pin = 4,
  
  //right back leg
  legRB_pin = 8,
  
  //right front leg
  legRF3_pin = 12,
  legRF2_pin = 13,
  legRF1_pin = 14,
  
}servo_pin_num;

struct front_leg1_servo_angles {
  int straight;
  int lowerstraight;
  int middle;
  int lowerside;
  int side;
  int beyond_side;
};

struct front_leg2_servo_angles {
  int upper_limit;
  int upward_vertical;
  int beyond_upward_vertical;
  int horizontal;
  int beyond_horizontal;
};

struct front_leg3_servo_angles {
  int horizontal;
  int lower_horizontal;
  int diagonal;
  int frontward_vertical;
  int downward_grounding;
};

struct back_leg_servo_angles {
  int backward_grounding;
  int horizontal;
  int diagonal; 
  int frontward_grounding;
  int beyond_frontward_vertical;
};

front_leg1_servo_angles legLF1_angle  ={15, 45, 60, 75, 105, 150};
front_leg1_servo_angles legRF1_angle  ={150, 120, 105, 90, 60, 15};

front_leg2_servo_angles legLF2_angle  ={0, 45, 75, 135, 150};
front_leg2_servo_angles legRF2_angle  ={0, 45, 75, 135, 150};

front_leg3_servo_angles legLF3_angle  ={0, 20, 45, 75, 165};
front_leg3_servo_angles legRF3_angle  ={0, 20, 45, 75, 165};

back_leg_servo_angles legLB_angle  ={0, 65, 80, 155, 165};//default
back_leg_servo_angles legRB_angle  ={165, 100, 85, 10, 0};


void setup() {
  
    pwm.begin();
    pwm.setPWMFreq(50);  // analog servos run at 50Hz updates

    //if you want to set servo degree to zero , comment out here.
    //initialize_servo_degree();

}
      
//here is movement of creepgates
void loop() {


// 動作１

delay(5000);
//  pwm.setPWM(legLB_pin, 0, map_angle(legLB_angle.backward_grounding));
//  pwm.setPWM(legRB_pin, 0, map_angle(legRB_angle.backward_grounding));
//pwm.setPWM(legLB_pin, 0, map_angle(legLB_angle.diagonal));
//pwm.setPWM(legRB_pin, 0, map_angle(legRB_angle.diagonal));
delay(100);

pwm.setPWM(legLF3_pin, 0, map_angle(legLF3_angle.horizontal));
pwm.setPWM(legRF3_pin, 0, map_angle(legRF3_angle.horizontal)); 
delay(100);
pwm.setPWM(legLF2_pin, 0, map_angle(legLF2_angle.upper_limit));
pwm.setPWM(legRF2_pin, 0, map_angle(legRF2_angle.upper_limit));


// 動作２

delay(1000);
pwm.setPWM(legLF3_pin, 0, map_angle(legLF3_angle.horizontal));
pwm.setPWM(legRF3_pin, 0, map_angle(legRF3_angle.horizontal)); 
delay(100);
pwm.setPWM(legLF2_pin, 0, map_angle(legLF2_angle.horizontal));
pwm.setPWM(legRF2_pin, 0, map_angle(legRF2_angle.horizontal));  

// 動作３

 delay(100);
// pwm.setPWM(legLF2_pin, 0, map_angle(legLF2_angle.beyond_upward_vertical));
// pwm.setPWM(legRF2_pin, 0, map_angle(legRF2_angle.beyond_upward_vertical));  
//  delay(100);
pwm.setPWM(legLF3_pin, 0, map_angle(legLF3_angle.frontward_vertical));
pwm.setPWM(legRF3_pin, 0, map_angle(legRF3_angle.frontward_vertical)); 

delay(100);
pwm.setPWM(legLF2_pin, 0, map_angle(legLF2_angle.beyond_horizontal));
pwm.setPWM(legRF2_pin, 0, map_angle(legRF2_angle.beyond_horizontal));  


// 動作４

delay(1000);

pwm.setPWM(legLF3_pin, 0, map_angle(legLF3_angle.downward_grounding));
pwm.setPWM(legRF3_pin, 0, map_angle(legRF3_angle.downward_grounding));    
delay(500);

pwm.setPWM(legLF2_pin, 0, map_angle(legLF2_angle.upward_vertical));
pwm.setPWM(legRF2_pin, 0, map_angle(legRF2_angle.upward_vertical));  
// //delay(1000);
}

void initialize_servo_degree(){

  while(true){

    pwm.setPWM(legLF3_pin, 0, map_angle(legLF3_angle.downward_grounding));
    pwm.setPWM(legLF2_pin, 0, map_angle(legLF2_angle.upward_vertical));
    pwm.setPWM(legLF1_pin, 0, map_angle(legLF1_angle.straight));

    //front right leg state
    pwm.setPWM(legRF3_pin, 0, map_angle(legRF3_angle.downward_grounding));     
    pwm.setPWM(legRF2_pin, 0, map_angle(legRF2_angle.upward_vertical));     
    pwm.setPWM(legRF1_pin, 0, map_angle(legRF1_angle.straight));

    //back left leg state
    pwm.setPWM(legLB_pin, 0, map_angle(legLB_angle.horizontal));
    
    //back right leg state
    pwm.setPWM(legRB_pin, 0, map_angle(legRB_angle.horizontal));

    delay(500);

  }

}
