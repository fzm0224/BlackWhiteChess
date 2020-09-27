#include "chessboard.h"
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>
#include <QMovie>
#include <windows.h>

int ChessBoard::dx[8] = { 0, 0, 1, 1, 1, -1, -1, -1 };
int ChessBoard::dy[8] = { 1, -1, 0, 1, -1, 0, 1, -1 };
int ChessBoard::only = 1;

ChessBoard::ChessBoard(QWidget *parent) : QMainWindow(parent)
{

    this->setFixedSize(600, 600);

    //初始默认黑色方先下，1表示黑色方下 2表示白色方下
    flag = 1;

    //map棋盘初始化
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            map[i][j] = 0;
        }
    }

    chessX = -1;
    chessY = -1;

    //0代表无棋子 1代表黑色棋子 2代表白色棋子
    map[3][3] = map[4][4] = 2;
    map[3][4] = map[4][3] = 1;

    fontlabel.setPointSize(12);
    fontlabel.setFamily("宋体");
    fontlabel.setBold(true);

    label = new QLabel(this);
    //这里如果不设置大小显示会出问题
    label->resize(150, 40);
    label->setFont(fontlabel);
    label->move(225, 10);
    label->setStyleSheet("QLabel{"
                         "border-image:url(:/new/prefix1/res/caption.jpg)"
                         "}");


    fontbutton.setPointSize(10);
    fontbutton.setFamily("宋体");
    fontbutton.setBold(true);

    b1 = new QPushButton(this);
    b1->move(50, 550);
    b1->setText("重新开始");
    b1->setFont(fontbutton);
    b1->setStyleSheet("QPushButton{"
                      "border-image:url(:/new/prefix1/res/b3.png)"
                      "}"

                      "QPushButton:pressed{"
                      "border-image:url(:/new/prefix1/res/b4.png)"
                      "}"
                      );
    b1->resize(100, 40);

    b2 = new QPushButton(this);
    b2->move(450, 550);
    b2->setText("回主界面");
    b2->setFont(fontbutton);
    b2->setStyleSheet("QPushButton{"
                      "border-image:url(:/new/prefix1/res/b3.png)"
                      "}"

                      "QPushButton:pressed{"
                      "border-image:url(:/new/prefix1/res/b4.png)"
                      "}"
                      );
    b2->resize(100, 40);

    connect(b1, &QPushButton::released, this, &ChessBoard::dealrestart);
    connect(b2, &QPushButton::released, this, &ChessBoard::dealgotoui);

    label_black = new QLabel(this);
    label_black->move(10, 70);
    label_black->resize(40, 40);
    label_black->setStyleSheet("QLabel{"
                               "border-image:url(:/new/prefix1/res/2.png)"
                               "}");

    label_b_num = new QLabel(this);
    label_b_num->move(10, 120);
    label_b_num->resize(40, 40);

    label_white = new QLabel(this);
    label_white->move(550, 70);
    label_white->resize(40, 40);
    label_white->setStyleSheet("QLabel{"
                               "border-image:url(:/new/prefix1/res/1.png)"
                               "}");

    label_w_num = new QLabel(this);
    label_w_num->move(550, 120);
    label_w_num->resize(40, 40);
}

ChessBoard::~ChessBoard()
{

}

