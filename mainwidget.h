#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include "widget.h"


class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);


private:
    Widget *m;
    QPushButton *open;
    QPushButton *stopRot;
    QPushButton *reset;
    void resizeEvent(QResizeEvent *e);

private slots:
    void onStopRot();
    void openOBJ();
};


#endif // MAINWIDGET_H
