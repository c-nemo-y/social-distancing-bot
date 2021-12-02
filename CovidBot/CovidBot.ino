//L293D
//Motor A
const int motorPin1  = 6;  // Pin 14 of L293
const int motorPin2  = 5;  // Pin 10 of L293
//Motor B
const int motorPin3  = 9; // Pin  7 of L293
const int motorPin4  = 10;  // Pin  2 of L293

//Left Ultrasonic Sensor
#define LeftEchoPin 52 
#define LeftTrigPin 53 

//Right Ultrasonic Sensor
#define RightEchoPin 11 
#define RightTrigPin 12 

//Front Ultrasonic Sensor
#define FrontEchoPin 3
#define FrontTrigPin 4

long left_duration; // variable for the left duration of sound wave travel
int left_old_distance; // variable for the left distance measurement

long right_duration; // variable for the right duration of sound wave travel
int right_old_distance; // variable for the right distance measurement

long front_duration; // variable for the front duration of sound wave travel
int front_old_distance; // variable for the front distance measurement
void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(LeftTrigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(LeftEchoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(RightTrigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(RightEchoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(FrontTrigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(FrontEchoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //  moveForward();
  int left_distance = leftUltra();
  int right_distance = rightUltra();
  int front_distance = frontUltra();
  
  if (front_distance >= 25 && left_distance >= 25 && right_distance >= 25) {
    moveForward();
  }
  if (left_distance < 25 && right_distance < 25 && front_distance < 25) {
    moveBack();
  }
  if (left_distance < 25 && right_distance < 25) {
    moveBack();
  }
  if (left_distance < 25) {
    Serial.println("here1");
    Serial.println(left_distance);
    moveRight();
  }
  if (right_distance < 25) {
    Serial.println("here2");
    Serial.println(right_distance);
    moveLeft();
  }
}

void moveRight() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void moveLeft() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);

}

void moveForward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}


void moveBack() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
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
  Serial.println(left_old_distance);
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
  //  Serial.println(right_)
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
  front_old_distance = right_duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //  Serial.println(right_)
  return front_old_distance;
}
