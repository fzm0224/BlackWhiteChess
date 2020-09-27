#include "chessai.h"
#include <QDebug>

int ChessAI::no = 1000;
int ChessAI::prio[8][8]=
{                       //prio是每个位置的优先级，数值越高越好
   { 80, -20, 8, 6, 6, 8, -20, 80 },
   { -20, -20, 0, -1, -1, 0, -20, -20 },
   { 8, 0, 3, 5, 5, 3, 0, 8 },
   { 6, -1, 5, 1, 1, 5, -1, 6 },
   { 6, -1, 5, 1, 1, 5, -1, 6 },
   { 8, 0, 3, 5, 5, 3, 0, 8 },
   { -20, -20, 0, -1, -1, 0, -20, -20 },
   { 80, -20, 8, 6, 6, 8, -20, 80 }
};
int ChessAI::aip = 0;

ChessAI::ChessAI()
{
    air = 0;
    aic = 0;

    p1 = 0;
    p2 = 0;
    p3 = 0;
    p4 = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //4层博弈对应的AI分数和棋局
            temp1[i][j] = 0;
            temp2[i][j] = 0;
            temp3[i][j] = 0;
            temp4[i][j] = 0;
        }
    }
}

ChessAI::~ChessAI()
{

}
