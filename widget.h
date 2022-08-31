#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer>
#include <QKeyEvent>
#include "objloader.h"


class Widget : public QOpenGLWidget
{
    Q_OBJECT


public:
    Widget(QWidget *parent = nullptr);
    void setModel(QString newModel);

    bool isModelRotation() const;
    void setRotation(bool mode);

public slots:
    void setResetMatrix();


private:
    QTimer *paintTimer; //Таймер
    GLfloat angle = 0; //Угол вращения
    GLuint model = 0; //Номер display list для вывода нужной модели
    GLuint texture[3]; //Текстуры
    GLuint torus = 1;

    GLuint texture_count = 0; //Номер текуйщей текстуры

    bool resetMatrix = true;
    bool modelRotation = true;
    bool isManuallyStoped = true;

    float xMouseRot, yMouseRot , zMouseRot;
    QPoint mPos;

    void initLight(); //Включить свет
    GLuint DrawBackground();
    void LoadGLTextures(); //Загрузить текстуры
    void initTexture(uint index, QImage &texture1); //Поставить настройки для текстуры
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

protected:
    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override;
    void paintGL() override;
};
#endif // WIDGET_H
