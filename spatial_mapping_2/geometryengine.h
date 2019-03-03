#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <sl/types.hpp>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();
    void drawCubeGeometry(QOpenGLShaderProgram *program);
    void setGeometry(std::vector<sl::float3> *vertices, std::vector<sl::uint3> *triangles, std::vector<sl::float2> *uv, size_t numOfTriangles);

private:
    QOpenGLBuffer vertBuf;
    QOpenGLBuffer texBuf;
    QOpenGLBuffer indexBuf;
    size_t numOfTriangles;
};

#endif // GEOMETRYENGINE_H
