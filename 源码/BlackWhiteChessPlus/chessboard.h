#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "chessai.h"

class ChessBoard : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = 0);
    ~ChessBoard();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

    //判断某个棋子的某个方向是否能下棋子，即判断该方向是否有同一方向且中间是敌方棋子填充且无空隙的同色棋子
    bool playOK(int x,int y, int dx, int dy);

    //判断某个格子是否能下棋子
    bool OK(int x, int y);

    //黑白棋子数目统计
    int num(int k);

    //游戏结束判断
    bool end();

    //翻转一个方向的所有可翻转的敌方棋子
    void turn(int tx, int ty, int dx, int dy);

    //翻转所有可翻转的棋子
    void play(int x, int y);

    //游戏结束
    void gameover(int x);

    //AI算法
    void AI();
    void AI2();
    void AI3();
    int getPoint();

private:
    int chessX;     //棋盘下标
    int chessY;

    int gridW;      //棋盘水平方向一个格子的宽度
    int gridH;      //棋盘水平方向一个格子的高度

    int startX;     //棋盘起点x坐标
    int startY;     //棋盘起点y坐标

    int flag;       //标记轮到哪方下棋

    int map[8][8];  //棋盘

    //方向向量，遍历8个方向
    static int dx[8];
    static int dy[8];

private:
    QLabel *label;
    QFont fontlabel;
    QFont fontbutton;
    QPushButton *b1;
    QPushButton *b2;
    QLabel *label_black;
    QLabel *label_white;
    QLabel *label_b_num;
    QLabel *label_w_num;

public:
    ChessAI ai;
    static int only;       //标志 位，为了使某段代码只执行一次,因为在人机中设定谁先走棋时使用，所以不能为私有

signals:
    void mysignal();

private slots:
    void dealrestart();
    void dealgotoui();
};

#endif // CHESSBOARD_H
