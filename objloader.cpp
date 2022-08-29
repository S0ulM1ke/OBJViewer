#include "objloader.h"

using std::vector;
using std::string;

GLuint objloader::load(const QString &filename)
{
    vector<string>().swap(coord);
    vector<QVector3D>().swap(vertex);
    vector<QVector2D>().swap(uvs);
    vector<QVector3D>().swap(normals);
    vector<face>().swap(faces);

    QFile in(filename);
    if(!in.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Не удалось открыть файл с моделью!";
    }

    char buf[256];

    while(!in.atEnd())
    {
        in.readLine(buf,256);
        objloader::coord.push_back(buf);
    }
    size_t N_coord = coord.size();
    for (size_t i = 0; i < N_coord; ++i)
    {
        if(coord[i][0] != '#')
        {
            if (coord[i][0] == 'v' && coord[i][1] == ' ') // если вершина
            {
                float tmpx,tmpy,tmpz;
                sscanf(coord[i].c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
                vertex.push_back(QVector3D(tmpx,tmpy,tmpz));
            } else if (coord[i][0] =='v' && coord[i][1]=='n') // если нормаль
            {
                float tmpx,tmpy,tmpz;
                sscanf(coord[i].c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
                normals.push_back(QVector3D(tmpx,tmpy,tmpz));
            } else if (coord[i][0] =='v' && coord[i][1]=='t') // если текстурная вершина
            {
                float tmpx,tmpy;
                sscanf(coord[i].c_str(),"vt %f %f",&tmpx,&tmpy);
                uvs.push_back(QVector2D(tmpx,tmpy));
            } else if(coord[i][0] == 'f')     // если грань
            {
                face::vertex v1, v2, v3;
                sscanf(coord[i].c_str(),"f %i/%i/%i %i/%i/%i %i/%i/%i", &v1.v_i, &v1.vt_i, &v1.vn_i, &v2.v_i, &v2.vt_i, &v2.vn_i, &v3.v_i, &v3.vt_i, &v3.vn_i);
                faces.push_back(face(v1,v2,v3));     // записываю грань в массив
            }
        }
    }
    GLuint num = draw();
    return num;

}

GLuint objloader::draw(GLfloat offset)
{

    GLuint num = glGenLists(1);
    glNewList(num,GL_COMPILE);
    size_t N_faces = faces.size();
    for(size_t i=0; i < N_faces; ++i)
    {
        face f = faces[i];

        glBegin(GL_TRIANGLES);

        QVector3D normal = normals[f.v[0].vn_i - 1];
        glNormal3f(normal.x(), normal.y(), normal.z());

        //glTexCoord2f(0.5f*(normal.x()+1), 0.5f*(normal.y()+1)); // построение текстурной вершины по вершине нормали, дает другое наложение текстуры на модель
        glTexCoord2f(uvs[f.v[0].vt_i - 1].x()+offset, uvs[f.v[0].vt_i - 1].y()+offset); glVertex3f(vertex[f.v[0].v_i - 1].x(),vertex[f.v[0].v_i - 1].y(),vertex[f.v[0].v_i - 1].z()); // читаем текстурную вершину из файла

        normal = normals[f.v[1].vn_i - 1];
        glNormal3f(normal.x(), normal.y(), normal.z());

        //glTexCoord2f(0.5f*(normal.x()+1), 0.5f*(normal.y()+1));
        glTexCoord2f(uvs[f.v[1].vt_i - 1].x()+offset, uvs[f.v[1].vt_i - 1].y()+offset); glVertex3f(vertex[f.v[1].v_i - 1].x(),vertex[f.v[1].v_i - 1].y(),vertex[f.v[1].v_i - 1].z());

        normal = normals[f.v[2].vn_i - 1];
        glNormal3f(normal.x(), normal.y(), normal.z());

        //glTexCoord2f(0.5f*(normal.x()+1), 0.5f*(normal.y()+1));
        glTexCoord2f(uvs[f.v[2].vt_i - 1].x()+offset, uvs[f.v[2].vt_i - 1].y()+offset); glVertex3f(vertex[f.v[2].v_i - 1].x(),vertex[f.v[2].v_i - 1].y(),vertex[f.v[2].v_i - 1].z());

        glEnd();
    }
    glEndList();
    return num;     // возвращаем номер дисплей листа
}
