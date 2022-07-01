// Including libraries
#include <Servo.h>

// Defining servo pins
//  Bread
#define servo_1_pin 1
//  Tomato, sosage, cucumber
#define servo_2_pin 2
#define servo_3_pin 3
#define servo_4_pin 4
//  Ketchup and mayonnaise
#define servo_5_pin 5
#define servo_6_pin 6
// Salt and pepper
#define servo_7_pin 7 
#define servo_8_pin 8

// Defining ultrasonic pins
#define ultrasonic_trig_pin 10
#define ultrasonic_1_pin 11
#define ultrasonic_2_pin 12
#define ultrasonic_3_pin 13
#define ultrasonic_4_pin 14
#define ultrasonic_5_pin 15
#define ultrasonic_6_pin 16
#define ultrasonic_7_pin 17
#define ultrasonic_8_pin 18

// Defining servo motor pins
#define servo_1_pin 1
#define servo_2_pin 2
#define servo_3_pin 3
#define servo_4_pin 4
#define servo_5_pin 5
#define servo_6_pin 6
#define servo_7_pin 7
#define servo_8_pin 8

// Defining container variables
int container_1_length = 30;
int container_2_length = 30;
int container_3_length = 30;
int container_4_length = 30;
int container_5_length = 20;
int container_6_length = 20;
int container_7_length = 10;
int container_8_length = 10;

// Defining container status variables
int container_1_status;
int container_2_status;
int container_3_status;
int container_4_status;
int container_5_status;
int container_6_status;
int container_7_status;
int container_8_status;

// Defining servo pins
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5;
Servo servo_6;
Servo servo_7;
Servo servo_8;

// Defining ultrasonic values 
float ultrasonic_1_distance;
float ultrasonic_2_distance;
float ultrasonic_3_distance;
float ultrasonic_4_distance;
float ultrasonic_5_distance;
float ultrasonic_6_distance;
float ultrasonic_7_distance;
float ultrasonic_8_distance;
int ultrasonic_1_average_distance;
int ultrasonic_2_average_distance;
int ultrasonic_3_average_distance;
int ultrasonic_4_average_distance;
int ultrasonic_5_average_distance;
int ultrasonic_6_average_distance;
int ultrasonic_7_average_distance;  
int ultrasonic_8_average_distance;  

// Function for sending trig
void activate_trig()
{
  digitalWrite(ultrasonic_trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonic_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonic_trig_pin, LOW);
}

// Function which waits voice to return and returns distance
float get_distance(int ultrasonic_pin)
{
  // Activating trig pin
  activate_trig();
  // Declaring variables for calculating
  long duration;
  float distance;
  // Doing calculation using voice speed
  duration = pulseIn(ultrasonic_pin, HIGH);
  distance = duration * 0.034 / 2;
  delay(100);
  return distance;
}

// Function for getting all ultrasonic distances in one list and returning it
void update_all_ultrasonic_distances()
{
  ultrasonic_1_distance = get_distance(ultrasonic_1_pin);
  ultrasonic_2_distance = get_distance(ultrasonic_2_pin);
  ultrasonic_3_distance = get_distance(ultrasonic_3_pin);
  ultrasonic_4_distance = get_distance(ultrasonic_4_pin);
  ultrasonic_5_distance = get_distance(ultrasonic_5_pin);
  ultrasonic_6_distance = get_distance(ultrasonic_6_pin);
  ultrasonic_7_distance = get_distance(ultrasonic_7_pin);
  ultrasonic_8_distance = get_distance(ultrasonic_8_pin);
}

// Function which checks values of ultraonic sensors 
void update_average_distances()
{
  int number_of_checks = 4;
  int ultrasonic_1_distances[number_of_checks];
  int ultrasonic_2_distances[number_of_checks];
  int ultrasonic_3_distances[number_of_checks];
  int ultrasonic_4_distances[number_of_checks];
  int ultrasonic_5_distances[number_of_checks];
  int ultrasonic_6_distances[number_of_checks];
  int ultrasonic_7_distances[number_of_checks];
  int ultrasonic_8_distances[number_of_checks];
  for (int i = 0; i < number_of_checks; i++){
    update_all_ultrasonic_distances();
    ultrasonic_1_distances[i] = ultrasonic_1_distance;
    ultrasonic_2_distances[i] = ultrasonic_2_distance;
    ultrasonic_3_distances[i] = ultrasonic_3_distance;
    ultrasonic_4_distances[i] = ultrasonic_4_distance;
    ultrasonic_5_distances[i] = ultrasonic_5_distance;
    ultrasonic_6_distances[i] = ultrasonic_6_distance;
    ultrasonic_7_distances[i] = ultrasonic_7_distance;
    ultrasonic_8_distances[i] = ultrasonic_8_distance;
    Serial.print("Check: ");
    Serial.println(ultrasonic_1_distances[i]);
  }
  ultrasonic_1_average_distance = 0;
  ultrasonic_2_average_distance = 0;
  ultrasonic_3_average_distance = 0;
  ultrasonic_4_average_distance = 0;
  ultrasonic_5_average_distance = 0;
  ultrasonic_6_average_distance = 0;
  ultrasonic_7_average_distance = 0;
  ultrasonic_8_average_distance = 0;
  int food_check_values[7];
  for (int i = 0; i < number_of_checks; i++){
    ultrasonic_1_average_distance += ultrasonic_1_distances[i];
  }
  for (int i = 0; i < number_of_checks; i++){
    ultrasonic_2_average_distance += ultrasonic_2_distances[i];
  }
  for (int i = 0; i < number_of_checks; i++){
    ultrasonic_3_average_distance += ultrasonic_3_distances[i];
  }
  for (int i = 0; i < number_of_checks; i++){
    ultrasonic_4_average_distance += ultrasonic_4_distances[i];
  }
  for (int i = 0; i < number_of_checks; i++){
    ultrasonic_5_average_distance += ultrasonic_5_distances[i];
  }
  for (int i = 0; i < number_of_checks; i++){
    ultrasonic_6_average_distance += ultrasonic_6_distances[i];
  }
  for (int i = 0; i < number_of_checks; i++){
    ultrasonic_7_average_distance += ultrasonic_7_distances[i];
  }
  for (int i = 0; i < number_of_checks; i++){
    ultrasonic_8_average_distance += ultrasonic_8_distances[i];
  }
  ultrasonic_1_average_distance /= number_of_checks;
  ultrasonic_2_average_distance /= number_of_checks;
  ultrasonic_3_average_distance /= number_of_checks;
  ultrasonic_4_average_distance /= number_of_checks;
  ultrasonic_5_average_distance /= number_of_checks;
  ultrasonic_6_average_distance /= number_of_checks;
  ultrasonic_7_average_distance /= number_of_checks;
  ultrasonic_8_average_distance /= number_of_checks;
  Serial.println(ultrasonic_1_average_distance);
}

