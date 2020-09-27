#ifndef CHESSAI_H
#define CHESSAI_H


class ChessAI
{
public:
    ChessAI();
    ~ChessAI();

public:
    static int aip;

public:
    static int no;//AI的分数不可能达到的上界值
    static int prio[8][8];

    int air;
    int aic;

    int p1;
    int p2;
    int p3;
    int p4;

    //4层博弈对应的AI分数和棋局
    int temp1[8][8];
    int temp2[8][8];
    int temp3[8][8];
    int temp4[8][8];
};

#endif // CHESSAI_H
