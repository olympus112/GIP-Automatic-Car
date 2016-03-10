#include <iostream>
#include <robot.h>

//GIP Stuff
	
	// Chapter 1: Exploring teh maze
	
		//we do that by drivin around, keepin to teh wall on our right side
		//after crossing teh entire maze, the car should be back at teh beginning
		
	
	// Chapter 2: Finding... Nemo? Nah, just bout anythin in that maze thing
	
const int STARTX = 1;
const int STARTY = 1;
const int STARTDIRECTION = 0; // 0:UP, 1:RIGHT, 2:DOWN, 3:LEFT;
const int FIELDSIZE = 20;

int x = STARTX;
int y = STARTY;
int d = STARTDIRECTION;

char* WallArray = new char[(FIELDSIZE+1)*(FIELDSIZE+1)/4];	// create "2D" array. 2 bits used per plot, only register top and left wall
															// 



//Robot code that matthoias made
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


int main(int argc, char *argv[]) {
	
	// EXPORE
	
	do{
		if(pingRight()){
			
		}else{
			
		}
		
		
		
	}while(x != STARTX || y != STARTY);
	
	
	
	
	
	
	
	
	return 0;
}
