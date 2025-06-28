#ifndef MAINTETRIS_H
#define MAINTETRIS_H
#include <Arduino.h>
#include <GameBoy.h>
#include "blocks.h"

extern GameBoy gb;

byte WIN[16][8] = {
    {0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 0, 0, 0, 1, 0}};

int xT = 2, yT = -1;
int rot = 0;
unsigned int level = 0, acc = 1;
int speed = 100;

unsigned int score = 0;

void drawBlock(byte arr[4][4], int xT, int yT);
void makeMoveTetris();
void createBlock(int num);
bool lossTetris();
bool win();
void mainTetris();

void mainTetris()
{
    if (win() == true) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 16; j++) {
                gb.wipePoint(i, j);
                gb.setLed(i, j, WIN[j][i]);
            }
        }
        delay(2000);
        gb.clearDisplay();
        score = 0;
        level = 0;
    }
    if (lossTetris() == true)
    {
        for (size_t i = 0; i < 8; i++)
        {
            for (size_t j = 0; j < 16; j++)
            {
                gb.wipePoint(i, j);
            }
        }
        Serial.println("You lost the game");
        gb.sound(COLLISION);
        gb.testMatrix(10);
    }

    makeMoveTetris();

    if (gb.checkBlockCollision(gb.block[rot], xT, yT + 1))
    {
        gb.memBlock(gb.block[rot], xT, yT);
        int lines = gb.fullLine();

        if (lines != 0)
        {
            score += lines;
            level += lines;
        }

        if (level >= 5)
        {
            gb.sound(SCORE);
            acc += 1;
            level = 0;
        }

        createBlock(random(0, 7));
    }
    else
    {
        yT++;
    }

    gb.drawDisplay();
    drawBlock(gb.block[rot], xT, yT);
    delay(speed / acc);
}

bool win()
{
    if (score >= 20)
    {
        return true;
    }
    return false;
}

void drawBlock(byte arr[4][4], int xT, int yT)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (arr[j][i] == 1)
            {
                gb.drawPoint(xT + i, yT + j);
            }
        }
    }
}

void makeMoveTetris()
{
    if (gb.getKey() == 4)
    {
        if (!gb.checkBlockCollision(gb.block[rot], xT - 1, yT))
        {
            xT--;
        }
    }
    if (gb.getKey() == 5)
    {
        if (!gb.checkBlockCollision(gb.block[rot], xT + 1, yT))
        {
            xT++;
        }
    }
    if (gb.getKey() == 1)
    {
        if (!gb.checkBlockCollision(gb.block[rot + 1], xT + 1, yT))
        {
            if (rot == 3)
            {
                rot = 0;
            }
            else
            {
                rot++;
            }
        }
    }
}

void createBlock(int num)
{
    xT = 2;
    yT = -1;
    rot = random(0, 4);
    if (num == 0)
        gb.generateBlock(gb.block, I_Block_1, I_Block_2, I_Block_3, I_Block_4);
    if (num == 1)
        gb.generateBlock(gb.block, Z_Block_1, Z_Block_2, Z_Block_3, Z_Block_4);
    if (num == 2)
        gb.generateBlock(gb.block, S_Block_1, S_Block_2, S_Block_3, S_Block_4);
    if (num == 3)
        gb.generateBlock(gb.block, L_Block_1, L_Block_2, L_Block_3, L_Block_4);
    if (num == 4)
        gb.generateBlock(gb.block, J_Block_1, J_Block_2, J_Block_3, J_Block_4);
    if (num == 5)
        gb.generateBlock(gb.block, T_Block_1, T_Block_2, T_Block_3, T_Block_4);
    if (num == 6)
        gb.generateBlock(gb.block, O_Block_1, O_Block_2, O_Block_3, O_Block_4);
}

bool lossTetris()
{
    if (gb.checkBlockCollision(gb.block[rot], xT, 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif