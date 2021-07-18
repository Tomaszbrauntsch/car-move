//Voltage of hd camera is between 5 - 12 volts
//Probably my camera is 5 volts
#include <Servo.h>
#include <SoftwareSerial.h> //Used for Bluetooth Chip

const int m1P1 = 3;
const int m1P2 = 4;
const int m2P1 = 5;
const int m2P2 = 6;
const int RxD = 9;
const int TxD = 8;
SoftwareSerial BT(RxD,TxD); //RX, TX
int x_state;  //State of X position on app
int y_state;  //State of Y position on app
int shoot_state; //State of button on app
int x_state_bt_read; //Contains latest reading of x position on app
int y_state_bt_read; //Contains latest reading of y position on app
int shoot_bt_read; //Contains latest reading of shoot on app
Servo gunServo;  //Initializes servo of gun

void setup() {
  BT.begin(9600); //bluetooth serial communication
  Serial.begin(9600);
  pinMode(m1P1, OUTPUT);
  pinMode(m1P2, OUTPUT);
  pinMode(m2P1, OUTPUT);
  pinMode(m2P2, OUTPUT);
}

void loop() {
  // Make the other pin the opposite value to go reverse
  x_state = X_BT_Coord();
  y_state = Y_BT_Coord();
    
  shoot_state = Shoot_BT_Signal();
    if((x_state > 80 && x_state < 130) && (y_state > 110 && y_state <= 200))  //Perimeters of joystick on app to move forward
        forward();
    else if((x_state > 80 && x_state < 130) && (y_state >= 0 && y_state < 90))  //Perimeters of joystick on app to move backward
        backward();
    else if ((x_state > 125 && x_state <= 200) && (y_state > 80 && y_state < 130))  //Perimeters of joystick on app to turn left
        turnLeft();
    else if ((x_state >= 0 && x_state < 75) && (y_state > 80 && y_state < 130))  //Perimeters of joystick on app to turn right
        turnRight();
    else
        stopMotors();

    if(shoot_state == 255){
        shoot_state = 0;
        shootGun();
      }
    }

int X_BT_Coord(){  //Finds latest X state from app
  while(BT.available()){ //Checks if there is a byte in transit
    x_state_bt_read = BT.read();
    delay(10);
    Serial.println(x_state_bt_read);
    return x_state_bt_read;
  }
}

int Y_BT_Coord(){  //Finds latest Y state from app
    while(BT.available()){ //Checks if there is a byte in transit
      y_state_bt_read = BT.read();
      delay(10);
      Serial.println(y_state_bt_read);
      return y_state_bt_read;
  }
}

int Shoot_BT_Signal(){  //Finds latest shoot state from app
  while(BT.available()){ //Checks if there is a byte in transit
    shoot_bt_read = BT.read();
    delay(10);
    Serial.println(shoot_bt_read);
    return shoot_bt_read;
  }
}

void shootGun(){
  gunServo.attach(10);  //Servo is connected to digital pin 10
  gunServo.write(100);
  delay(1000);
  gunServo.write(0);
  delay(1000);
  gunServo.detach();
  }

void forward(){
  digitalWrite(m1P1, LOW);
  digitalWrite(m1P2, HIGH);
  digitalWrite(m2P1, LOW);
  digitalWrite(m2P2, HIGH);
  }

void backward(){
 
  digitalWrite(m1P1, HIGH);
  digitalWrite(m1P2, LOW);
  digitalWrite(m2P1, HIGH);
  digitalWrite(m2P2, LOW);
  }
void turnLeft(){
  digitalWrite(m1P1, LOW);
  digitalWrite(m1P2, HIGH);
  digitalWrite(m2P1, LOW);
  digitalWrite(m2P2, LOW);
  delay(450); // turn to do exactly a 90 degree turn (modify while doing the MIT app inventor, to just spin until the user stops)
  }
void turnRight(){
  digitalWrite(m1P1, LOW);
  digitalWrite(m1P2, LOW);
  digitalWrite(m2P1, LOW);
  digitalWrite(m2P2, HIGH);
  delay(450); // turn to do exactly a 90 degree turn (modify while doing the MIT app inventor, to just spin until the user stops)
  }

void stopMotors(){
  digitalWrite(m1P1, LOW);
  digitalWrite(m1P2, LOW);
  digitalWrite(m2P1, LOW);
  digitalWrite(m2P2, LOW);
  }
