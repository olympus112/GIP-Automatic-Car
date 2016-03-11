#include <iostream>
#include <robot.h>
#define SENSOR_VOOR 2
#define SENSOR_LINKS 4
#define SENSOR_RECHTS 5
#define MIN_AFSTAND_VOOR 0
#define MAX_AFSTAND_VOOR 15
#define MIN_AFSTAND_ZIJKANT 10
#define MAX_AFSTAND_ZIJKANT 15
#define RICHTING_A 12
#define RICHTING_B 13
#define PBM_A 3
#define PBM_B 11
#define REM_A 9
#define REM_B 8
#define AMPERE_A A0
#define AMPERE_B A1

/*
-GIP Stuff
	* Chapter 1: Exploring thr maze
		we do that by driving around, keeping to the wall on our right side
		after crossing the entire maze, the car should be back at the beginning
		
-Pin configuration
	* 0 - computer
	* 1 - computer
	* 2 - SENSOR_VOOR
	* 3 - PBM_A
	* 4 - SENSOR_LINKS
	* 5 - SENSOR_RECHTS
	* 6 - vrij
	* 7 - vrij
	* 8 - REM_B
	* 9 - REM_A
	* 10 - vrij 
	* 11 - PBM_B
	* 12 - RICHTING_A
	* 13 - RICHTING_B
 */
 
const int STARTX = 1;
const int STARTY = 1;
const int STARTDIRECTION = 0; // 0:UP, 1:RIGHT, 2:DOWN, 3:LEFT;
const int FIELDSIZE = 20;
long afstand_voor;
long afstand_links;
long afstand_rechts;

int x = STARTX;
int y = STARTY;
int d = STARTDIRECTION;

char* WallArray = new char[(FIELDSIZE+1)*(FIELDSIZE+1)/4];	// create "2D" array. 2 bits used per plot, only register top and left wall

void setup() {
  // Initieer seriÃ«le communicatie.
  Serial.begin(9600); 

  //Stel kanaal A in.
  pinMode(RICHTING_A, OUTPUT); 
  pinMode(REM_A, OUTPUT);

  //Stel kanaal B in.
  pinMode(RICHTING_B, OUTPUT); 
  pinMode(REM_B, OUTPUT); 
}

void loop() { 
  //afstand_voor = ping(SENSOR_VOOR);
  //afstand_links = ping(SENSOR_LINKS);
  //afstand_rechts = ping(SENSOR_RECHTS);

  voorwaarts(255);
  delay(2000);
  achterwaarts(255);
  delay(2000);
  //printSensors();
  Serial.print(analogRead(AMPERE_A));
  Serial.print("        ");
  Serial.println(analogRead(AMPERE_B));
}

void aanloop(int beginsnelheid, int eindsnelheid, int tijdsinterval) {
  for(int i = beginsnelheid; i < eindsnelheid; i++) {
    analogWrite(PBM_A, i);
    analogWrite(PBM_B, i);
    delay(tijdsinterval / (eindsnelheid - beginsnelheid));
  }
}

void voorwaarts(int snelheid) {
  // Motor A en B voorwaarts @ volle snelheid.
  digitalWrite(RICHTING_A, HIGH); // Stelt de voorwaartse richting van kanaal A in.
  digitalWrite(RICHTING_B, HIGH); // Stelt de voorwaartse richting van kanaal B in.
  
  digitalWrite(REM_A, LOW); // Schakel de rem voor kanaal A uit.
  digitalWrite(REM_B, LOW); // Schakel de rem voor kanaal B uit.

  analogWrite(PBM_A, snelheid);
  analogWrite(PBM_B, snelheid);
  //aanloop(255, snelheid, 1);

  delay(6000); // afstand

  digitalWrite(REM_A, HIGH); // Schakel de rem voor kanaal A in.
  digitalWrite(REM_B, HIGH); // Schakel de rem voor kanaal B in.
}

void achterwaarts(int snelheid) {
  // Motor A en B achterwaarts @ volle snelheid.
  digitalWrite(RICHTING_A, LOW); // Stelt de achterwaartse richting van kanaal A in.
  digitalWrite(RICHTING_B, LOW); // Stelt de achterwaartse richting van kanaal B in.
  
  digitalWrite(REM_A, LOW);
  digitalWrite(REM_B, LOW); 

  analogWrite(PBM_A, snelheid);
  analogWrite(PBM_B, snelheid);
  //aanloop(255, snelheid, 1);

  delay(6000); // afstand

  digitalWrite(REM_A, HIGH); 
  digitalWrite(REM_B, HIGH); 
}

