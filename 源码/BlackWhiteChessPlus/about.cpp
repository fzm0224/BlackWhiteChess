#include "about.h"

About::About(QWidget *parent) : QDialog(parent)
{
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);

    resize(500, 500);

    QFont font;
    font.setBold(true);
    font.setFamily("宋体");
    font.setPointSize(12);

    label.setParent(this);
    label.move(100, 200);
    label.resize(260, 210);
    label.setFont(font);
    label.setText("产品名：黑白棋\n\n作者：李勇峰\n\n时间：2018年5月24日 周四\n\n版本：V3.0\n\n编译环境：Qt 5.4\n\n----- 点击鼠标右键退出！-----");

//    label.setStyleSheet("QLabel{"
//                        "border-color:red"
//                        "}");

    this->exec();
}

About::~About()
{

}

void About::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0, 0, QPixmap(":/new/prefix1/res/about.png"));
}

void About::mousePressEvent(QMouseEvent *e)
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

void About::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::LeftButton)
    {
        move(e->globalPos() - p);
    }
}
