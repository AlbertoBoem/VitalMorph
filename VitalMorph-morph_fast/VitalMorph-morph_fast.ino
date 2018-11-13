/*
To use:
Arduino Mega
7 + 7 servo motors

Alberto Boem
Kai Sasaki
2016
University of Tsukuba
*/
 
 
 
#include <VarSpeedServo.h> 
#include <Utility.h>

VarSpeedServo myservo1,myservo2,myservo3,myservo4,myservo5,myservo6,myservo7;
VarSpeedServo myservo8,myservo9,myservo10,myservo11,myservo12,myservo13,myservo14;

int motor_init_speed = 255;//0-255
int motor_init_angle = 22.5;
int motor_speed = 0;

int servo_number1 = 2;int servo_number8 = 9;
int servo_number2 = 3;int servo_number9 = 10;
int servo_number3 = 4;int servo_number10 = 11;
int servo_number4 = 5;int servo_number11 = 12;
int servo_number5 = 6;int servo_number12 = 13;
int servo_number6 = 7;int servo_number13 = 38;
int servo_number7 = 8;int servo_number14 = 40;

int read_angle_delay = 0;
int motor_activation_delay = 10;
int threshold = 1;
int threshold_angle = 0;
int max_value = 495;
int min_value = 85;

int potpin = 0;   int val = 0; 
int potpin2 = 1;  int val2 = 0;
int potpin3 = 2;  int val3 = 0; 
int potpin4 = 3;  int val4 = 0; 
int potpin5 = 4;  int val5 = 0; 
int potpin6 = 5;  int val6 = 0;
int potpin7 = 6;  int val7 = 0; 
int potpin8 = 15;  int val8 = 0;
int potpin9 = 8;  int val9 = 0; 
int potpin10 = 9; int val10 = 0; 
int potpin11 = 10; int val11 = 0; 
int potpin12 = 11; int val12 = 0;
int potpin13 = 12; int val13 = 0; 
int potpin14 = 13; int val14 = 0;

int preval = 0;int preval2 = 0;
int preval3 = 0;int preval4 = 0;
int preval5 = 0;int preval6 = 0;
int preval7 = 0;int preval8 = 0;
int preval9 = 0;int preval10 = 0;
int preval11 = 0;int preval12 = 0;
int preval13 = 0;int preval14 = 0;

int count = 0;
int count_limit = 1;
boolean Action_flag = false;

boolean servo_flag = false;boolean servo2_flag = false;
boolean servo3_flag = false;boolean servo4_flag = false;
boolean servo5_flag = false;boolean servo6_flag = false;
boolean servo7_flag = false;boolean servo8_flag = false;
boolean servo9_flag = false;boolean servo10_flag = false;
boolean servo11_flag = false;boolean servo12_flag = false;
boolean servo13_flag = false;boolean servo14_flag = false;


void setup() 
{ 

  pinMode(servo_number1, OUTPUT);pinMode(servo_number2, OUTPUT);
  pinMode(servo_number3, OUTPUT);pinMode(servo_number4, OUTPUT);
  pinMode(servo_number5, OUTPUT);pinMode(servo_number6, OUTPUT);
  pinMode(servo_number7, OUTPUT);pinMode(servo_number8, OUTPUT);
  pinMode(servo_number9, OUTPUT);pinMode(servo_number10, OUTPUT);
  pinMode(servo_number11, OUTPUT);pinMode(servo_number12, OUTPUT);
  pinMode(servo_number13, OUTPUT);pinMode(servo_number14, OUTPUT);
  
  Serial.begin(9600);
  setADCFrequency(ADC_DIV16);
  
  myservo1.attach(servo_number1);myservo2.attach(servo_number2);
  myservo3.attach(servo_number3);myservo4.attach(servo_number4);
  myservo5.attach(servo_number5);myservo6.attach(servo_number6);
  myservo7.attach(servo_number7);myservo8.attach(servo_number8);
  myservo9.attach(servo_number9);myservo10.attach(servo_number10);
  myservo11.attach(servo_number11);myservo12.attach(servo_number12);
  myservo13.attach(servo_number13);myservo14.attach(servo_number14);

  delay(500);

  myservo1.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo2.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo3.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo4.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo5.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo6.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo7.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo8.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo9.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo10.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo11.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo12.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo13.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay);
  myservo14.write(motor_init_angle,motor_init_speed,true);

  delay(100);

  myservo1.detach();myservo2.detach();
  myservo3.detach();myservo4.detach();
  myservo5.detach();myservo6.detach();
  myservo7.detach();myservo8.detach();
  myservo9.detach();myservo10.detach();
  myservo11.detach();myservo12.detach();
  myservo13.detach();myservo14.detach();

} 

