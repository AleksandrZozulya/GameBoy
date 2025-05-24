#ifndef MAINRACING_H
#define MAINRACING_H
#include <Arduino.h>
#include <GameBoy.h>

GameBoy gb;


int enemy_x = 2;
int car_speed = 100;
int playerCar_x = 2;
int playerCar_y = 12;

void enemyCar(int x, int y);
void playerCar(int x, int y);
void wipePlayerCar(int x, int y);
void wipeEnemyCar(int x, int y);
void createLine(int y);
void wipeLine(int y);
bool carCollision(int playerCar_x, int playerCar_y, int enemy_car_x, int enemy_car_y);
void mainRacing();

void mainRacing()
{
    enemy_x = random(0, 10);
    if (enemy_x > 5)
    {
        enemy_x = 2;
    }
    else
    {
        enemy_x = 5;
    }
    for (int enemy_y = -3; enemy_y < 16; enemy_y++)
    {
        createLine(enemy_y);
        createLine(enemy_y + 5);
        createLine(enemy_y + 10);
        createLine(enemy_y + 15);
        createLine(enemy_y - 5);
        createLine(enemy_y - 10);
        createLine(enemy_y - 15);
        enemyCar(enemy_x, enemy_y);
        if (gb.getKey() == 4)
        {
            playerCar_x = 2;
            wipePlayerCar(5, 12);
        }
        else if (gb.getKey() == 5)
        {
            playerCar_x = 5;
            wipePlayerCar(2, 12);
        }
        playerCar(playerCar_x, playerCar_y);
        if (carCollision(playerCar_x, playerCar_y, enemy_x, enemy_y) == true)
        {
            gb.sound(COLLISION);
            gb.testMatrix(10);
            gb.clearDisplay();
            return;
        }
        delay(car_speed);
        wipeLine(enemy_y);
        wipeLine(enemy_y + 5);
        wipeLine(enemy_y + 10);
        wipeLine(enemy_y + 15);
        wipeLine(enemy_y - 5);
        wipeLine(enemy_y - 10);
        wipeLine(enemy_y - 15);
        wipeEnemyCar(enemy_x, enemy_y);
    }
}

bool carCollision(int playerCar_x, int playerCar_y, int enemy_car_x, int enemy_car_y)
{
    if (playerCar_y == enemy_car_y && playerCar_x == enemy_car_x)
    {
        return true;
    }
    if (playerCar_x == enemy_car_x && enemy_car_y > 12)
    {
        return true;
    }
    return false;
}

void enemyCar(int x, int y)
{
    gb.drawPoint(x, y);
    gb.drawPoint(x - 1, y - 1);
    gb.drawPoint(x, y - 1);
    gb.drawPoint(x + 1, y - 1);
    gb.drawPoint(x, y - 2);
    gb.drawPoint(x + 1, y - 3);
    gb.drawPoint(x - 1, y - 3);
}

void playerCar(int x, int y)
{
    gb.drawPoint(x, y);
    gb.drawPoint(x + 1, y + 1);
    gb.drawPoint(x, y + 1);
    gb.drawPoint(x - 1, y + 1);
    gb.drawPoint(x, y + 2);
    gb.drawPoint(x - 1, y + 3);
    gb.drawPoint(x + 1, y + 3);
}

void wipePlayerCar(int x, int y)
{
    gb.wipePoint(x, y);
    gb.wipePoint(x + 1, y + 1);
    gb.wipePoint(x, y + 1);
    gb.wipePoint(x - 1, y + 1);
    gb.wipePoint(x, y + 2);
    gb.wipePoint(x - 1, y + 3);
    gb.wipePoint(x + 1, y + 3);
}

void wipeEnemyCar(int x, int y)
{
    gb.wipePoint(x, y);
    gb.wipePoint(x - 1, y - 1);
    gb.wipePoint(x, y - 1);
    gb.wipePoint(x + 1, y - 1);
    gb.wipePoint(x, y - 2);
    gb.wipePoint(x + 1, y - 3);
    gb.wipePoint(x - 1, y - 3);
}

void createLine(int y)
{
    gb.drawPoint(0, y);
    gb.drawPoint(0, y + 1);
    gb.drawPoint(0, y + 2);
    gb.drawPoint(7, y);
    gb.drawPoint(7, y + 1);
    gb.drawPoint(7, y + 2);
}

void wipeLine(int y)
{
    gb.wipePoint(0, y);
    gb.wipePoint(0, y + 1);
    gb.wipePoint(0, y + 2);
    gb.wipePoint(7, y);
    gb.wipePoint(7, y + 1);
    gb.wipePoint(7, y + 2);
}

#endif