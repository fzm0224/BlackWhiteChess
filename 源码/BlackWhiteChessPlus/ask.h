#ifndef ASK_H
#define ASK_H

#include <QDialog>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

#include "chessai.h"
#include "chessboard.h"

class Ask : public QDialog
{
    Q_OBJECT
public:
    explicit Ask(QWidget *parent = 0);
    ~Ask();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QPoint p;
    QLabel label;
    QPushButton b1;
    QPushButton b2;

    ChessAI ask_ai;
    ChessBoard ask_board;

signals:

public slots:
    void deal_black();
    void deal_white();
};

#endif // ASK_H
