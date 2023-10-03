// Define the stepper motor pins
// x-axis stepper motor
#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12
// y-axis stepper motor
#define IN5 2
#define IN6 3
#define IN7 4
#define IN8 5

// Define the current step and direction of the motor
int curStepX = 1;
int curStepY = 1;
float curXpos = 0;
float curYpos = 0;
boolean dirX = true;
boolean dirY = true;
int speedX = 4000; //lower, faster
int dist2stepX = 500; // how many runs within a step
int speedY = 4000; //lower, faster
int dist2stepY = 500; // how long it can run within a step
float request; //serial port request
float x_position;
float y_position;
float maxInd;
float maxVal;
float sensor0;
float sensor1;
float sensor2;
float sensor3;
float sensor4;
float sensor5;
const int analogPin0 = A0;  // Analog input pin
const int analogPin1 = A1;  // Analog input pin
const int analogPin2 = A2;  // Analog input pin
const int analogPin3 = A3;  // Analog input pin
const int analogPin4 = A4;  // Analog input pin
const int analogPin5 = A5;  // Analog input pin
void stepperX_pos(float x_pos); 
void stepperY_pos(float y_pos); 
float takeMeasurement();
void setup() 
{
  Serial.begin(9600);
  // Set the motor pins as output
  //x-axis motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //y-axis motor
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
}

void loop() 
{
  
  if (Serial.available() )
  {
    String command = Serial.readStringUntil('\n');
    command.trim();
    Serial.println(request);
    //request to move to x, y position
    if (command.startsWith("MOVE"))
    {
      int space1 = command.indexOf(' ');
      int space2 = command.lastIndexOf(' ');
      if (space1 !=-1 && space2 != -1 && space1 != space2)
      {
        float x = command.substring(space1+1,space2).toFloat();
        float y = command.substring(space2+1).toFloat();
        curStepX = 1;
        stepperX_pos(x);
        curStepY = 1;
        stepperY_pos(y);
        Serial.println("READY");
        float measurement = takeMeasurement();
        Serial.println(measurement,2);
      }
    
    //request sensor data (digital max)

    }
  }
}

