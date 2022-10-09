/*
	Program 1: Wumpus, version 1 (fixed size array)

	// You will want to add more to this header comment!
  // author name : Gaurav Vaghmar

*/
#include <stdio.h>
#include <stdlib.h>		// for srand
#include <string.h>
#include <stdbool.h>
#include <time.h>

const int adjValues [20][3] = {
  {2,5,8},{1,3,10},{2,4,12},{3,5,14},{1,4,6},{5,7,15},{6,8,17},{1,7,9},{8,10,18},{2,9,11},{10,12,19},{3,11,13},{12,14,20},
  {4,13,15}, {6,14,16}, {15,17,20}, {7,16,18}, {9,17,19}, {11,18,20},{13,16,20}
};

//--------------------------------------------------------------------------------
void displayCave()
{
    printf( "       ______18______             \n"
    		"      /      |       \\           \n"
    		"     /      _9__      \\          \n"
    		"    /      /    \\      \\        \n"
    		"   /      /      \\      \\       \n"
    		"  17     8        10     19       \n"
    		"  | \\   / \\      /  \\   / |    \n"
    		"  |  \\ /   \\    /    \\ /  |    \n"
    		"  |   7     1---2     11  |       \n"
    		"  |   |    /     \\    |   |      \n"
    		"  |   6----5     3---12   |       \n"
    		"  |   |     \\   /     |   |      \n"
    		"  |   \\       4      /    |      \n"
    		"  |    \\      |     /     |      \n"
    		"  \\     15---14---13     /       \n"
    		"   \\   /            \\   /       \n"
    		"    \\ /              \\ /        \n"
    		"    16---------------20           \n"
    		"\n");
}

//--------------------------------------------------------------------------------
void displayInstructions()
{
    printf( "Hunt the Wumpus:                                             \n"
    		"The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
    		"room has 3 tunnels leading to other rooms.                   \n"
    		"                                                             \n"
    		"Hazards:                                                     \n"
    		"1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
    		"2. The Wumpus is not bothered by the pits, as he has sucker feet. Usually he is \n"
			"   asleep. He will wake up if you enter his room. When you move into the Wumpus'\n"
			"   room, then he wakes and moves if he is in an odd-numbered room, but stays    \n"
			"   still otherwise.  After that, if he is in your room, he snaps your neck and  \n"
			"   you die!                                                                     \n"
    		"                                                                                \n"
    		"Moves:                                                                          \n"
    		"On each move you can do the following, where input can be upper or lower-case:  \n"
    		"1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
    		"   then a room number.                                                          \n"
    		"2. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
    		"3. Enter 'C' to cheat and display current board positions.                      \n"
    		"4. Enter 'D' to display this set of instructions.                               \n"
    		"5. Enter 'P' to print the maze room layout.                                     \n"
            "6. Enter 'G' to guess which room Wumpus is in, to win or lose the game!         \n"
    		"7. Enter 'X' to exit the game.                                                  \n"
    		"                                                                                \n"
    		"Good luck!                                                                      \n"
    		" \n\n");
}//end displayInstructions()

// checkMove checks the move whether the entered value is adjecent to any other valus on the map by taking in two parameters. It returns bool value and
//uses for loop to loop throuhg specific nested array using person parameter and matches the value to move number and if it does then it returns true
bool checkMove (int *moveNumber, int *person){
  bool moveValid = false;
  for (int i = 0; i < 3; i++){ 
    // printf("%d %d %d\n",adjValues[*person - 1][i], *person, *moveNumber);
    //adjValues is a global array to find the adjecent value in regard to moveNumber
    if(*moveNumber == adjValues[*person - 1][i]){
      moveValid = true;
    }
  }
  return moveValid; // returns true or false
}
//check Objects function has four parameters to check where the pit1, pit2, and Wumpus are and if any of them is adjecent to the room person is in then it returns various messages. 
void checkObjects(int *personRoom, int *pit1, int *pit2, int * Wumpus){
  printf("You are in room %d. ", *personRoom);
  // for loop to loop through nested array and determine which nested array using personRoom variable in which the person is in.
  for (int i = 0; i< 3; i++){
    if(*Wumpus == adjValues[*personRoom-1][i] ){
      printf("You smell a stench. "); // for an adjecent room in which wumpus is in.
    } 
  }
  for (int i = 0; i< 3; i++){
    if(*pit1 == adjValues[*personRoom-1][i] ){
      printf("You feel a draft. "); // for an adjecent room which pit is.
    } 
    if(*pit2 == adjValues[*personRoom-1][i] ){
      printf("You feel a draft. "); // for an adjecent room which pit is.
    } 
  }
  printf("\n\n");
}

// checkPit function takes in three parameters which are the rooms where the pits are and the current position of person(user) then it determines whether
//the person has fallen into pit or not by matching the room of person and pit room. Lastly, it returns bool value
bool checkPit(int *personRoom, int *pit1, int *pit2){
  
  bool pit = false;
  // using if else statement to output messages for two different pits
  if (*personRoom == *pit1){ // matching the current position of person and comparing it to pit room location
    printf("Aaaaaaaaahhhhhh....   \n");
  	printf("    You fall into a pit and die. \n");
    pit = true;// setting variable's value to true if matched
  }
  if (*personRoom == *pit2){// matching the current position of person and comparing it to pit room location
    printf("Aaaaaaaaahhhhhh....   \n");
  	printf("    You fall into a pit and die. \n");
    pit = true; // setting variable's value to true if matched 
  }
  return pit; // returns true or false
}
//evenWumpus function checks whether the person entered room has wumpus or it slips away and it uses % to determine if the person entered room is even or odd and it prints out the message according to that.
bool evenWumpus(int *personRoom, int *wumpus){
  //
  bool evenW = false;
  if (*personRoom % 2 == 0 && *personRoom == *wumpus){
    printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n"
			"It is over.\n");
    evenW = true;
  }
  if (*personRoom % 2 == 1 && *personRoom == *wumpus){
    *wumpus = rand()  % 20 + 1; 
    printf( "You hear a slithering sound, as the Wumpus slips away. \n"
			"Whew, that was close! \n");
    evenW = false;
  }
  return evenW; // returns true or false
}

