const int SETUP_TIME = 7000; //7000
const int AUTONOMOUS_TIME = 15000;  //15000
const int STOP_TIME = 2000;  //2000

int left_motor_forward;
int left_motor_backward;
int right_motor_forward;
int right_motor_backward;

int leftLED; //BLUE
int rightLED; //YELLOW

int leftB; //BLUE
int rightB; //YELLOW

int flexL;
int flexR;

int photos[] = {A0, A1, A2, A3};

//modes
bool LEFT;
bool RIGHT;

void setup()
{
  Serial.begin(9600);
 
  left_motor_forward = 10;
  left_motor_backward = 11;
  right_motor_forward = 5;
  right_motor_backward = 6;

  leftLED = 12; //BLUE
  rightLED = 13; //YELLOW

  leftB = 2; //BLUE
  rightB = 8; //YELLOW

  flexL = A4;
  flexR = A5;

  LEFT = false;
  RIGHT = false;
 
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);

  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
 
  pinMode(leftB, INPUT);
  pinMode(rightB, INPUT);

  for(int i=0; i<4; i++){
  pinMode(photos[i], INPUT);
  }
}

void loop()
{
  //DO NOT TOUCH THIS CODE
  long mil = millis();
/*
  int flexL1 = analogRead(flexL);
  int flexR2 = analogRead(flexR);
  Serial.print("flexL = ");
  Serial.print(flexL1);
  Serial.print("     ");
  Serial.print("flexR = ");
  Serial.print(flexR2);
  Serial.println("     ");
  */
  
  
  if(mil<SETUP_TIME)
  {
    //LEAVE THIS BLANK
    //setMode();
    //SET MODE HERE
    LEFT = true;
    //RIGHT = true;
  }
  else if(mil<AUTONOMOUS_TIME+SETUP_TIME)
  {
    autonomousMode();
  }
  else if(mil<AUTONOMOUS_TIME+SETUP_TIME+STOP_TIME)
  {
    fullStop();
  }
  else
  {
    teleOpMode();
  }
 
}

//WRITE CODE IN HERE:  YOUR AUTONOMOUS CODE GOES IN HERE.  PART 1 OF RACE
void autonomousMode()
{
  autoMode();
}
//WRITE CODE IN HERE:  YOUR TELEOP CODE GOES IN HERE.  PART 2 OF RACE
//you MUST write this method
void teleOpMode()
{
  photoMove();
}
//WRITE CODE IN HERE:  YOU SHOULD MAKE EVERY MOTOR STOP
//you MUST write this method
void fullStop()
{
  leftForward(0);
  rightForward(0);
}

void fullSpeedForward()
{
  leftForward(110);
  rightForward(255);
}

void turnLeft()
{
  leftBackward(100);
  rightForward(255);
}

void turnRight()
{
  leftForward(100);
  rightBackward(255);
}

//times
int cooldown = 50;
//adjust the values behind the plus sign for each part of the track
int line1 = SETUP_TIME + 700; //a1a2
int turn1 = line1 + 70; //a2 to a3 //70 with full battery
int line2 = turn1 + 400; //a3
int turn2 = line2 + 70; //a3 to a4
int line3 = turn2 + 700; //a4a5
int turn3 = line3 + 100; //a5 to a6 //test this
int line4 = turn3 + 700; //a6a7
int turn4 = line4 + 85; //a7 to a8 //test this

