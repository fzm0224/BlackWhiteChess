#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = 0);
    ~About();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QPoint p;
    QLabel label;

signals:

public slots:
};

#endif // ABOUT_H
