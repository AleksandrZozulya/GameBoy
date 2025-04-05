#include <Arduino.h>
#include <GameBoy.h>

GameBoy gb;
#define forward 3
#define left 4
#define right 5
#define backward 6

int dirX, dirY;
int FoodX, FoodY;
int x = 1;
int y = 0;

void randomFood();
void makeMove();
bool collision(int dirX, int dirY, int FoodX, int FoodY);

void setup()
{
  gb.begin(13);
  randomSeed(150);
  randomFood();
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
  if (forward == key)
  {
    y--;
    x = 0;
  }
  if (left == key)
  {
    x--;
    y = 0;
  }
  if (right == key)
  {
    x++;
    y = 0;
  }
  if (backward == key)
  {
    y++;
    x = 0;
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
