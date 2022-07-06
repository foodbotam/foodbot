// Including libraries
#include <Servo.h>
#include <Wire.h>

// Motor name which is working now
String working_motor = "";

// All ultrasonic data combined
String ultrasonic_full_data = "";

// Defining servo pins
//  Bread
#define servo_1_pin 6
//  Tomato, sosage, cucumber
#define servo_2_pin 7
#define servo_3_pin 8
#define servo_4_pin 9
//  Ketchup and mayonnaise
#define servo_5_pin 10
#define servo_6_pin 11
// Salt and pepper
#define servo_7_pin 12
#define servo_8_pin 13

// Defining ultrasonic pins
#define ultrasonic_trig_pin 2
#define ultrasonic_1_pin 5
#define ultrasonic_2_pin 42
#define ultrasonic_3_pin 43
#define ultrasonic_4_pin 44

// Defining container variables
int container_1_length = 30;
int container_2_length = 30;
int container_3_length = 30;
int container_4_length = 30;
int container_5_length = 20;
int container_6_length = 20;
int container_7_length = 10;
int container_8_length = 10;

// Defining status codes

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

// Defining status information
#define status_pin  3
#define status_free  0
#define status_busy  255
#define status_waiting  80


// Defining ultrasonic values 
float ultrasonic_1_distance;
float ultrasonic_2_distance;
float ultrasonic_3_distance;
float ultrasonic_4_distance;
int ultrasonic_1_average_distance;
int ultrasonic_2_average_distance;
int ultrasonic_3_average_distance;
int ultrasonic_4_average_distance;

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
}

// Function which checks values of ultraonic sensors 
void update_average_distances()
{
  int number_of_checks = 4;
  int ultrasonic_1_distances[number_of_checks];
  int ultrasonic_2_distances[number_of_checks];
  int ultrasonic_3_distances[number_of_checks];
  int ultrasonic_4_distances[number_of_checks];
  for (int i = 0; i < number_of_checks; i++){
    update_all_ultrasonic_distances();
    ultrasonic_1_distances[i] = ultrasonic_1_distance;
    ultrasonic_2_distances[i] = ultrasonic_2_distance;
    ultrasonic_3_distances[i] = ultrasonic_3_distance;
    ultrasonic_4_distances[i] = ultrasonic_4_distance;
    Serial.print("Check: ");
    Serial.println(ultrasonic_1_distances[i]);
  }
  ultrasonic_1_average_distance = 0;
  ultrasonic_2_average_distance = 0;
  ultrasonic_3_average_distance = 0;
  ultrasonic_4_average_distance = 0;
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
  ultrasonic_1_average_distance /= number_of_checks;
  ultrasonic_2_average_distance /= number_of_checks;
  ultrasonic_3_average_distance /= number_of_checks;
  ultrasonic_4_average_distance /= number_of_checks;
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
}

// Function for using status
void use_status(int status_code = 0) {
  Serial.print("Status: ");
  Serial.println(status_code);
  analogWrite(status_pin, status_code);
  }

// Function which will reset working motor 
void reset_working_motor()
{
  working_motor = "";  
}

// Function for dropping bread
void drop_bread(int wait_time = 2000, int servo_rotation_count = 1)
{
    servo_1.write(180);
    delay(wait_time);
    servo_1.write(0);
    delay(wait_time);
    use_status(status_waiting);
}

// Function for cutting food
void cut_food(int number, int wait_time = 2000, int servo_rotation_count = 3)
{
  switch(number) {
  case 2:
    for (int i = 0; i < servo_rotation_count; i++) {
      servo_2.write(180);
      delay(wait_time);
      servo_2.write(0);
      delay(wait_time);
    }
    reset_working_motor();
    break;
  case 3:
    for (int i = 0; i < servo_rotation_count; i++) {
      servo_3.write(180);
      delay(wait_time);
      servo_3.write(0);
      delay(wait_time);
    }
    reset_working_motor();
    break;
  case 4:
    for (int i = 0; i < servo_rotation_count; i++) {
      servo_4.write(180);
      delay(wait_time);
      servo_4.write(0);
      delay(wait_time);
    }
    reset_working_motor();
    break;
  default:
    break;
  }
}

// Function for filling sauce
void fill_sauce(int number, int wait_time = 2000, int servo_rotation_count = 1)
{
    switch(number) {
    case 5:
      for (int i = 0; i < servo_rotation_count; i++) {
        servo_5.write(180);
        delay(wait_time);
        servo_5.write(0);
        delay(wait_time);
    }
      reset_working_motor();
      break;
    case 6:
      for (int i = 0; i < servo_rotation_count; i++) {
      servo_6.write(180);
      delay(wait_time);
      servo_6.write(0);
      delay(wait_time);
    }
      reset_working_motor();
      break;
    default:
      break;
    }
}

// Function for filling spices
void fill_spice(int number, int wait_time = 3000, int servo_rotation_count = 1)
{
    switch(number) {
    case 7:
      for (int i = 0; i < servo_rotation_count; i++) {
      servo_7.write(180);
      delay(wait_time);
      servo_7.write(0);
      delay(wait_time);
    }
      reset_working_motor();
      break;
    case 8:
      for (int i = 0; i < servo_rotation_count; i++) {
      servo_8.write(180);
      delay(wait_time);
      servo_8.write(0);
      delay(wait_time);
    }
      reset_working_motor();
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

void receiveEvent(int howMany) {
  String command = "";
 while (0 < Wire.available()) {
    char c = Wire.read();
    command.concat(c);
  }
  Serial.println(command);
  if (command=="49"){
    working_motor = "1";
  }
  else if (command=="50"){
    working_motor = "2";
  }
  else if (command=="51"){
    working_motor = "3";
  }
  else if (command=="52"){
    working_motor = "4";
  }
  else if (command=="53"){
    working_motor = "5";
  }
  else if (command=="54"){
    working_motor = "6";
  }
  else if (command=="55"){
    working_motor = "7";
  }
  else if (command=="56"){
    working_motor = "8";
  }
  
  
}

// Function that executes whenever data is requested from master
void requestEvent() {
 Wire.write("");
}



void setup() {
  // Starting communication with esp
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  // Defining pin types
  pinMode(ultrasonic_1_pin, INPUT);
  pinMode(ultrasonic_2_pin, INPUT);
  pinMode(ultrasonic_3_pin, INPUT);
  pinMode(ultrasonic_4_pin, INPUT);
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
  Serial.begin(9600);
  // Reseting servos
  reset_servos();
}




void loop() {
  Serial.print("Command is ");
  Serial.println(working_motor);
  if (working_motor == "1"){
    drop_bread();
  }
  else if (working_motor == "2"){
    cut_food(2);
  }
  else if (working_motor == "3"){
    cut_food(3);
  }
  else if (working_motor == "4"){
    cut_food(4);
  }
  else if (working_motor == "5"){
    fill_sauce(5);
  }
  else if (working_motor == "6"){
    fill_sauce(6);
  }
  else if (working_motor == "7"){
    fill_spice(7);
  }
  else if (working_motor == "8"){
    fill_spice(8);
  }
  
}
