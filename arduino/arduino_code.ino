// Including libraries

// Defining ultrasonic pins
#define ultrasonic_trig_pin 10
#define ultrasonic_1_pin 11
#define ultrasonic_2_pin 12
#define ultrasonic_3_pin 13
#define ultrasonic_4_pin 14
#define ultrasonic_5_pin 15
#define ultrasonic_6_pin 16
#define ultrasonic_7_pin 17

// Defining servo motor pins
#define servo_1_pin 1
#define servo_2_pin 2
#define servo_3_pin 3
#define servo_4_pin 4
#define servo_5_pin 5
#define servo_6_pin 6
#define servo_7_pin 7

// Defining container variables
int container_1_length = 30;
int container_2_length = 30;
int container_3_length = 30;
int container_4_length = 20;
int container_5_length = 20;
int container_6_length = 10;
int container_7_length = 10;

// Defining container status variables
int container_1_status;
int container_2_status;
int container_3_status;
int container_4_status;
int container_5_status;
int container_6_status;
int container_7_status;

// Defining ultrasonic values 
float ultrasonic_1_distance;
float ultrasonic_2_distance;
float ultrasonic_3_distance;
float ultrasonic_4_distance;
float ultrasonic_5_distance;
float ultrasonic_6_distance;
float ultrasonic_7_distance;  
int ultrasonic_1_average_distance;
int ultrasonic_2_average_distance;
int ultrasonic_3_average_distance;
int ultrasonic_4_average_distance;
int ultrasonic_5_average_distance;
int ultrasonic_6_average_distance;
int ultrasonic_7_average_distance;  

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
  for (int i = 0; i < number_of_checks; i++){
    update_all_ultrasonic_distances();
    ultrasonic_1_distances[i] = ultrasonic_1_distance;
    ultrasonic_2_distances[i] = ultrasonic_2_distance;
    ultrasonic_3_distances[i] = ultrasonic_3_distance;
    ultrasonic_4_distances[i] = ultrasonic_4_distance;
    ultrasonic_5_distances[i] = ultrasonic_5_distance;
    ultrasonic_6_distances[i] = ultrasonic_6_distance;
    ultrasonic_7_distances[i] = ultrasonic_7_distance;
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
  ultrasonic_1_average_distance /= number_of_checks;
  ultrasonic_2_average_distance /= number_of_checks;
  ultrasonic_3_average_distance /= number_of_checks;
  ultrasonic_4_average_distance /= number_of_checks;
  ultrasonic_5_average_distance /= number_of_checks;
  ultrasonic_6_average_distance /= number_of_checks;
  ultrasonic_7_average_distance /= number_of_checks;
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
  // Starting serial monitor for communication
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Check started" );
  update_containers_status();
  Serial.print("Status: ");
  Serial.println(container_1_status);
  Serial.println("Check finished" );
  delay(200);
}
