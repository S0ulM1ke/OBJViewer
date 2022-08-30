#include "mainwidget.h"
#include <GL/gl.h>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    m = new Widget(this);

    QGridLayout *gl = new QGridLayout(this);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    gl->setContentsMargins(0, 0, 0, 0);
    gl->addWidget(m);

    open = new QPushButton("Upload OBJ",this);
    stopRot = new QPushButton("Stop rotation", this);
    reset = new QPushButton("Reset", this);

    hbox->addWidget(open, 0, Qt::AlignCenter);
    hbox->addWidget(stopRot, 0, Qt::AlignCenter);
    hbox->addWidget(reset, 0 , Qt::AlignCenter);

    vbox->addStretch(1);
    vbox->addLayout(hbox);

    m->setLayout(vbox);

    //  СДЕЛАЙ СЕТЕРЫ И ГЕТЕРЫ ДУБИНА!!!

    connect(open, &QPushButton::clicked, this, &MainWidget::openOBJ);
    connect(stopRot, &QPushButton::clicked, this, &MainWidget::onStopRot);
    connect(reset, &QPushButton::clicked, this, &MainWidget::onReset);

}

void MainWidget::resizeEvent(QResizeEvent *e)
{

    Q_UNUSED(e);
//    QSize currentSize = e->size();
//    m->resizeGL(currentSize.width(), currentSize.height());
//    m->repaint();
//    QWidget::resizeEvent(e);

}

void MainWidget::onStopRot()
{
    if (m->paintTimer->isActive()){
        m->paintTimer->stop();
        stopRot->setText("Rotate");
    }
    else {
        m->paintTimer->start();
        stopRot->setText("Stop rotation");
    }
}

void MainWidget::openOBJ()
{
    QString filename =  QFileDialog::getOpenFileName(
              this,
              "Open OBJ file",
              QDir::currentPath(),
              "All files (*.*) ;; OBJ model files (*.obj)");

    if( !filename.isNull() )
    {

       glDeleteLists(m->model, 0);
        m->model = objloader::Instance().load(filename);
//        m->modelURL = filename;
//        m->torus = objloader::Instance().load(":/files/torus.obj");
    }

}

void MainWidget::onReset()
{
    m->resetMatrix = false;
    m->angle = 0;
}
