#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 135    // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 430    // this is the 'maximum' pulse length count (out of 4096)

#define map_leg1_angle(angle) map(angle, 0, 165, SERVOMIN, SERVOMAX)
#define map_leg2_angle(angle) map(angle, 0, 165, SERVOMAX, SERVOMIN)

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
};

struct leg2_servo_angles {
  int down;
  int abovedown;
  int lowerhoraizontal;
  int horaizontal;
  int up;
};

leg1_servo_angles legLF1_angle  ={15, 45, 60, 75, 105};
leg1_servo_angles legRF1_angle  ={150, 120, 105, 90, 60};
leg1_servo_angles legLB1_angle  ={150, 120, 105, 90, 60};
leg1_servo_angles legRB1_angle  ={15, 45, 60, 75, 105};

leg2_servo_angles legLF2_angle  ={0, 30, 60, 105, 165};
leg2_servo_angles legRF2_angle  ={0, 30, 60, 105, 165};
leg2_servo_angles legLB2_angle  ={0, 30, 60, 105, 165};
leg2_servo_angles legRB2_angle  ={0, 30, 60, 105, 165};


int Left_TRIG = 3;
int Left_ECHO = 2;
int Right_TRIG = 5;
int Right_ECHO = 4;

double Left_duration = 0;
double Left_distance = 0;
double Right_duration = 0;
double Right_distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25; // 25℃の気温の想定

void setup() {
  
    pwm.begin();
    pwm.setPWMFreq(50);  // analog servos run at 50Hz updates

    //front left leg state
//    pwm.setPWM(legLF2_pin, 0, map_leg2_angle(legLF2_angle.down));
//    pwm.setPWM(legLF1_pin, 0, map_leg1_angle(legLF1_angle.straight));

    //front right leg state
    pwm.setPWM(legRF2_pin, 0, map_leg2_angle(legRF2_angle.down));     
    pwm.setPWM(legRF1_pin, 0, map_leg1_angle(legRF1_angle.straight));

    //back left leg state
//    pwm.setPWM(legLB2_pin, 0, map_leg2_angle(legLB2_angle.down));
//    pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.middle));
    
    //back right leg state
    pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.down));
    pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.straight));

    Serial.begin( 9600 );

    pinMode(Left_ECHO, INPUT );
    pinMode(Left_TRIG, OUTPUT );

    pinMode(Right_ECHO, INPUT );
    pinMode(Right_TRIG, OUTPUT );

}
      
//here is movement of creepgates
void loop() {

    
  pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.horaizontal));
  pwm.setPWM(legRF2_pin, 0, map_leg2_angle(legRF2_angle.horaizontal));

  digitalWrite(Left_TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite( Left_TRIG, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite( Left_TRIG, LOW );
  Left_duration = pulseIn( Left_ECHO, HIGH );

  //if (Left_duration <= 0 ) return;

  Left_distance = (Left_duration * 0.5) * speed_of_sound * 100.0 / 1000000.0;

  Serial.print("Left_Distance:");
  Serial.print(Left_distance);
  Serial.print(" cm,");

  
  digitalWrite(Right_TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite(Right_TRIG, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite(Right_TRIG, LOW );
  Right_duration = pulseIn(Right_ECHO, HIGH );

  //if (Right_duration <= 0 ) return;

  Right_distance = (Right_duration * 0.5) * speed_of_sound * 100.0 / 1000000.0;

  Serial.print("Right_Distance:");
  Serial.print(Right_distance);
  Serial.println(" cm,");
    
  if(Right_distance > 50 && Right_distance < 100)//適当に変える
  {

  pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.down));
  //右脚をのばす

  delay(3000);

  return;
  }

  if(Left_distance > 50 && Left_distance < 100)//適当に変える
  {

  pwm.setPWM(legRF2_pin, 0, map_leg2_angle(legRF2_angle.down));
  //左脚をのばす

  delay(3000);

  return;
  }

  delay(200);
  
  pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.horaizontal));
  pwm.setPWM(legRF2_pin, 0, map_leg2_angle(legRF2_angle.horaizontal));
  delay(200);

  //脚を戻そう

    // pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.horaizontal));
    // delay(500);
    // pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.side));
    // delay(500);
    // pwm.setPWM(legRB2_pin, 0, map_leg2_angle(legRB2_angle.down));
    // delay(500);

    // pwm.setPWM(legRF2_pin, 0, map_leg2_angle(legRF2_angle.horaizontal));
    // delay(300);
    // pwm.setPWM(legRF1_pin, 0, map_leg1_angle(legRF1_angle.straight));
    // delay(200);
    // pwm.setPWM(legRF2_pin, 0, map_leg2_angle(legRF2_angle.down));  
    // pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.straight));
    // pwm.setPWM(legLF1_pin, 0, map_leg1_angle(legLF1_angle.side));
    // pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.straight));
    // delay(400);

    // pwm.setPWM(legLB2_pin, 0, map_leg2_angle(legLB2_angle.horaizontal));
    // delay(400);
    // pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.side));
    // delay(400);
    // pwm.setPWM(legLB2_pin, 0, map_leg2_angle(legRB2_angle.abovedown));
    // delay(400);

    // pwm.setPWM(legLF2_pin, 0, map_leg2_angle(legLF2_angle.horaizontal));
    // delay(300);
    // pwm.setPWM(legLF1_pin, 0, map_leg1_angle(legLF1_angle.straight));
    // delay(200);
    // pwm.setPWM(legLF2_pin, 0, map_leg2_angle(legLF2_angle.down));  
    // pwm.setPWM(legRB1_pin, 0, map_leg1_angle(legRB1_angle.straight));
    // pwm.setPWM(legRF1_pin, 0, map_leg1_angle(legRF1_angle.side));
    // pwm.setPWM(legLB1_pin, 0, map_leg1_angle(legLB1_angle.straight));
    // delay(400);

}