void ChessBoard::paintEvent(QPaintEvent *)
{
    //每次重绘都要重新设置棋子数量
    label_b_num->setText(QString("<center><h1 style=background-color:pink>%1</h1></center>").arg(num(1)));
    label_w_num->setText(QString("<center><h1 style=background-color:pink>%1</h1></center>").arg(num(2)));

    if (flag == 1)
    {
        label->setText(" 下棋者 : 黑色方 ");
    }
    if (flag == 2)
    {
        label->setText(" 下棋者 : 白色方 ");
    }

    gridW = width()/10;     //窗口宽度分10份
    gridH = height()/10;    //窗口高度分10份

    //棋盘起点坐标
    startX = gridW;
    startY = gridH;

    QPainter p(this);   //创建画家，指定窗口为绘图设备

    //背景图
    p.drawPixmap(rect(), QPixmap(":/new/prefix1/res/ice.jpg"));

    //设置画笔
    QPen pen;
    pen.setWidth(2);    //线宽
    p.setPen(pen);      //将画笔交给画家

    //取中间8份画棋盘
    for (int i = 0; i <= 8; i++)
    {
        //横线
        p.drawLine(startX, startY + i * gridH, startX + 8 * gridW, startY + i * gridH);

        //竖线
        p.drawLine(startX + i * gridW, startY, startX + i * gridW, startY + 8 * gridH);
    }
    //画棋子
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (1 == map[i][j])
            {
                //这里在打印时进行坐标翻转
                //注意这里2.png是黑色棋子，而代码中1代表黑色棋子，这里当时起名字的时候没在意，别搞混了
                p.drawPixmap(startX + j * gridW, startY + i * gridH,
                           gridW, gridH,
                           QPixmap(":/new/prefix1/res/2.png")
                           );
            }
            else if (2 == map[i][j])
            {
                p.drawPixmap(startX + j * gridW, startY + i * gridH,
                           gridW, gridH,
                           QPixmap(":/new/prefix1/res/1.png")
                           );
            }
            else if (OK(i,j))
            {
                QPoint point;
                point.setX(startX + j * gridW + (gridW / 2));
                point.setY(startY + i * gridH + (gridH / 2));
                p.drawEllipse(point, gridW / 5, gridH / 5);
            }
        }
    }

    //这段代码只在选择人机先走的时候使用一次，后面将使用mousePressEvent中的代码
    //这样做因为如果使用改代码段的话当鼠标事件发生后重绘界面时会调用Sleep，出现一秒的延迟
    //感觉这种方法不太好，但是暂时找不到更好的方式
    if (flag == ai.aip && only == 1)
    {
        AI();
        play(ai.air, ai.aic);
        end();

        update();
        only = 0;   //保证这段代码只执行一次
    }
}

void ChessBoard::mousePressEvent(QMouseEvent *e)
{
    //获取点击坐标
    int x = e->x();
    int y = e->y();

    //要保证点击点在棋盘范围里面
    if (x >= startX && x <= startX + 8 * gridW
            && y >= startY && y <= startX + 8 * gridH)
    {
        //棋盘的位置转换为坐标下标值
        //类似于a[i][j]的i和j
        //由于map中的xy坐标与屏幕的坐标系不同，所以这里xy应该翻转
        chessX = (x - startX)/gridW;
        chessY = (y - startY)/gridH;

        int temp = chessX;
        chessX = chessY;
        chessY = temp;

        if (!OK(chessX, chessY))
        {
            return ;
        }

        play(chessX, chessY);

        end();

        //立即更新窗口，如果使用update会被优化，导致显示延迟
        repaint();
    }

    if (flag == ai.aip)
    {
        Sleep(1000);
        AI();
        play(ai.air, ai.aic);
        end();

        update();
    }
}

bool ChessBoard::playOK(int x, int y, int dx, int dy)
{
    if (map[x][y] != 0)
        return false;
    int tx = x, ty = y;                  //tx和ty分别表示该点通过行和列往特定方向移动后的坐标
    while (tx + dx >= 0 && tx + dx < 8 && ty + dy >= 0 && ty + dy < 8 && map[tx + dx][ty + dy] == 3 - flag)
    {		//循环遍历，未到达边界或者右边的棋子是对方的则循环继续，否则循环退出
        tx += dx, ty += dy;    //移动坐标
    }
    //若使循环退出的那一格里，是对方的棋子，则(x,y)可落子，否则不可落子
    if (tx == x && ty == y)
        return false;		//难点，这一句不可少-->重点，不可去掉，判断邻近的位置是否可下时需要这一步
    if (tx + dx >= 0 && tx + dx < 8 && ty + dy >= 0 && ty + dy < 8 && map[tx + dx][ty + dy] == flag)
        return true;
    return false;
}

bool ChessBoard::OK(int x, int y)
{
    if (map[x][y])
    {
        return false;
    }
    for (int i = 0; i < 8; i++)  //只要一个方向满足可以下的条件，就可以下
        if (playOK(x, y, dx[i], dy[i]))
            return true;   //调用
    return false;
}

int ChessBoard::num(int k)
{
    int s = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (map[i][j] == k)
                s++;
    return s;
}

bool ChessBoard::end()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (OK(i, j))   //调用
                return false;

    flag = 3 - flag;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (OK(i, j))
                return false;  //调用

    if (num(1) < num(2))
    {
        gameover(0);
    }
    else if (num(1)>num(2))
    {
        gameover(1);
    }
    else
    {
        gameover(2);
    }
    return true;
}

