//L293D
//Motor A
const int left1  = 40;  // Pin 14 of L293
const int left2  = 41;  // Pin 10 of L293
#define leftEnable A14

//Motor B
const int right1  = 31; // Pin  7 of L293
const int right2  = 30;  // Pin  2 of L293
#define rightEnable A15

//Left Ultrasonic Sensor
#define LeftEchoPin 52 
#define LeftTrigPin 53 

//Right Ultrasonic Sensor
#define RightEchoPin 12
#define RightTrigPin 13 

//Front Ultrasonic Sensor
#define FrontEchoPin 10
#define FrontTrigPin 11

int max_speed = 255;
int reduced = 220;

long left_duration; // variable for the left duration of sound wave travel
int left_old_distance; // variable for the left distance measurement

long right_duration; // variable for the right duration of sound wave travel
int right_old_distance; // variable for the right distance measurement

long front_duration; // variable for the front duration of sound wave travel
int front_old_distance; // variable for the front distance measurement
void setup() {
  // put your setup code here, to run once:
  pinMode(leftEnable, OUTPUT);
  pinMode(rightEnable, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(LeftTrigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(LeftEchoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(RightTrigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(RightEchoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(FrontTrigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(FrontEchoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);

}

const int speedFactor = 0.8;

void loop() {
  // put your main code here, to run repeatedly:
  //  moveForward();
  Serial.println("top");
  int left_distance = leftUltra();
  int right_distance = rightUltra();
  int front_distance = frontUltra();
  Serial.println(front_distance);
  Serial.println(right_distance);
  Serial.println(left_distance);

  int safe_dist = 40;
  
  if (front_distance >= safe_dist && left_distance >= safe_dist && right_distance >= safe_dist) {
    moveForward();
  }
//  if (left_distance < safe_dist && right_distance < safe_dist && front_distance < safe_dist) {
//    moveBack();
//  }
//  if (left_distance < safe_dist && right_distance < safe_dist) {
//    moveBack();
//  }
  if (front_distance < safe_dist) {
      digitalWrite(left1, HIGH);
      digitalWrite(left2, HIGH);
      digitalWrite(right1, HIGH);
      digitalWrite(right2, HIGH);
      delay(700);
    moveBack();
    delay(2000*speedFactor);
    if(left_distance > right_distance){
      moveLeft();
      } else {
      moveRight(); 
      }
    delay(500*speedFactor);
    while (frontUltra() < safe_dist + 20) {
      
      delay(100*speedFactor);
    }
  }
  if (left_distance < 25) {
//    Serial.println("here1");
//    Serial.println(left_distance);
    moveRight();
  }
  if (right_distance < 25) {
//    Serial.println("here2");
//    Serial.println(right_distance);
    moveLeft();
  }
  Serial.println("4");
}

void moveRight() {
  analogWrite(leftEnable, max_speed);
  analogWrite(rightEnable, reduced);
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
}

void moveLeft() {
  analogWrite(leftEnable, max_speed);
  analogWrite(rightEnable, reduced);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);

}

void moveForward() {
  analogWrite(leftEnable, max_speed);
  analogWrite(rightEnable, reduced);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
}


void moveBack() {

  analogWrite(leftEnable, max_speed);
  analogWrite(rightEnable, reduced);
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
}

int leftUltra() {
  digitalWrite(LeftTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the LeftTrigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(LeftTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(LeftTrigPin, LOW);
  // Reads the LeftEchoPin, returns the sound wave travel time in microseconds
  left_duration = pulseIn(LeftEchoPin, HIGH);
  // Calculating the distance
  left_old_distance = left_duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  return left_old_distance;
}

int rightUltra() {

  digitalWrite(RightTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the RightTrigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(RightTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(RightTrigPin, LOW);
  // Reads the RightEchoPin, returns the sound wave travel time in microseconds
  right_duration = pulseIn(RightEchoPin, HIGH);
  // Calculating the distance
  right_old_distance = right_duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  return right_old_distance;
}

int frontUltra() {

  digitalWrite(FrontTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the RightTrigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(FrontTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(FrontTrigPin, LOW);
  // Reads the RightEchoPin, returns the sound wave travel time in microseconds
  front_duration = pulseIn(FrontEchoPin, HIGH);
  // Calculating the distance
  front_old_distance = front_duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
 
  return front_old_distance;
}
