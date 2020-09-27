#ifndef STARTUI_H
#define STARTUI_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>

#include "chessboard.h"
#include "about.h"
#include "ask.h"

class StartUI : public QWidget
{
    Q_OBJECT

public:
    StartUI(QWidget *parent = 0);
    ~StartUI();

private:
    QPushButton *bpp;
    QPushButton *bpc;
    QPushButton *help;
    QPushButton *about;
    QFont font;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;

    ChessBoard board;
    Ask *ask;

public slots:
    void deal_bpp();
    void deal_bpc();
    void deal_help();
    void deal_about();
    void dealmysignal();
};

#endif // STARTUI_H