void loop() 
{ 
 
  if(Serial.available() > 0){
    int c = Serial.read();
    if(c == 'D'){ 
  myservo1.attach(servo_number1);myservo2.attach(servo_number2);
  myservo3.attach(servo_number3);myservo4.attach(servo_number4);
  myservo5.attach(servo_number5);myservo6.attach(servo_number6);
  myservo7.attach(servo_number7);myservo8.attach(servo_number8);
  myservo9.attach(servo_number9);myservo10.attach(servo_number10);
  myservo11.attach(servo_number11);myservo12.attach(servo_number12);
  myservo13.attach(servo_number13);myservo14.attach(servo_number14);

  delay(500);
 // for(int i = 0;i < 10; i++){
int wait = 5;
  //myservo1.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  myservo8.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  //myservo2.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  myservo9.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  //myservo3.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  myservo10.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  //myservo4.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  myservo11.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  //myservo5.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  myservo12.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  //myservo6.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  myservo13.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  //myservo7.write(motor_init_angle,motor_init_speed,true);
  delay(motor_activation_delay*wait);
  myservo14.write(motor_init_angle,motor_init_speed,true);

  delay(100);
  }
  myservo1.detach();myservo2.detach();
  myservo3.detach();myservo4.detach();
  myservo5.detach();myservo6.detach();
  myservo7.detach();myservo8.detach();
  myservo9.detach();myservo10.detach();
  myservo11.detach();myservo12.detach();
  myservo13.detach();myservo14.detach();

    } 
  //}
  
  val = analogRead(potpin);delay(read_angle_delay);
  val2 = analogRead(potpin2);delay(read_angle_delay);
  val3 = analogRead(potpin3);delay(read_angle_delay);
  val4 = analogRead(potpin4);delay(read_angle_delay);
  val5 = analogRead(potpin5);delay(read_angle_delay);
  val6 = analogRead(potpin6);delay(read_angle_delay);
  val7 = analogRead(potpin7);delay(read_angle_delay);
  val8 = analogRead(potpin8);delay(read_angle_delay);
  val9 = analogRead(potpin9);delay(read_angle_delay);
  val10 = analogRead(potpin10);delay(read_angle_delay);
  val11 = analogRead(potpin11);delay(read_angle_delay);
  val12 = analogRead(potpin12);delay(read_angle_delay);
  val13 = analogRead(potpin13);delay(read_angle_delay);
  val14 = analogRead(potpin14);delay(read_angle_delay);
 
 
  val = map(val, min_value, max_value, 0, 180);val = constrain(val,0,180);
  val2 = map(val2, min_value, max_value, 0, 180);val2 = constrain(val2,0,180);
  val3 = map(val3, min_value, max_value, 0, 180);val3 = constrain(val3,0,180);
  val4 = map(val4, min_value, max_value, 0, 180);val4 = constrain(val4,0,180);
  val5 = map(val5, min_value, max_value, 0, 180);val5 = constrain(val5,0,180);
  val6 = map(val6, min_value, max_value, 0, 180);val6 = constrain(val6,0,180);
  val7 = map(val7, min_value, max_value, 0, 180);val7 = constrain(val7,0,180);
  val8 = map(val8, min_value, max_value, 0, 180);val8 = constrain(val8,0,180);
  val9 = map(val9, min_value, max_value, 0, 180);val9 = constrain(val9,0,180);
  val10 = map(val10, min_value, max_value, 0, 180);val10 = constrain(val10,0,180);
  val11 = map(val11, min_value, max_value, 0, 180);val11 = constrain(val11,0,180);
  val12 = map(val12, min_value, max_value, 0, 180);val12 = constrain(val12,0,180);
  val13 = map(val13, min_value, max_value, 0, 180);val13 = constrain(val13,0,180);
  val14 = map(val14, min_value, max_value, 0, 180);val14 = constrain(val14,0,180);
  
   
   
 
   Serial.print("val =");Serial.print(val);
   Serial.print("val2 =");Serial.print(val2);
   Serial.print("val3 =");Serial.print(val3);
   Serial.print("val4 =");Serial.print(val4);
   Serial.print("val5 =");Serial.print(val5);
   Serial.print("val6 =");Serial.print(val6);
   Serial.print("val7 =");Serial.print(val7);
   Serial.print("val8 =");Serial.print(val8);
   Serial.print("val9 =");Serial.print(val9);
   Serial.print("val10 =");Serial.print(val10);
   Serial.print("val11 =");Serial.print(val11);
   Serial.print("val12 =");Serial.print(val12);
   Serial.print("val13 =");Serial.print(val13);
   Serial.print("val14 =");Serial.print(val14);
   Serial.println(); 
   
  
  if(count == count_limit){
    Action_flag = true;
    count = 0; 
  }
  count++;
  
  int average  =  val;int average2 =  val2;
  int average3 =  val3;int average4 =  val4;
  int average5 =  val5;int average6 =  val6;
  int average7  =  val7;int average8 =  val8;
  int average9 =  val9;int average10 =  val10;
  int average11 =  val11;int average12 =  val12;
  int average13 =  val13;int average14 =  val14;

/*
   Serial.print("val =");Serial.print(average-preval);
   Serial.print("val2 =");Serial.print(average2-preval2);
   Serial.print("val3 =");Serial.print(average3-preval3);
   Serial.print("val4 =");Serial.print(average4-preval4);
   Serial.print("val5 =");Serial.print(average5-preval5);
   Serial.print("val6 =");Serial.print(average6-preval6);
   Serial.print("val7 =");Serial.print(average7-preval7);
   Serial.print("val8 =");Serial.print(average8-preval8);
   Serial.print("val9 =");Serial.print(average9-preval9);
   Serial.print("val10 =");Serial.print(average10-preval10);
   Serial.print("val11 =");Serial.print(average11-preval11);
   Serial.print("val12 =");Serial.print(average12-preval12);
   Serial.print("val13 =");Serial.print(average13-preval13);
   Serial.print("val14 =");Serial.print(average14-preval14);
   Serial.println(); 
*/
/*Memo
 & 7
2 & 8
3 & 9
4 & 10
5 & 11
6 & 12
*/


  
 
 
 /*
 if(Action_flag && (abs(average-average8) > threshold)){
    servo_flag = false;
    myservo8.attach(servo_number8);
    myservo8.writeMicroseconds(((2500-500)/180)*average+500);
    Serial.println("Yeeeeeeeeeeeeees"); 
    delay(motor_activation_delay);
    myservo8.detach();
  }
  */
  /*
  else if(Action_flag && (abs(average8-preval8) > threshold)){
    servo8_flag = false;
    myservo1.attach(servo_number1);
    myservo1.write(average8,motor_init_speed,true);
     
     delay(motor_activation_delay);
     myservo1.detach();
  }
  */
 

  if(Action_flag && (abs(average-preval) > threshold) && abs(average-average8) > threshold_angle && servo8_flag){
    servo_flag = false;
    myservo8.attach(servo_number8);
    myservo8.write(average,motor_init_speed,true);
    //myservo8.writeMicroseconds(((2500-500)/180)*average+500);
    delay(motor_activation_delay);
    myservo8.detach();
    //try
    digitalWrite(servo_number8, LOW);
    
  } else if(Action_flag && (abs(average8-preval8) > threshold) && abs(average-average8) > threshold_angle&& servo_flag){
    servo8_flag = false;
    myservo1.attach(servo_number1);
    //myservo1.writeMicroseconds(((2500-500)/180)*average8+500);
    myservo1.write(average8,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo1.detach();
    //try
    digitalWrite(servo_number1, LOW);
  }

  if(Action_flag && (abs(average2-preval2) > threshold && abs(average2-average9) > threshold_angle) && servo9_flag){
    servo2_flag = false;
    myservo9.attach(servo_number9);
    myservo9.write(average2,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo9.detach();
    //try
    digitalWrite(servo_number9, LOW);
    
  }else if(Action_flag && (abs(average9-preval9) > threshold && abs(average2-average9) > threshold_angle) && servo2_flag){
    servo9_flag = false;
    myservo2.attach(servo_number2);
    myservo2.write(average9,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo2.detach();
    //try
    digitalWrite(servo_number2, LOW);
  }
  
  if(Action_flag && (abs(average3-preval3) > threshold && abs(average3-average10) > threshold_angle) && servo10_flag){
    servo3_flag = false;
    myservo10.attach(servo_number10);
    myservo10.write(average3,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo10.detach();
    
  } else if(Action_flag && (abs(average10-preval10) > threshold && abs(average3-average10) > threshold_angle) && servo3_flag){
    servo10_flag = false;
    myservo3.attach(servo_number3);
    myservo3.write(average10,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo3.detach();
    //try
    digitalWrite(servo_number3, LOW);
    
  }
  
  if(Action_flag && (abs(average4-preval4) > threshold && abs(average4-average11) > threshold_angle) && servo11_flag){
    servo4_flag = false;
    myservo11.attach(servo_number11);
    myservo11.write(average4,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo11.detach();
    //try
    digitalWrite(servo_number11, LOW);
    
  } else if(Action_flag && (abs(average11-preval11) > threshold && abs(average4-average11) > threshold_angle) && servo4_flag){
    servo11_flag = false;
    myservo4.attach(servo_number4);
    myservo4.write(average11,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo4.detach();
    //try
    digitalWrite(servo_number4, LOW);
  }
  
  if(Action_flag && (abs(average5-preval5) > threshold && abs(average5-average12) > threshold_angle) && servo12_flag){
    servo5_flag = false;
    myservo12.attach(servo_number12);
    myservo12.write(average5,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo12.detach();
    //try
    digitalWrite(servo_number12, LOW);
    
  } else if(Action_flag && (abs(average12-preval12) > threshold && abs(average5-average12) > threshold_angle) && servo5_flag){
    servo12_flag = false;
    myservo5.attach(servo_number5);
    myservo5.write(average12,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo5.detach();
    //try
    digitalWrite(servo_number5, LOW);
  }
  
  if(Action_flag && (abs(average6-preval6) > threshold && abs(average6-average13) > threshold_angle) && servo13_flag){
    servo6_flag = false;
    myservo13.attach(servo_number13);
    myservo13.write(average6,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo13.detach();
    //try
    digitalWrite(servo_number13, LOW);
    
  } else if(Action_flag && (abs(average13-preval13) > threshold && abs(average6-average13) > threshold_angle) && servo6_flag){
    servo13_flag = false;
    myservo6.attach(servo_number6);
    myservo6.write(average13,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo6.detach();
    //try
    digitalWrite(servo_number6, LOW);
  }

  if(Action_flag && (abs(average7-preval7) > threshold && abs(average7-average14) > threshold_angle) && servo14_flag){
    servo7_flag = false;
    myservo14.attach(servo_number14);
    myservo14.write(average7,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo14.detach();
    //try
    digitalWrite(servo_number14, LOW);
    
  } else if(Action_flag && (abs(average14-preval14) > threshold && abs(average7-average14) > threshold_angle) && servo7_flag){
    servo14_flag = false;
    myservo7.attach(servo_number7);
    myservo7.write(average14,motor_init_speed,true);
    delay(motor_activation_delay);
    myservo7.detach();
    //try
    digitalWrite(servo_number7, LOW);
  }

  if(abs(average-preval) == 0 && abs(average8-preval8) == 0){
    servo_flag = true;
    servo8_flag = true;
    myservo1.detach();
    myservo8.detach();
  }
  
  if(abs(average2-preval2) == 0 && abs(average9-preval9) == 0){
    servo2_flag = true;
    servo9_flag = true;
    myservo2.detach();
    myservo9.detach();
  }
  if(abs(average3-preval3) == 0 && abs(average10-preval10) == 0){
    servo3_flag = true;
    servo10_flag = true;
    myservo3.detach();
    myservo10.detach();
  }
  if(abs(average4-preval4) == 0 && abs(average11-preval11) == 0){
    servo4_flag = true;
    servo11_flag = true;
    myservo4.detach();
    myservo11.detach();
  }
  if(abs(average5-preval5) == 0 && abs(average12-preval12) == 0){
    servo5_flag = true;
    servo12_flag = true;
    myservo5.detach();
    myservo12.detach();
  }
  if(abs(average6-preval6) == 0 && abs(average13-preval13) == 0){
    servo6_flag = true;
    servo13_flag = true;
    myservo6.detach();
    myservo13.detach();
  }
  if(abs(average7-preval7) == 0 && abs(average14-preval14) == 0){
    servo7_flag = true;
    servo14_flag = true;
    myservo7.detach();
    myservo14.detach();
  }

  preval = average;preval2 = average2;
  preval3 = average3;preval4 = average4;
  preval5 = average5;preval6 = average6;
  preval7 = average7;preval8 = average8;
  preval9 = average9;preval10 = average10;
  preval11 = average11;preval12 = average12;
  preval13 = average13;preval14 = average14;
  
} 