void draaiLinks() {
  
}

void draaiRechts() {
  
}

void printSensors() {
  Serial.print(afstand_voor);
  Serial.print("cm (voor)");
  Serial.print("           ");

  Serial.print(afstand_links);
  Serial.print("cm (links)");
  Serial.print("           ");

  Serial.print(afstand_rechts);
  Serial.print("cm (rechts)");
  Serial.println();
}

long ping(int sensorPin) {
  long tijdsverschil, afstand;
  
  pinMode(sensorPin, OUTPUT); 
  digitalWrite(sensorPin, LOW); // Geef een korte LOW pulse om zeker te zijn van een schone HIGH pulse.
  delayMicroseconds(2); 
  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(5); // De sensor wordt geactiveerd door een HIGH pulse van 2 of meer microseconden.
  digitalWrite(sensorPin, LOW);
  
  // Dezelfde pin wordt gebruikt om het signaal van de sensor te lezen.
  // Een HIGH pulse waarvan de duur de tijd is in microseconden van het verzenden
  // van de pulse tot de ontvangst van de weerkaatste echo.
  pinMode(sensorPin, INPUT);
  
  tijdsverschil = pulseIn(sensorPin, HIGH);
  afstand = microsecondenNaarCentimeters(tijdsverschil);

  delay(50);

  return afstand;
}

void controleerAfstand(long afstand, int sensor) {
  switch(sensor) {
    case SENSOR_VOOR:
      if(afstand <= MAX_AFSTAND_VOOR) { // De auto nadert een muur en zal zo meteen moeten stoppen.
        Serial.println("Muur gedetecteerd (vooraan)");
        //TODO stop de auto
      }
      break;
    case SENSOR_LINKS:
      if(afstand >= MIN_AFSTAND_ZIJKANT && afstand <= MAX_AFSTAND_ZIJKANT) { 
        //De linkerkant van de auto bevind zich met een juiste afstand van de muur.
      } else {
        if(afstand < MIN_AFSTAND_ZIJKANT) {
          Serial.println("Auto nadert de linkermuur.");
        }
        if(afstand > MAX_AFSTAND_ZIJKANT) {
          Serial.println("Gang gedetecteerd aan de linkerkant");
        }
      }
      break;
    case SENSOR_RECHTS:
      if(afstand >= MIN_AFSTAND_ZIJKANT && afstand <= MAX_AFSTAND_ZIJKANT) { 
        //De rechterkant van de auto bevind zich met een juiste afstand van de muur.
      } else { 
        if(afstand < MIN_AFSTAND_ZIJKANT) {
          Serial.println("Auto nadert de rechtermuur.");
        }
        if(afstand > MAX_AFSTAND_ZIJKANT) {
          Serial.println("Gang gedetecteerd aan de rechterkant");
        }
      }
      break;
  }
}

long microsecondenNaarCentimeters(long microseconden) {
  // De snelheid van het geluid 340 m/s if 29 microseconden per centimeter.
  // De puls resit heen en weer, dus om de afstand tussen de sensor en
  // de muur te vinden delen we het aantal microseconden door 2.
  return microseconden / 29 / 2;
}															// 

// TODO implement in matthias code;
void forward(){
	//Native Forward call
	switch(d){
		case 0:
			y+=1;
			break;
		case 1:
			x+=1;
			break;
		case 2:
			y-=1;
			break;
		case 3:
			x-=1;
			break;
	}
}
void turnRight(){
	d = (d + 1) % 4;
}
void turnLeft(){
	d = (d + 3) % 4;
}
//says if there be wallz in front of it
bool ping(){
	//Fake ping! *I* King of Arabor, shall decide over the existence of teh wall!
	bool input;
	cout << "Is there wall in front of me? ";
	cin >> input;
	return input;
}
bool pingLeft(){
	bool input;
	cout << "Is there wall to the left of me? ";
	cin >> input;
	return input;
}
bool pingRight(){
	bool input;
	cout << "Is there wall to the right of me? ";
	cin >> input;
	return input;
}

// TumFunctions to make interfacing with the wall array a bit easier :P
void setWall(){
	
}

//same as void setup
int main(int argc, char *argv[]) {
	// EXPORE
	do{
		if(pingRight()){
			
		}else{
			
		}
	}while(x != STARTX || y != STARTY);
	
	return 0;
}


 