// guessWumpus function gives user an opportunity to guess in which room wumpus is in and if it guesses correctly then won otherwise lose
void guessWumpus(int *userGuess, int *wumpus){
  //using if statement checking if the entered room number contains wumlus or not
  if(*userGuess == *wumpus){
    printf("You won!\n");
    printf("\nExiting Program ...\n");
    exit(0); // exits the program
  }
  else{
    printf("You lost.\n");
    printf("\nExiting Program ...\n");
    exit(0); // exits the program
  }
}

//--------------------------------------------------------------------------------
int main(void) {

	// Seed the random number generator.  Change seed to time(0) to change output each time.
  srand(1);
  
  char userMove; 
  int userMoveNumber;
  // using srand(1) assiging random values that stays the same each time program runs for nonrandom game 
  int pit1 = rand() % 20 + 1;
  int pit2 = rand() % 20 + 1;
  int Wumpus =rand() % 20 + 1;
  int person = rand() % 20 + 1;
  // printf("%d %d %d", pit1, pit2, Wumpus);
  int moveNumber = 1;
  printf("You are in room %d.\n\n",person);
  printf("1. Enter your move (or 'D' for directions): ");

  // while loop iterates until the user hasn't entered x to exit the game
  while (userMove != 'x'){
    scanf("%c",&userMove);    
    //if entered character is x then program exits
    if(userMove =='x' || userMove =='X'){
      printf("\nExiting Program ...\n");
      break; // exits the program
    }
    // if character entered is d or D then it displays the cave and instructions and continues while loop
    if (userMove == 'd' || userMove == 'D'){
      printf("\n");
      displayCave(); // calling displayCave functuion to display cave
      displayInstructions(); // calling displayInstructions functuion to display Instructions
      printf("You are in room %d.\n\n",person);
      printf("%d. Enter your move (or 'D' for directions): ",moveNumber);
      continue; // continues the loop
    }
    // if entered char is c or C then it shows the locations of game components
    if(userMove == 'c' || userMove == 'C'){
      printf( "Cheating! Game elements are in the following rooms: \n"
    		"Player Wumpus Pit1 Pit2  \n"
    		"%4d %7d %5d %5d \n\n", person, Wumpus, pit1, pit2);
      printf("You are in room %d.\n\n",person);
      printf("%d. Enter your move (or 'D' for directions): ",moveNumber);
      continue; // continues the loop
    }
    // if the userMove char is m then it prompts user to input a move number where they want the person to be in that particular room if it's adjecant
    if(userMove == 'm' || userMove== 'M'){
      scanf("%d",&userMoveNumber);
      // printf("%d\n",person);
      bool checkM = checkMove(&userMoveNumber, &person); // returns bool value if move is valid or not
      // if the user move number is out of range then it asks user to input the value again using conditions 
      if(userMoveNumber < 0 || userMoveNumber > 20 || checkM == false){
        printf("Invalid move.  Please retry. \n");
        printf("You are in room %d.\n\n",person); 
        printf("%d. Enter your move (or 'D' for directions): ",moveNumber);
        continue; // continues the loop
      } 
      moveNumber++; //incrementing game moves each time the move is valid
      bool evenW = evenWumpus(&userMoveNumber,&Wumpus); // calls function evenWampus and returns true or false
      if(evenW == true){ // if true then exits the program 
        printf("\nExiting Program ...\n");
        exit(0); // exits the program
      }
      bool pitFall = checkPit(&userMoveNumber, &pit1,&pit2); // calls pitFall function
      if(pitFall == true){
        printf("\nExiting Program ...\n");
        exit(0); // exits the program
      }
      checkObjects(&userMoveNumber, &pit1, &pit2, &Wumpus); //calls checkobjetcs function to give warnings and hazards
      person = userMoveNumber;
      printf("%d. Enter your move (or 'D' for directions): ",moveNumber);
      
    }
    // if user char is R then it resets the value of game componets by prompting user to input values they want for them to be assigned
    if(userMove == 'R' || userMove == 'r'){
      printf("Enter the room locations (1..20) for player, wumpus, pit1, and pit2: \n");
      scanf("%d %d %d %d", &person, &Wumpus, &pit1, &pit2);
      printf("\n");
      checkObjects(&person, &pit1, &pit2, &Wumpus); // calls function checkObjects
      printf("%d. Enter your move (or 'D' for directions): ",moveNumber);
      continue;
    }
    // guess the move
    if(userMove == 'G' || userMove == 'g'){
      int userGuess;
      printf("Enter room (1..20) you think Wumpus is in: ");
      scanf("%d", &userGuess);
      guessWumpus(&userGuess, &Wumpus);
      continue;
    }
    // displaying cave
    if(userMove == 'p' || userMove == 'P'){
      printf("\n");
      displayCave();
      printf("You are in room %d.\n\n",person); 
      printf("%d. Enter your move (or 'D' for directions): ",moveNumber);
    }
   
  }  
	return 0;
}
