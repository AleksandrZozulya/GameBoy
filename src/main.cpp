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
int dirX, dirY;
int FoodX, FoodY;
int x = 1;
int y = 0;
int direction = dirRight;

int snakeX[10];
int snakeY[10];

void randomFood();
void makeMove();
bool collision(int dirX, int dirY, int FoodX, int FoodY);

void setup()
{
  gb.begin(13);
  randomSeed(150);
  randomFood();

  snakeX[0] = 4;
  snakeY[0] = 7;
}
void loop()
{
  makeMove();
  dirX = dirX + x;
  dirY = dirY + y;
  if (dirY > 15)
  {
    dirY = 0;
  }
  if (dirX > 7)
  {
    dirX = 0;
  }
  if (dirY < 0)
  {
    dirY = 15;
  }
  if (dirX < 0)
  {
    dirX = 7;
  }
  if(collision(dirX, dirY, FoodX, FoodY)){
    randomFood();
  }
  gb.clearDisplay();
  gb.drawPoint(dirX, dirY);
  gb.drawPoint(FoodX, FoodY);
  delay(300);
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
void randomFood()
{
  FoodX = random(0, 8);
  FoodY = random(0, 16);
}

