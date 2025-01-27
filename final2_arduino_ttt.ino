#include <Adafruit_NeoPixel.h>
#include <Keypad.h>

#define X 'X'
#define O 'O'
#define EMPTY ' '

char board[3][3]; // Represents the Tic Tac Toe board
char currentPlayer = X; // X starts the game
int coord = 0;

// Previous move indices
int prevRow = -1;
int prevCol = -1;

// Keypad setup
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8, 9}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int PIN = 11;
int numLEDS = 9;



Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLEDS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // Initialize the board
  resetBoard();

  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  //Loop from pins 2 - 10
  for (int i=2; i<=10; i++) {
    pinMode(i, INPUT);
  }
  

  strip.begin();
}

void loop() {
  // Check for button press
  
  runCheck();
  if(currentPlayer == 'X'){
    Serial.println(currentPlayer); //troubleshooting
    if(coord>=0 && coord <=9){
      write();
      }
      
   delay(100); // Delay to prevent multiple presses
  
  }   
      // If game is not over, get computer's move
  else if(currentPlayer == 'O' && !terminal()) {
      Serial.println(currentPlayer); // troubleshooting
      coord = getComputerMove();
      if(coord>=0 && coord <=9){
      
          write();
          delay(100); // Delay to prevent multiple presses
      }
      
  }
  
  // Check for game over
  if (terminal()) {
    Serial.println("terminal");
    char result = winner();
    if (result != EMPTY) {
      Serial.print("Winner: ");
      Serial.println(result);
    } else {
      Serial.println("It's a tie!");
    }
    delay(2000); // Delay before restarting the game
    resetBoard();
  }
  delay(100);
}

void write()
{
   if (coord >= 0  && coord <=9) 
   {
    
    if (winner() == EMPTY) 
    {
      int stop = false;
      if (coord == 0 && board[0][0] == EMPTY) {board[0][0] = currentPlayer; prevRow = 0;prevCol = 0; currentPlayer = (currentPlayer == X) ? O : X;} else
      if (coord == 1 && board[1][0] == EMPTY) {board[1][0] = currentPlayer; prevRow = 1;prevCol = 0; currentPlayer = (currentPlayer == X) ? O : X;} else
      if (coord == 2 && board[2][0] == EMPTY) {board[2][0] = currentPlayer; prevRow = 2;prevCol = 0; currentPlayer = (currentPlayer == X) ? O : X;} else
      if (coord == 3 && board[0][1] == EMPTY) {board[0][1] = currentPlayer; prevRow = 0;prevCol = 1; currentPlayer = (currentPlayer == X) ? O : X;} else
      if (coord == 4 && board[1][1] == EMPTY) {board[1][1] = currentPlayer; prevRow = 1;prevCol = 1; currentPlayer = (currentPlayer == X) ? O : X;} else
      if (coord == 5 && board[2][1] == EMPTY) {board[2][1] = currentPlayer; prevRow = 2;prevCol = 1; currentPlayer = (currentPlayer == X) ? O : X;} else
      if (coord == 6 && board[0][2] == EMPTY) {board[0][2] = currentPlayer; prevRow = 0;prevCol = 2; currentPlayer = (currentPlayer == X) ? O : X;} else
      if (coord == 7 && board[1][2] == EMPTY) {board[1][2] = currentPlayer; prevRow = 1;prevCol = 2; currentPlayer = (currentPlayer == X) ? O : X;} else
      if (coord == 8 && board[2][2] == EMPTY) {board[2][2] = currentPlayer; prevRow = 2;prevCol = 2; currentPlayer = (currentPlayer == X) ? O : X;} else 
      {stop = true;}

      
      Serial.println("player");//troubleshooting

       // Switch player
      if (!stop) {
         if(currentPlayer == 'X')
         {strip.setPixelColor(coord,0,0,255);}
         else 
         {strip.setPixelColor(coord,255,0,0);}
      }
    }
    strip.show();
    if (winner() != EMPTY) {
      // Game is over, handle it here
      // For example, you can print the winner or restart the game
      char result = winner();
      if (result != EMPTY) {
        Serial.print("Winner: ");
        Serial.println(result);
      } else {
        Serial.println("It's a tie!");
      }
      delay(2000); // Delay before restarting the game
      resetBoard();
    }
  }
}


bool runCheck() {
  
  char customKey = customKeypad.getKey();
  coord = customKey-49;
  
  //Serial.print(currentPlayer); //troubleshooting

  return true;
}



bool terminal() {
  // Check for a winner
  if (winner() != EMPTY) {
    return true;
  }
  
  // Check for tie
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == EMPTY) {
        return false;
      }
    }
  }
  return true;
}

char winner() {
  // Check rows
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY) {
      return board[i][0];
    }
  }
  
  // Check columns
  for (int i = 0; i < 3; i++) {
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY) {
      return board[0][i];
    }
  }
  
  // Check diagonals
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY) {
    return board[0][0];
  }
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY) {
    return board[0][2];
  }
  
  return EMPTY; // No winner yet
}

void resetBoard() {
  // Reset the board
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = EMPTY;
      
    }
  }
  for (int i=0; i<=8; i++) {
  	strip.setPixelColor(i,0,0,0);  //set led color to none
  }
  currentPlayer = X; // X starts the game
}





int getComputerMove() {
  int bestScore = -1000;
  int bestMove = -1;
  
  // Loop through all empty cells
  for (int i = 0; i < 9; i++) {
    int row = i / 3;
    int col = i % 3;
    if (board[row][col] == EMPTY) {
      board[row][col] = currentPlayer;
      int score = minimax(board, 0, false);
      board[row][col] = EMPTY;
      if (score > bestScore) {
        bestScore = score;
        bestMove = i;
      }
    }
  }
  
  return bestMove;
}

int minimax(char board[3][3], int depth, bool isMaximizing) {
  if (terminal()) {
    //Serial.println("lll"); //troubleshooting
    char result = winner();
    if (result == X) {
      return -10 + depth;
    } else if (result == O) {
      return 10 - depth;
    } else {
      return 0;
    }
  }
  
  if (isMaximizing) {
    int bestScore = -1000;
    for (int i = 0; i < 9; i++) {
      int row = i / 3;
      int col = i % 3;
      if (board[row][col] == EMPTY) {
        board[row][col] = O;
        bestScore = max(bestScore, minimax(board, depth + 1, false));
        board[row][col] = EMPTY;
      }
    }
    return bestScore;
  } else {
    int bestScore = 1000;
    for (int i = 0; i < 9; i++) {
      int row = i / 3;
      int col = i % 3;
      if (board[row][col] == EMPTY) {
        board[row][col] = X;
        bestScore = min(bestScore, minimax(board, depth + 1, true));
        board[row][col] = EMPTY;
      }
    }
    return bestScore;
  }
}