//adjust the speeds to make the motors turn properly
void autoMode()
{
  long mil = millis();
  if(mil < line1)
  {
    //full speed forward
    leftForward(205); //if 110 it moves in a straighter line
    rightForward(255);
  }
  else if(mil < turn1)
  {/*
    if(mil < line1 + cooldown)
    {
      //stop
      fullStop();
    }
    else
    {*/
      if(LEFT)
      {
        //turn left
        leftBackward(100);
        rightForward(255);
      }
      else if(RIGHT)
      {
        //turn right
        leftForward(150);
        rightBackward(255);
      }
    //}
  }
  else if(mil < line2)
  {
    //full speed forward
    leftForward(205);
    rightForward(255);
  }
  
  else if(mil < turn2)
  {
    if(LEFT)
    {
      //turn right
      leftForward(150);
      rightBackward(200);
    }
    else if(RIGHT)
    {
      //turn left
      leftBackward(150);
      rightForward(200);
    }
  }
  else if(mil < line3)
  {
    //full speed forward
    leftForward(205);
    rightForward(255);
  }
  else if(mil < turn3)
  {
    if(LEFT)
    {
      //turn right
      leftForward(150);
      rightBackward(200);
    }
    else if(RIGHT)
    {
      //turn left
      leftBackward(150);
      rightForward(200);
    }
  }
  else if(mil < line4)
  {
    //full speed forward
    leftForward(205);
    rightForward(255);
  }
  else if(mil < turn4)
  {
    if(LEFT)
    {
      //turn right
      leftForward(150);
      rightBackward(200);
    }
    else if(RIGHT)
    {
      //turn left
      leftBackward(150);
      rightForward(200);
    }
  }
  else
  {
    //fullStop();
    
    //half speed forward
    leftForward(205);
    rightForward(255);
  }
}

void setMode()
{
  int bLeftState = digitalRead(leftB);
  int bRightState = digitalRead(rightB);

  if(bLeftState == 1)
  {
    LEFT = true;
  }
  else if(bRightState == 1)
  {
    RIGHT = true;
  }
  
  if(LEFT == true)
  {
    digitalWrite(leftLED, HIGH);
    Serial.println("LEFT mode");
  }
  else if(RIGHT == true)
  {
    digitalWrite(rightLED, HIGH);
    Serial.println("RIGHT mode");
  }
}

void leftForward(int power)
{
  analogWrite(left_motor_forward, power);
  analogWrite(left_motor_backward, 0);
}

void leftBackward(int power)
{
  analogWrite(left_motor_forward, 0);
  analogWrite(left_motor_backward, power);
}

void rightForward(int power)
{
  analogWrite(right_motor_forward, power);
  analogWrite(right_motor_backward, 0);
}

void rightBackward(int power)
{
  analogWrite(right_motor_forward, 0);
  analogWrite(right_motor_backward, power);
}

void photoMove(){
  int photo0 = analogRead(photos[0]);  //
  int photo1 = analogRead(photos[1]);  //200-1000
  int photo2 = analogRead(photos[2]);  //13-866
  int photo3 = analogRead(photos[3]);  //
  //long mil = millis();
  //long future = mil + 250;


  if(photo0 > 800){
  //go backwards
  leftBackward(205);
  rightBackward(255);
  }
  else if(photo1 > 850){
  //turn right
  leftForward(150);
  rightBackward(200);
  }
  else if(photo3 > 700){
  //go forward
    leftForward(170);
    rightForward(255);
  }
  else if(photo2 > 650){
  //turn left
  leftBackward(150);
  rightForward(200);
  }
 
  else{
  leftForward(0); //100
  rightForward(0);  //150
  }
}

void testPhotos()
{
  int photoState1 = analogRead(photos[0]);
  int photoState2 = analogRead(photos[1]);
  int photoState3 = analogRead(photos[2]);
  int photoState4 = analogRead(photos[3]);

  Serial.print("1 = ");
  Serial.print(photoState1);
  Serial.print("      ");
  Serial.print("2:");
  Serial.print(photoState2);
  Serial.print("      ");
  Serial.print("3:");
  Serial.print(photoState3);
  Serial.print("      ");
  Serial.print("4:"); // 2
  Serial.print(photoState4);
  Serial.println("      ");
}

void buttonTest()
{
  int b1state = digitalRead(leftB);
  int b2state = digitalRead(rightB);

  Serial.print("b1: ");
  Serial.println(b1state);
  Serial.print("b2: ");
  Serial.println(b2state);
}
