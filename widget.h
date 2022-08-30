#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer>
#include <QKeyEvent>
#include "objloader.h"


class Widget : public QOpenGLWidget
{
    friend class MainWidget;
    Q_OBJECT
    QTimer *paintTimer; //Таймер
    GLfloat angle = 0; //Угол вращения
    GLuint model = 0; //Номер display list для вывода нужной модели
    GLuint texture[3]; //Текстуры
    GLuint torus = 1;

    GLuint texture_count = 0; //Номер текуйщей текстуры

    void initLight(); //Включить свет
    GLuint DrawBackground();
    void LoadGLTextures(); //Загрузить текстуры
    void initTexture(uint index, QImage &texture1); //Поставить настройки для текстуры
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    Widget(QWidget *parent = nullptr);
    bool resetMatrix = true;

private:
    QString modelURL = ":/files/monkey2.obj";

protected:
    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override;
    void paintGL() override;
};
#endif // WIDGET_H
