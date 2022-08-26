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
    GLuint model[3]; //Номер display list для вывода нужной модели
    GLuint texture[3]; //Текстуры
    GLuint torus = 0;

    GLuint texture_count = 0; //Номер текуйщей текстуры
    GLuint model_count = 0; //Номер текущей модели

    void initLight(); //Включить свет
    GLuint drawCube(); //Нарисовать куб
    void LoadGLTextures(); //Загрузить текстуры
    void initTexture(uint index, QImage &texture1); //Поставить настройки для текстуры
    int loadObject(const QString &filename);
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    Widget(QWidget *parent = nullptr);
protected:
    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override;
    void paintGL() override;
};
#endif // WIDGET_H