void ChessBoard::gameover(int x)
{
    QDialog dlg;
    dlg.setFixedSize(400, 380);

    QLabel label;
    label.setParent(&dlg);
    label.move(0, 80);
    label.resize(400, 300);

    QLabel caption;
    caption.setParent(&dlg);
    caption.move(0, 0);
    caption.resize(400, 80);
    caption.setStyleSheet("QLabel{"
                          "background-color:black"
                          "}");

    QString str;
    if (x == 0)
    {
        if (ai.aip == 1)
        {
            str = QString("\n<center><h1><font color=white>Nice，你打败了AI！</font></h1></center>"
                          "\n<center><h3><font color=white>AI棋子：%1个  "
                          "你的棋子：%2个</font></h3></center>\n").arg(num(1)).arg(num(2));
        }
        else if(ai.aip == 2)
        {
            str = QString("\n<center><h1><font color=white>Oh no，你输给了AI！</font></h1></center>"
                          "\n<center><h3><font color=white>你的棋子：%1个  "
                          "AI棋子：%2个</font></h3></center>\n").arg(num(1)).arg(num(2));
        }
        else
        {
            str = QString("\n<center><h1><font color=white>白色方胜利！</font></h1></center>"
                          "\n<center><h3><font color=white>黑色棋子：%1个  "
                          "白色棋子：%2个</font></h3></center>\n").arg(num(1)).arg(num(2));
        }
    }
    else if (x == 1)
    {
        if(ai.aip == 1)
        {
            str = QString("\n<center><h1><font color=white>Oh no，你输给了AI！</font></h1></center>"
                          "\n<center><h3><font color=white>AI棋子：%1个  "
                          "你的棋子：%2个</font></h3></center>\n").arg(num(1)).arg(num(2));
        }
        else if(ai.aip == 2)
        {
            str = QString("\n<center><h1><font color=white>Nice，你打败了AI！</font></h1></center>"
                          "\n<center><h3><font color=white>你的棋子：%1个  "
                          "AI棋子：%2个</font></h3></center>\n").arg(num(1)).arg(num(2));
        }
        else
        {
            str = QString("\n<center><h1><font color=white>黑色方胜利！</font></h1></center>"
                          "\n<center><h3><font color=white>黑色棋子：%1个  "
                          "白色棋子：%2个</font></h3></center>\n").arg(num(1)).arg(num(2));
        }
    }
    else
    {
        if (ai.aip != 0)
        {
            str = QString("\n<center><h1><font color=white>平局-你跟AI五五开！</font></h1></center>"
                          "\n<center><h3><font color=white>你的棋子：%1个  "
                          "AI棋子：%2个</font></h3></center>\n").arg(num(1)).arg(num(2));
        }
        else
        {
            str = QString("\n<center><h1><font color=white>平局-五五开！</font></h1></center>"
                          "\n<center><h3><font color=white>黑色棋子：%1个  "
                          "白色棋子：%2个</font></h3></center>\n").arg(num(1)).arg(num(2));
        }
    }
    caption.setText(str);

    QMovie * movie;
    //创建动画
    if (x == 2)
    {
        movie = new QMovie(":/new/prefix1/res/wwk.gif");
    }
    else
    {
        if ((x == 1 && ai.aip == 1) || (x == 0 && ai.aip == 2))
        {
            movie = new QMovie(":/new/prefix1/res/wwk.gif");
        }
        else
        {
            movie = new QMovie(":/new/prefix1/res/v1.gif");
        }
    }
    //设置动画
    label.setMovie(movie);
    //启动动画
    movie->start();
    label.setScaledContents(true);

    dlg.exec();
}

void ChessBoard::turn(int tx, int ty, int dx, int dy)
{
    if (!playOK(tx, ty, dx, dy))    //难点，这一句不可少     //调用
        return;
    // 如果该方向的该位置可走，即存在同一方向且中间是敌方棋子填充且无空隙的同色棋子，则翻转敌方棋子
    while (tx + dx >= 0 && tx + dx < 8 && ty + dy >= 0 && ty + dy < 8 && map[tx + dx][ty + dy] == 3 - flag)
    {
        // 从该点起，沿着该方向，将对方颜色的棋子全部变为己方颜色的棋子，直到遇到己方棋子为止
        map[tx + dx][ty + dy] = flag; //在该处换掉棋子的颜色
        tx += dx, ty += dy;
    }
}

void ChessBoard::play(int x, int y)
{
    for (int i = 0; i < 8; i++)
        turn(x, y, dx[i], dy[i]);
    map[x][y] = flag;
    flag = 3 - flag;
}

void ChessBoard::dealrestart()
{
    //初始默认黑色方先下，1表示黑色方下 2表示白色方下
    flag = 1;

    //当选择人机先走的时候，让only=1，使得paintEvent中的判断通过，执行AI函数，实现AI先走
    //而其他情况下让这个不通过，调用mousePressEvent中的判断，来实现人机走棋时时间延缓1s
    if (ai.aip == 1)
    {
        only = 1;
    }

    //map棋盘初始化
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            map[i][j] = 0;
        }
    }

    chessX = -1;
    chessY = -1;

    //0代表无棋子 1代表黑色棋子 2代表白色棋子
    map[3][3] = map[4][4] = 2;
    map[3][4] = map[4][3] = 1;

    update();
}

