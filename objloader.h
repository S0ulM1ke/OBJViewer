// Загрузчик файлов формата obj
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Windows.h"
#include <GL/gl.h> // для типа GLuint
#include <string>
#include <vector>
#include <QVector2D>
#include <QVector3D>
#include <QFile>
#include <QDebug>

class objloader
{

    struct face // грань
    {
        struct vertex { // вершина
            GLuint v_i; // индекс вершины
            GLuint vt_i; // индекс текстурной вершины
            GLuint vn_i; // индекс вершины нормали
        };

        vertex v[3]; // три вершины у треугольника - полигона

        face(vertex v1,vertex v2,vertex v3) // полигон (грань)
        {
            v[0]=v1;
            v[1]=v2;
            v[2]=v3;
        }
    };

    std::vector<std::string> coord;
    std::vector<QVector3D> vertex;
    std::vector<QVector2D> uvs;
    std::vector<QVector3D> normals;
    std::vector<face> faces;

    objloader(){}
    objloader(const objloader &)  = delete;
    objloader(const objloader &&) = delete;
    objloader& operator=(const objloader &)  = delete;
    objloader& operator=(const objloader &&) = delete;
public:
    static objloader& Instance()
    {
        static objloader theSingleInstance;
        return theSingleInstance;
    }
    GLuint load(const QString &filename); // загрузка по названию файла
    GLuint draw(GLfloat offset = 0);

};

#endif // OBJLOADER_H