// Function which will return if there is food or not
void update_containers_status()
{
  update_average_distances();
  container_1_status = (map(ultrasonic_1_average_distance,0,container_1_length,10,0) >= 0) ? map(ultrasonic_1_average_distance,0,container_1_length,10,0) : 11;
  container_2_status = (map(ultrasonic_2_average_distance,0,container_2_length,10,0) >= 0) ? map(ultrasonic_2_average_distance,0,container_2_length,10,0) : 11;
  container_3_status = (map(ultrasonic_3_average_distance,0,container_3_length,10,0) >= 0) ? map(ultrasonic_3_average_distance,0,container_3_length,10,0) : 11;
  container_4_status = (map(ultrasonic_4_average_distance,0,container_4_length,10,0) >= 0) ? map(ultrasonic_4_average_distance,0,container_4_length,10,0) : 11;
  container_5_status = (map(ultrasonic_5_average_distance,0,container_5_length,10,0) >= 0) ? map(ultrasonic_5_average_distance,0,container_5_length,10,0) : 11;
  container_6_status = (map(ultrasonic_6_average_distance,0,container_6_length,10,0) >= 0) ? map(ultrasonic_6_average_distance,0,container_6_length,10,0) : 11;
  container_7_status = (map(ultrasonic_7_average_distance,0,container_7_length,10,0) >= 0) ? map(ultrasonic_7_average_distance,0,container_7_length,10,0) : 11;
  container_8_status = (map(ultrasonic_8_average_distance,0,container_8_length,10,0) >= 0) ? map(ultrasonic_8_average_distance,0,container_8_length,10,0) : 11;
}

// Function for dropping bread
void drop_bread()
{
    servo_1.write(180);
    delay(1000);
    servo_1.write(0);
    delay(1000);
}

// Function for cutting food
void cut_food(int number)
{
  switch(number) {
  case 2:
    servo_2.write(180);
    delay(1000);
    servo_2.write(0);
    delay(1000);
    break;
  case 3:
    servo_3.write(180);
    delay(1000);
    servo_3.write(0);
    delay(1000);
    break;
  case 4:
    servo_4.write(180);
    delay(1000);
    servo_4.write(0);
    delay(1000);
    break;
  default:
    break;
  }
}

// Function for filling sauce
void fill_sauce(int number, int wait_time = 2000)
{
    switch(number) {
    case 5:
      servo_5.write(180);
      delay(wait_time);
      servo_5.write(0);
      delay(1000);
      break;
    case 6:
      servo_6.write(180);
      delay(wait_time);
      servo_6.write(0);
      delay(1000);
      break;
    default:
      break;
    }
}

// Function for filling spices
void fill_spice(int number)
{
    switch(number) {
    case 7:
      servo_7.write(180);
      delay(1000);
      servo_7.write(0);
      delay(1000);
      break;
    case 8:
      servo_8.write(180);
      delay(1000);
      servo_8.write(0);
      delay(1000);
      break;
    default:
      break;
    }
}

// Function for resetting all servos to angle 0
void reset_servos()
{
    servo_1.write(0);
    servo_2.write(0);
    servo_3.write(0);
    servo_4.write(0);
    servo_5.write(0);
    servo_6.write(0);
    servo_7.write(0);
    servo_8.write(0);
    delay(1000);
}


void setup() {
  // Defining pin types
  pinMode(ultrasonic_1_pin, INPUT);
  pinMode(ultrasonic_2_pin, INPUT);
  pinMode(ultrasonic_3_pin, INPUT);
  pinMode(ultrasonic_4_pin, INPUT);
  pinMode(ultrasonic_5_pin, INPUT);
  pinMode(ultrasonic_6_pin, INPUT);
  pinMode(ultrasonic_7_pin, INPUT);
  pinMode(ultrasonic_trig_pin, OUTPUT);
  // Attaching servos
  servo_1.attach(servo_1_pin);
  servo_2.attach(servo_2_pin);
  servo_3.attach(servo_3_pin);
  servo_4.attach(servo_4_pin);
  servo_5.attach(servo_5_pin);
  servo_6.attach(servo_6_pin);
  servo_7.attach(servo_7_pin);
  servo_8.attach(servo_8_pin);
  // Starting serial monitor for communication
  Serial.begin(115200);
  // Reseting servos
  Serial.print("Sksuma");
  reset_servos();
  Serial.println("Sksav");
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println("Check started" );
//  update_containers_status();
//  Serial.print("Status: ");
//  Serial.println(container_2_status);
//  Serial.println("Check finished" );
//  delay(200);
    delay(2000);
    cut_food(2);
    delay(2000);
}
