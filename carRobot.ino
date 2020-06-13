/*
Arduino Yun
PROJEKT: Car Robot
WYKONANIE: Schier Jonasz, Szmajduch Dawid
*/
 
#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>
#include <Console.h>
 
#include <SharpIR.h>
 
#define IR1 A5 //lewy przod
#define IR2 A4 //prawy przod
#define IR3 A3 // lewy tyl
#define IR4 A2 //prawy tyl
 
#define model1 430 //od 4cm do 30cm
#define model2 430
#define model3 430
#define model4 430
 
SharpIR lewyPrzod = SharpIR(IR1, model1);
SharpIR prawyPrzod = SharpIR(IR2, model2);
SharpIR lewyTyl= SharpIR(IR3, model3);
SharpIR prawyTyl = SharpIR(IR4, model4);
 
// Listen to the default port 5555, the Yún webserver
// will forward there all the HTTP requests you send
BridgeServer server;
 
//łączenie silników do Arduino
//pierwszy silnik
int enA = 10;
int in1 = 9;
int in2= 8;
 
//drugi silnik
int enB = 5;
int in3 = 7;
int in4 = 6;
 
int disLP;
int disPP;
int disLT;
int disPT;
 
String actualMove = "";
 
void setup() {
  // Bridge startup
  Bridge.begin();
 
  // ustawienie wszystkich pinów silnika na wyjście
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
  Console.begin();
 
  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
}
 
//Funkcje
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 60);
 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 60);
}
 
void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 60);
 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 60);
}
 
void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 50);
 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 50);
}
 
void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 50);
 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 50);
}
 
void stap() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
}
 
void loop() {
  // Get clients coming from server
  BridgeClient client = server.accept();
 
  
  // There is a new client?
  if (client) {
    //int milis = millis();
    // Process request
    actualMove = process(client);
 
    //int milis2 = millis();
    //Console.println(milis2 - milis);
    // Close connection and free resources.
    client.stop();
  }
 
  //Czytanie odleglosci
  float volt1 = analogRead(IR1) * 0.0048828125;
  float volt2 = analogRead(IR2) * 0.0048828125;
  float volt3 = analogRead(IR3) * 0.0048828125;
  float volt4 = analogRead(IR4) * 0.0048828125;
  disLP = 13*pow(volt1, -1); //lewy przod
  disPP = 13*pow(volt2, -1); //prawy przod
  disLT = 13*pow(volt3, -1); //lewy tyl
  disPT = 13*pow(volt4, -1); //prawy tyl
 
  if (actualMove == "forward") {
    if (disLP < 9 || disPP < 9) {
      stap();
      actualMove = "stop";
    }
  } else if (actualMove == "backward") {
      if (disLT < 9 || disPT < 9) {
        stap();
        actualMove = "stop";
    }
  }
  //Console.println(actualMove);
  //Console.println(disLP);
  //Console.println(disPP);
 
}
 
String process(BridgeClient client) {
  // read the command
  String command = client.readStringUntil('/');
  Console.print(command);
 
  // is "move" command?
  if(command == "move") {
    return moveCommand(client);
  }
  return "";
}
 
 
 
String moveCommand(BridgeClient client) {
  String value;
  
  value = client.readStringUntil("\r");
  value.trim();
 
  Console.print("Move: ");
  Console.println(value);
 
  if (value == "forward" && (disLP > 9 || disPP > 9)) {
    moveForward();
  }
 
  if (value == "backward" && (disLT > 9 || disPT > 9)) {
    moveBackward();
  }
 
  if (value == "left") {
    turnLeft();
  }
 
  if (value == "right") {
    turnRight();
  }
 
  if (value == "stop") {
    stap();
  }
  return value;
}