void ChessBoard::dealgotoui()
{
    flag = 1;
    only = 1;

    //map棋盘初始化
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            map[i][j] = 0;
        }
    }

    chessX = -1;
    chessY = -1;
    ai.aip = 0;
    //0代表无棋子 1代表黑色棋子 2代表白色棋子
    map[3][3] = map[4][4] = 2;
    map[3][4] = map[4][3] = 1;

    update();

    emit mysignal();
}


/*
 * AI
 */


int ChessBoard::getPoint()
{
    int point = 0;
    for (int i1 = 0; i1<8; i1++)
        for (int j1 = 0; j1<8; j1++)
        {
            if (map[i1][j1] == ai.aip)
                point += ai.prio[i1][j1];   //若是ai的子，则加上该位置的积分
            if (map[i1][j1] == 3 - ai.aip)
                point -= ai.prio[i1][j1];   //若是玩家的子，则减去该位置的积分
        }
    return point;
}

void ChessBoard::AI3()//函数里面会改变p，但是调用函数不会改变p
{
    ai.p4 = ai.no;
    for (int iiii = 0; iiii < 8; iiii++)
        for (int jjjj = 0; jjjj < 8; jjjj++)  //第四层
        {
            if (!OK(iiii, jjjj))
                continue;  //调用
            for (int i = 0; i<8; i++)
                for (int j = 0; j<8; j++)
                    ai.temp4[i][j] = map[i][j];
            play(iiii, jjjj);//调用
            flag = 3 - flag;
            if (ai.p4 > getPoint())
                ai.p4 = getPoint();//调用
            for (int i = 0; i<8; i++)
                for (int j = 0; j<8; j++)
                    map[i][j] = ai.temp4[i][j];
        }
    if (ai.p4 == ai.no)
        ai.p4 = getPoint();  //调用
    if (ai.p3 < ai.p4)
        ai.p3 = ai.p4;
}
void ChessBoard::AI2()//函数里面会改变p，但是调用函数不会改变p
{
    ai.p3 = -ai.no;
    for (int iii = 0; iii < 8; iii++)
        for (int jjj = 0; jjj < 8; jjj++)  //第三层
        {
            if (!OK(iii, jjj))
                continue; //调用
            for (int i = 0; i<8; i++)
                for (int j = 0; j<8; j++)
                    ai.temp3[i][j] = map[i][j];
            play(iii, jjj);//调用
            AI3();
            flag = 3 - flag;
            for (int i = 0; i<8; i++)
                for (int j = 0; j<8; j++)
                    map[i][j] = ai.temp3[i][j];
        }
    if (ai.p3 == -ai.no)
    {
        flag = 3 - flag;
        AI3();
        flag = 3 - flag;
    }
    if (ai.p2 > ai.p3)
        ai.p2 = ai.p3;
}
void ChessBoard::AI()  //函数里面会改变p，但是调用函数不会改变p
{
    ai.p1 = -ai.no;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)  //第一层
        {
            if (!OK(i, j))
                continue;   //调用
            // 保存棋盘状态
            for (int m = 0; m < 8; m++)
                for (int n = 0; n < 8; n++)
                    ai.temp1[m][n] = map[m][n];
            play(i, j);
            ai.p2 = ai.no;
            for (int ii = 0; ii < 8; ii++)
            {
                for (int jj = 0; jj < 8; jj++)  //第二层
                {
                    if (!OK(ii, jj))
                        continue;   //调用
                    for (int i = 0; i<8; i++)
                        for (int j = 0; j<8; j++)
                            ai.temp2[i][j] = map[i][j];
                    play(ii, jj);   //调用
                    AI3();  //调用
                    flag = 3 - flag;
                    for (int i = 0; i<8; i++)
                        for (int j = 0; j<8; j++)
                            map[i][j] = ai.temp2[i][j];
                }
            }
            if (ai.p2 == ai.no)
            {
                flag = 3 - flag;
                AI2();  //调用
                flag = 3 - flag;
            }

            if (ai.p1 < ai.p2)
                ai.p1 = ai.p2, ai.air = i, ai.aic = j;   //难点，如果调用AI函数却1次都没有执行这条语句，那么AI就会下错位置

            flag = 3 - flag;

            for (int x = 0; x < 8; x++)
                for (int y = 0; y < 8; y++)
                    map[x][y] = ai.temp1[x][y];
        }
    }
}
