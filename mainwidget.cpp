#include "mainwidget.h"
#include <GL/gl.h>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    m = new Widget(this);

//    QBoxLayout *gl = new QBoxLayout(this);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    open = new QPushButton("Upload OBJ",this);
    stopRot = new QPushButton("Stop rotation", this);
    reset = new QPushButton("Reset", this);


//    gl->setSpacing(0);
//    gl->setContentsMargins(0, 0, 0, 0);
//    gl->addWidget(m);
    vbox->addWidget(m);


    hbox->addWidget(open, 0, Qt::AlignCenter);
    hbox->addWidget(stopRot, 0, Qt::AlignCenter);
    hbox->addWidget(reset, 0 , Qt::AlignCenter);

    vbox->addStretch(1);
    vbox->addLayout(hbox);

//    vbox->addLayout(gl);

    connect(open, &QPushButton::clicked, this, &MainWidget::openOBJ);
    connect(stopRot, &QPushButton::clicked, this, &MainWidget::onStopRot);
    connect(reset, &QPushButton::clicked, this, &MainWidget::onReset);

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

}
