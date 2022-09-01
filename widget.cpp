#include "widget.h"
#include <gl/GLU.h>

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    resize(800,600); // задаем размеры окна
    paintTimer = new QTimer(this); // создаю таймер
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    paintTimer->start();
}

void Widget::setModel(QString newModel)
{
    glDeleteLists(model, 0);
    model = objloader::Instance().load(newModel);
}

void Widget::setResetMatrix()
{
    resetMatrix = false;
    xPrevRot = 0;
    yPrevRot = 0;
    xMouseRot = 0;
    yMouseRot = 0;
    angle = 0;
    zWheel = 1.0f;
}

void Widget::setRotation(bool mode)
{
    modelRotation = mode;
    isManuallyStoped = mode;
}

bool Widget:: isModelRotation() const
{
    return modelRotation;
}

void Widget::initTexture(uint index, QImage &texture1)
{
    texture1.convertTo(QImage::Format_RGBA8888); // формат текстуры OpenGL
    glBindTexture(GL_TEXTURE_2D, texture[index]); // привязываю текстуру GL_Texture_2d к участку памяти texture[index]
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // параметры фильтрации
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, GLsizei(texture1.width()), GLsizei(texture1.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits()); // заливаю текстуру
}

void Widget::mousePressEvent(QMouseEvent *mo)
{

    mPos = mo->pos();
    if (mo->button() == Qt::LeftButton && isManuallyStoped) {
        modelRotation = false;
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *mo)
{
    xPrevRot = xMouseRot;
    yPrevRot = yMouseRot;
    if (mo->button() == Qt::LeftButton && isManuallyStoped) {
        modelRotation = true;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *mo)
{
    xMouseRot = xPrevRot + (1/M_PI*(mo->pos().y() - mPos.y()));
    yMouseRot = yPrevRot + (1/M_PI*(mo->pos().x() - mPos.x()));
}

void Widget::wheelEvent(QWheelEvent *wh)
{
    zWheel = zWheel + wh->angleDelta().y() / 9000.0f;
}

void Widget::LoadGLTextures()
{
    // Создание текстур
    glGenTextures(3, texture);

    // Загрузка картинки
    QImage texture1;
    texture1.load(":/files/bricks.jpg");
    initTexture(0, texture1); // инициализация и настройки для текстуры

    texture1.load(":/files/background.jpg");
    initTexture(1, texture1);

    texture1.load(":/files/background.jpg");
    initTexture(2, texture1);
}


void Widget::keyPressEvent(QKeyEvent *event) {
    if (event->key()==Qt::Key_F) {
        qDebug() << "F";
        ++texture_count%=3;
    }
    if (event->key()==Qt::Key_S) {
        if (paintTimer->isActive()) paintTimer->stop();
        else paintTimer->start();
    }
}

void Widget::initLight()
{
    GLfloat light_ambient[] = { 0, 0, 0, 0.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 2.0, 1.0 };

    /* устанавливаем параметры источника света */
    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    /* включаем освещение и источник света */
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

GLuint Widget::DrawBackground()
{
    GLuint num = glGenLists(1);
        glNewList(num,GL_COMPILE);

        glBegin(GL_QUADS);
        glNormal3f( 0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -6.0f,  -2.0f);	// Низ лево
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 6.0f, -6.0f,  -2.0f);	// Низ право
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 6.0f,  6.0f,  -2.0f);	// Верх право
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f,  6.0f,  -2.0f);	// Верх лево

        glEnd();

        glEndList();
        return num;

}

void Widget::initializeGL()
{
    glEnable(GL_MULTISAMPLE); // сглаживание MSAA вкл
    LoadGLTextures();			// Загрузка текстур
    glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры
    glClearColor(1,1,1,1); // заливаем белым цветом
    glClearDepth(1.0); // Разрешить очистку буфера глубины
    glEnable(GL_DEPTH_TEST); // Разрешить тест глубины
    glDepthFunc(GL_LESS); // Тип теста глубины
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Улучшение в вычислении перспективы
    initLight(); // включаем свет
    model = objloader::Instance().load(":/files/monkey2.obj");
//    torus = objloader::Instance().load(":/files/torus.obj");
    torus = DrawBackground();

}

void Widget::resizeGL(int nWidth, int nHeight)
{
    // установка точки обзора
    glViewport(0, 0, nWidth, nHeight);
    qreal aspectratio = qreal(nWidth) / qreal(nHeight);

    // инициализация матрицы проекций
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // сброс матрицы проекции
    gluPerspective( 90.0, aspectratio, 0.1, 100.0 );

    // инициализация матрицы вида модели
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // сброс матрицы вида модели
}

void Widget::paintGL() // рисование
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана и буфера глубины
    glLoadIdentity();           // сбросить текущую матрицу
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTranslatef(0,0,-2.5);
//    glDeleteLists(torus,1);
//    torus = objloader::Instance().draw(angle/100);
    glCallList(torus);
    glPushMatrix();
    glTranslatef(0,0,0.1f);
    glRotatef(angle,0.0f,1.0f,0.0f);
    if (modelRotation){
        angle += 0.4f;
    }
    if (!resetMatrix)
    {
        glPopMatrix();
        resetMatrix = true;
    }
    glRotatef(xMouseRot, 1.0f, 0.0f, 0.0f); // кручение по вращении мышкой Х
    glRotatef(yMouseRot, 0.0f , 1.0f, 0.0f); // кручение по вращении мышкой Y
//    glTranslatef(0, 0, zWheel);
    glBindTexture(GL_TEXTURE_2D, texture[texture_count]);
    glScaled(zWheel, zWheel, zWheel);
    glCallList(model);



//    angle += 0.4f;
}




