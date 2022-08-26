#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    m = new Widget(this);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    open = new QPushButton("Upload OBJ",this);
    stopRot = new QPushButton("Stop rotation", this);
    reset = new QPushButton("Reset", this);

    hbox->addWidget(open, 0, Qt::AlignCenter);
    hbox->addWidget(stopRot, 0, Qt::AlignCenter);
    hbox->addWidget(reset, 0 , Qt::AlignCenter);

    vbox->addStretch(1);
    vbox->addLayout(hbox);

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
        m->model[0] = objloader::Instance().load(filename);
        m->torus = objloader::Instance().load(":/files/torus.obj");
      qDebug() << "selected file path : " << filename.toUtf8();
    }

}

void MainWidget::onReset()
{
    m->model_count++;
}