float takeMeasurement()
{
      sensor0 = float(analogRead(analogPin0));
      maxInd = 0.0;
      maxVal = sensor0;
      float thresh = 0.0;
      sensor1= float(analogRead(analogPin1));
      if (sensor1 > maxVal)// && sensor1 > thresh)
      {
        maxVal = sensor1;
        maxInd = 1.0;
      }
      sensor2 = float(analogRead(analogPin2));
      if (sensor2 > maxVal)// && sensor2 > thresh)
      {
        maxVal = sensor2;
        maxInd = 2.0;
      }
      sensor3 = float(analogRead(analogPin3));
      if (sensor3 > maxVal )//&& sensor3 > thresh)
      {
        maxVal = sensor3;
        maxInd = 3.0;
      }
      sensor4 = float(analogRead(analogPin4));
      if (sensor4 > maxVal )//&& sensor4 > thresh)
      {
        maxVal = sensor4;
        maxInd = 4.0;
      }
      sensor5 = float(analogRead(analogPin5));
      if (sensor5 > maxVal )//&& sensor5 > thresh)
      {
        maxVal = sensor5;
        maxInd = 5.0;
      }
      return maxInd;
}
void stepperX_pos(float x_pos) 
{
  float disX;
  if (x_pos > curXpos)
  {
    disX = x_pos - curXpos;    
    dirX = true;
    stepperX_move(round(disX*dist2stepX));
    curXpos = curXpos + disX;
  } 
  else if (x_pos < curXpos)
  {
    disX = curXpos - x_pos;
    dirX = false;
    dirX = false;
    stepperX_move(round(disX*dist2stepX));
    curXpos = curXpos - disX;
  }
}
void stepperX_move(int xw) 
{
     for (int x = 0; x < xw; x++) {
      delayMicroseconds(speedX);
        switch (curStepX) {
             case 0:
                  digitalWrite(IN1, LOW);
                  digitalWrite(IN2, LOW);
                  digitalWrite(IN3, LOW);
                  digitalWrite(IN4, HIGH);
                  break;
             case 1:
                  digitalWrite(IN1, LOW);
                  digitalWrite(IN2, LOW);
                  digitalWrite(IN3, HIGH);
                  digitalWrite(IN4, HIGH);
                  break;
             case 2:
                  digitalWrite(IN1, LOW);
                  digitalWrite(IN2, LOW);
                  digitalWrite(IN3, HIGH);
                  digitalWrite(IN4, LOW);
                  break;
             case 3:
                  digitalWrite(IN1, LOW);
                  digitalWrite(IN2, HIGH);
                  digitalWrite(IN3, HIGH);
                  digitalWrite(IN4, LOW);
                  break;
             case 4:
                  digitalWrite(IN1, LOW);
                  digitalWrite(IN2, HIGH);
                  digitalWrite(IN3, LOW);
                  digitalWrite(IN4, LOW);
                  break;
             case 5:
                  digitalWrite(IN1, HIGH);
                  digitalWrite(IN2, HIGH);
                  digitalWrite(IN3, LOW);
                  digitalWrite(IN4, LOW);
                  break;
             case 6:
                  digitalWrite(IN1, HIGH);
                  digitalWrite(IN2, LOW);
                  digitalWrite(IN3, LOW);
                  digitalWrite(IN4, LOW);
                  break;
             case 7:
                  digitalWrite(IN1, HIGH);
                  digitalWrite(IN2, LOW);
                  digitalWrite(IN3, LOW);
                  digitalWrite(IN4, HIGH);
                  break;
             default:
                  digitalWrite(IN1, LOW);
                  digitalWrite(IN2, LOW);
                  digitalWrite(IN3, LOW);
                  digitalWrite(IN4, LOW);
                  break;
                  }
       SetDirectionX();
      }
}
void SetDirectionX() 
{
    if (dirX) {
        curStepX++;
    }
    else {
        curStepX--;
    }
    if (curStepX > 7) {
        curStepX = 0;
    }
    if (curStepX < 0) {
        curStepX = 7;
    }
}
void stepperY_pos(float y_pos) 
{
  float disY;
    if (y_pos > curYpos)
  {
    disY = y_pos - curYpos;    
    dirY = true;
    stepperY_move(round(disY*dist2stepY));
    curYpos = curYpos + disY;
  } 
  else if (y_pos < curYpos)
  {
    disY = curYpos - y_pos;
    dirY = false;
    stepperY_move(round(disY*dist2stepY));
    curYpos = curYpos - disY;
  }

}
void stepperY_move(int xw) 
{
     for (int x = 0; x < xw; x++) 
     {
      delayMicroseconds(speedY);
        switch (curStepY) 
        {
             case 0:
                  digitalWrite(IN5, LOW);
                  digitalWrite(IN6, LOW);
                  digitalWrite(IN7, LOW);
                  digitalWrite(IN8, HIGH);
                  break;
             case 1:
                  digitalWrite(IN5, LOW);
                  digitalWrite(IN6, LOW);
                  digitalWrite(IN7, HIGH);
                  digitalWrite(IN8, HIGH);
                  break;
             case 2:
                  digitalWrite(IN5, LOW);
                  digitalWrite(IN6, LOW);
                  digitalWrite(IN7, HIGH);
                  digitalWrite(IN8, LOW);
                  break;
             case 3:
                  digitalWrite(IN5, LOW);
                  digitalWrite(IN6, HIGH);
                  digitalWrite(IN7, HIGH);
                  digitalWrite(IN8, LOW);
                  break;
             case 4:
                  digitalWrite(IN5, LOW);
                  digitalWrite(IN6, HIGH);
                  digitalWrite(IN7, LOW);
                  digitalWrite(IN8, LOW);
                  break;
             case 5:
                  digitalWrite(IN5, HIGH);
                  digitalWrite(IN6, HIGH);
                  digitalWrite(IN7, LOW);
                  digitalWrite(IN8, LOW);
                  break;
             case 6:
                  digitalWrite(IN5, HIGH);
                  digitalWrite(IN6, LOW);
                  digitalWrite(IN7, LOW);
                  digitalWrite(IN8, LOW);
                  break;
             case 7:
                  digitalWrite(IN5, HIGH);
                  digitalWrite(IN6, LOW);
                  digitalWrite(IN7, LOW);
                  digitalWrite(IN8, HIGH);
                  break;
             default:
                  digitalWrite(IN5, LOW);
                  digitalWrite(IN6, LOW);
                  digitalWrite(IN7, LOW);
                  digitalWrite(IN8, LOW);
                  break;
                  }
       SetDirectionY();
      }
}
void SetDirectionY()
{
    if (dirY) {
        curStepY++;
    }
    else {
        curStepY--;
    }
    if (curStepY > 7) {
        curStepY = 0;
    }
    if (curStepY < 0) {
        curStepY = 7;
    }
} 
void maxIndex(float myArray[])
{
  float index = 0;
  float maxVal = 1000;
  for (int i = 0; i < (sizeof(myArray) / sizeof(myArray[0])); i++) 
  {
     if (maxVal < myArray[i])
     {
        maxVal = myArray[i];
        index = i;
     }
  }    
  maxInd =  index;
}
