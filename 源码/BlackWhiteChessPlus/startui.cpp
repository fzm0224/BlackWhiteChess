#include "startui.h"
#include <QMessageBox>
#include <QDebug>
#include <QDir>

StartUI::StartUI(QWidget *parent)
    : QWidget(parent)
{
//打印当前相对路径，下面加载背景音乐时由于没有找对当前的相对路径瞎忙活了半天
//    qDebug() << "+++++++++++++++++++++++++++++++++++++++++++";
//    qDebug()<<"current currentPath: "<<QDir::currentPath();
//    qDebug() << "-------------------------------------------";

    //设置字体
    font.setPointSize(10);
    font.setFamily("宋体");
    font.setBold(true);

    //双人对战
    bpp = new QPushButton(this);
    bpp->resize(100, 35);
    bpp->setStyleSheet("QPushButton{"
                       "border-image:url(:/new/prefix1/res/b3.png)"
                       "}"

                       "QPushButton:pressed{"
                       "border-image:url(:/new/prefix1/res/b4.png)"
                       "}");
    bpp->setFont(font);
    bpp->setText("双人对战");
    bpp->move(50, 320);

    //人机对战
    bpc = new QPushButton(this);
    bpc->resize(100, 35);
    bpc->setStyleSheet("QPushButton{"
                       "border-image:url(:/new/prefix1/res/b3.png)"
                       "}"

                       "QPushButton:pressed{"
                       "border-image:url(:/new/prefix1/res/b4.png)"
                       "}");
    bpc->setFont(font);
    bpc->setText("人机对战");
    bpc->move(180, 320);

    //帮助
    help = new QPushButton(this);
    help->resize(100, 35);
    help->setStyleSheet("QPushButton{"
                       "border-image:url(:/new/prefix1/res/b3.png)"
                       "}"

                       "QPushButton:pressed{"
                       "border-image:url(:/new/prefix1/res/b4.png)"
                       "}");
    help->setFont(font);
    help->setText("帮助");
    help->move(320, 320);

    //关于
    about = new QPushButton(this);
    about->resize(100, 35);
    about->setStyleSheet("QPushButton{"
                       "border-image:url(:/new/prefix1/res/b3.png)"
                       "}"

                       "QPushButton:pressed{"
                       "border-image:url(:/new/prefix1/res/b4.png)"
                       "}");
    about->setFont(font);
    about->setText("关于");
    about->move(450, 320);

    player = new QMediaPlayer(this);
    //绝对路径
    //player->setMedia(QUrl::fromLocalFile("E:/Code_Qt/Project/build-BlackWhiteChessPlus-Desktop_Qt_5_4_1_MinGW_32bit-Debug/music/background-music.mp3"));
    //相对路径
//    player->setMedia(QUrl::fromLocalFile("./music/background-music.mp3"));
//    player->setVolume(100);
//    player->play();

    //循环播放背景音乐
    //播放列表
    playlist = new QMediaPlaylist(this);
    playlist->addMedia(QUrl::fromLocalFile("./music/background-music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    player = new QMediaPlayer(this);
    player->setPlaylist(playlist);
    player->setVolume(50);
    player->play();

    connect(bpp, &QPushButton::released, this, &StartUI::deal_bpp);
    connect(bpc, &QPushButton::released, this, &StartUI::deal_bpc);
    connect(about, &QPushButton::released, this, &StartUI::deal_about);
    connect(help, &QPushButton::released, this, &StartUI::deal_help);
    connect(&board, &ChessBoard::mysignal, this, &StartUI::dealmysignal);
}

StartUI::~StartUI()
{

}

void StartUI::deal_bpp()
{
    this->hide();
    board.show();
}

void StartUI::deal_bpc()
{
    this->hide();
    board.show();

    ask = new Ask(this);

//    int ret = QMessageBox::question(this, "人机先下棋？", "在与人机对战中，是否设置为人机先下棋？\n如果不选择默认为玩家先下。");
//    switch(ret)
//    {
//    case QMessageBox::Yes:
//        board.ai.aip = 1;
//        board.only = 1;
//        break;
//    case QMessageBox::No:
//        board.ai.aip = 2;
//        //细节：这里设定可以让首次设定玩家先走的情况下调用mousePressEvent中的判定，
//        //使人机下第一步棋的时候仍然要等待一秒。
//        board.only = 0;
//        break;
//    default:
//        break;
//    }
}

void StartUI::deal_about()
{
    About about;
    about.show();
}

void StartUI::deal_help()
{
    QDialog dlg;
    dlg.setFixedSize(600, 500);
    dlg.setStyleSheet("QDialog{"
                      "border-image:url(:/new/prefix1/res/bg.jpg)"
                      "}");

    QFont fontcaption;
    fontcaption.setPointSize(20);
    fontcaption.setFamily("宋体");
    fontcaption.setBold(true);

    QLabel caption;
    caption.setParent(&dlg);
    caption.move(125, 30);
    caption.resize(150, 50);
    caption.setStyleSheet("QLabel{"
                          "border-image:url(:/new/prefix1/res/caption.jpg)"
                          "}");
    caption.setFont(fontcaption);
    caption.setText("<center>游戏简介</center>");

    QFont fontlabel;
    fontlabel.setPointSize(13);
    fontlabel.setFamily("宋体");
    fontlabel.setBold(true);

    QLabel label;
    label.setParent(&dlg);
    label.move(52, 110);
    label.resize(295, 330);
    label.setFont(fontlabel);
    //让QLabel能够自动判断并换行显示：
    label.setWordWrap(true);
    label.setAlignment(Qt::AlignTop);
    label.setText("\n    黑白棋又叫翻转棋,游戏通过相互翻转对方的棋子，最后以棋盘上谁的棋子多来判断胜负。\n\n"
                  "    下子方式：把自己颜色的棋子放在棋盘的空格上，而当自己放下的棋子在横、竖、斜八个方向内有一个自己的棋子，"
                  "则被夹在中间的对方棋子全部翻转会成为自己的棋子。夹住的位置上必须全部是对手的棋子，不能有空格。"
                  "并且，只有在可以翻转棋子的地方才可以下子。\n\n"
                  "注：在本游戏中通过圆圈来直接标注出可下子位置。");
    //关于颜色的英文： khaki 卡其色    brown 咖啡色   grey 灰色     powderblue 粉蓝色     royalblue 宝石蓝
    label.setStyleSheet("QLabel{"
                        "background-color:skyblue"
                        "}");
    dlg.exec();
}

void StartUI::dealmysignal()
{
    board.hide();
    this->show();
}
