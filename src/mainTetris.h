#ifndef MAINTETRIS_H
#define MAINTETRIS_H
#include <Arduino.h>
#include <GameBoy.h>
#include "blocks.h"

extern GameBoy gb;

int xT = 2, yT = -1;
int rot = 0;

void drawBlock(byte arr[4][4], int xT, int yT);
void makeMoveTetris();
void createBlock(int num);



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

void makeMoveTetris(){
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
           } else {
            rot++;
           }
           
        }
    }
    
}

void createBlock(int num){
    xT = 2; yT = -1; rot = random(0,4);
    if(num == 0) gb.generateBlock(gb.block, I_Block_1, I_Block_2, I_Block_3, I_Block_4);
    if(num == 1) gb.generateBlock(gb.block, Z_Block_1, Z_Block_2, Z_Block_3, Z_Block_4);
    if(num == 2) gb.generateBlock(gb.block, S_Block_1, S_Block_2, S_Block_3, S_Block_4);
    if(num == 3) gb.generateBlock(gb.block, L_Block_1, L_Block_2, L_Block_3, L_Block_4);
    if(num == 4) gb.generateBlock(gb.block, J_Block_1, J_Block_2, J_Block_3, J_Block_4);
    if(num == 5) gb.generateBlock(gb.block, T_Block_1, T_Block_2, T_Block_3, T_Block_4);
    if(num == 6) gb.generateBlock(gb.block, O_Block_1, O_Block_2, O_Block_3, O_Block_4);
}

#endif