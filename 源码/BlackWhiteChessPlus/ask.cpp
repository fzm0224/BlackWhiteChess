#include "ask.h"

Ask::Ask(QWidget *parent) : QDialog(parent)
{
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);

    resize(300, 300);

    QFont font;
    font.setBold(true);
    font.setFamily("黑体");
    font.setPointSize(12);

    b1.move(80, 120);
    b1.resize(50, 50);
    b1.setParent(this);
    b1.setFont(font);
    b1.setText("黑");
    b1.setStyleSheet("QPushButton{"
                     "border-image:url(:/new/prefix1/res/circle4.png)"
                     "}"
                     "QPushButton:pressed{"
                     "border-image:url(:/new/prefix1/res/circle3.png)"
                     "}");

    b2.move(180, 120);
    b2.resize(50, 50);
    b2.setParent(this);
    b2.setFont(font);
    b2.setText("白");
    b2.setStyleSheet("QPushButton{"
                     "border-image:url(:/new/prefix1/res/circle4.png)"
                     "}"
                     "QPushButton:pressed{"
                     "border-image:url(:/new/prefix1/res/circle3.png)"
                     "}");

    label.setParent(this);
    label.move(60, 60);
    label.resize(200, 70);
    label.setFont(font);
    label.setText("    在与人机的对战中,你\n要选择黑色方还是白色方？\n黑色方为先下棋的一方。\n");
//    label.setStyleSheet("QLabel{"
//                        "background-color:red"
//                        "}");


    connect(&b1, &QPushButton::pressed, this, &Ask::deal_black);
    connect(&b2, &QPushButton::pressed, this, &Ask::deal_white);

    exec();
}

Ask::~Ask()
{

}

void Ask::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0, 0, QPixmap(":/new/prefix1/res/dlg2.png"));
}

void Ask::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
    {
        //如果是右键
        close();
    }
    else if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void Ask::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::LeftButton)
    {
        move(e->globalPos() - p);
    }
}

void Ask::deal_black()
{
    ask_ai.aip = 2;
    //细节：这里设定可以让首次设定玩家先走的情况下调用mousePressEvent中的判定，
    //使人机下第一步棋的时候仍然要等待一秒。
    ask_board.only = 0;
    this->close();
}

void Ask::deal_white()
{
    ask_ai.aip = 1;
    ask_board.only = 1;
    this->close();
}
