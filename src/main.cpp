#include <Arduino.h>
#include <GameBoy.h>

GameBoy gb;

// macros for buttons 
#define btnUp 3
#define btnLeft 4
#define btnRight 5
#define btnDown 6

//macros for direction
#define dirUp 0
#define dirRight 1
#define dirLeft 2
#define dirDown 3

// integers 
int FoodX, FoodY;
int x = 1;
int y = 0;
int direction = dirRight;
bool state;

unsigned int lenSnake = 2;

int snakeX[15];
int snakeY[15];

void randomFood();
void makeMove();
bool collision(int dirX, int dirY, int FoodX, int FoodY);
void move();
void drawSnake();
void drawFruit();
boolean isPartOfSnake(int x, int y);

void setup()
{
  gb.begin(13);
  randomSeed(analogRead(A2));
  randomFood();

  snakeX[0] = 4;
  snakeY[0] = 7;
}

void loop()
{
  makeMove();     //read buttons
  move();         //snake move

  // collision
  if(collision(snakeX[0], snakeY[0], FoodX, FoodY)){
    lenSnake++;
    randomFood();
  }

  gb.clearDisplay();
  drawSnake();
  drawFruit();
  delay(200);
}

void makeMove()
{
  int key = gb.getKey();
  Serial.println(key);
  if (btnUp == key)
  {
    y--;
    x = 0;
    direction = dirUp;
  }
  if (btnLeft == key)
  {
    x--;
    y = 0;
    direction = dirLeft;
  }
  if (btnRight == key)
  {
    x++;
    y = 0;
    direction = dirRight;
  }
  if (btnDown == key)
  {
    y++;
    x = 0;
    direction = dirDown;
  }
}

bool collision(int dirX, int dirY, int FoodX, int FoodY)
{
  if (dirY == FoodY and dirX == FoodX)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void drawFruit(){
  state = !state;
  if(state == true){
    gb.drawPoint(FoodX, FoodY);
  } else {
    gb.wipePoint(FoodX, FoodY);
  }
}

void randomFood()
{
  FoodX = random(0, 8);
  FoodY = random(0, 16);
  while (isPartOfSnake(FoodX, FoodY))
  {
    FoodX = random(0, 8);
    FoodY = random(0, 16);
  }
}

void move() {
  if((snakeX[0] == FoodX) and (snakeY[0] == FoodY)) {
    lenSnake++;
    randomFood();
  }

  for (int i = lenSnake - 1; i > 0; i--) {
      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
  }

  if (direction == dirUp) {
      if (snakeY[0] == 0) {
          snakeY[0] = 15;
      } else {
          snakeY[0]--;
      }
  } else if (direction == dirDown) {
      if (snakeY[0] == 15) {
          snakeY[0] = 0;
      } else {
          snakeY[0]++;
      }
  } else if (direction == dirLeft) {
      if (snakeX[0] == 0) {
          snakeX[0] = 7;
      } else {
          snakeX[0]--;
      }
  } else if (direction == dirRight) {
      if (snakeX[0] == 7) {
          snakeX[0] = 0;
      } else {
          snakeX[0]++;
      }
  }
}

void drawSnake(){
  for (size_t i = 0; i < lenSnake; i++)
  {
    gb.drawPoint(snakeX[i],snakeY[i]);
  }
}

boolean isPartOfSnake(int x, int y){
  for(int i = 0; i < lenSnake - 1; i++){
    if(x == snakeX[i] && y == snakeY[i]){
      return true;
    } 
  }
  return false; 
}

