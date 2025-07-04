#include <Arduino.h>
#include <GameBoy.h>
#include <mainRacing.h>
#include <mainSnake.h>
#include <mainTetris.h>

GameBoy gb;

int mode;
int modeCount;

bool gameTetrisStarted = false;

void mainMenu();
int modeSelector();
void switchMode(int mode);

byte ARROWS[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

byte CAR[8][8] = {
    {0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0}};

byte SNAKE[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}};

byte TETRIS[8][8] = {
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0}};
void setup()
{
    gb.begin(15);
    randomSeed(analogRead(A5));
}

void loop()
{
    if (gb.getKey() == 2 && modeSelector() == 0)
    {
        gb.clearDisplay();
        mode = 1;
    }
    else if (gb.getKey() == 2 && modeSelector() == 1)
    {
        gb.clearDisplay();
        mode = 2;
    }
    else if (gb.getKey() == 2 && modeSelector() == 2)
    {
        gb.clearDisplay();
        mode = 3;
    }
    else if (gb.getKey() == 1)
    {
        gb.clearDisplay();
        mode = 0;
    }
    switchMode(mode);
}

void mainMenu()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            gb.wipePoint(i, j);
            gb.setLed(i, j, ARROWS[j][i]);
        }
    }
    if (modeSelector() == 0)
    {

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                gb.wipePoint(i, 8 + j);
                gb.setLed(i, 8 + j, CAR[j][i]);
            }
        }
    }
    if (modeSelector() == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                gb.wipePoint(i, 8 + j);
                gb.setLed(i, 8 + j, SNAKE[j][i]);
            }
        }
    }
    if (modeSelector() == 2)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                gb.wipePoint(i, 8 + j);
                gb.setLed(i, 8 + j, TETRIS[j][i]);
            }
        }
    }
}

int modeSelector()
{
    if (gb.getKey() == 4)
    {
        modeCount++;
        delay(250);
        if (modeCount > 2)
        {
            modeCount = 0;
        }
    }
    else if (gb.getKey() == 5)
    {
        modeCount--;
        delay(250);
        if (modeCount < 0)
        {
            modeCount = 2;
        }
    }
    return modeCount;
}

void switchMode(int mode)
{
    switch (mode)
    {
    case 0:
        mainMenu();
        break;
    case 1:
        mainRacing();
        break;
    case 2:
        mainSnake();
        break;
    case 3:
        if (!gameTetrisStarted)
        {
            createBlock(random(0, 7));
            gameTetrisStarted = true;
        }
        mainTetris();
        break;
    }
}
