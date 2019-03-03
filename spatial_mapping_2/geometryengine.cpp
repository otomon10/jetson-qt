#include "geometryengine.h"

#include <QDebug>               // debug
#include <QOpenGLDebugLogger>   // debug

GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // debug
    QOpenGLContext *ctx = QOpenGLContext::currentContext();
    QOpenGLDebugLogger *logger = new QOpenGLDebugLogger();
    QObject::connect(logger, &QOpenGLDebugLogger::messageLogged, [=](const QOpenGLDebugMessage &debugMessage){
        qDebug() << debugMessage;
    });
    logger->initialize(); // initializes in the current context, i.e. ctx
    logger->startLogging();

    // Generate VBOs
    vertBuf.create();
    texBuf.create();
    indexBuf.create();

    numOfTriangles = 0;
}

GeometryEngine::~GeometryEngine()
{
    vertBuf.destroy();
    texBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    if(numOfTriangles == 0) return;

    vertBuf.bind();
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(float)*3);

    // Draw cube geometry using indices from VBO 2
    indexBuf.bind();
    glDrawElements(GL_TRIANGLES, numOfTriangles, GL_UNSIGNED_INT, 0);
}

void GeometryEngine::setGeometry(std::vector<sl::float3> *vertices, std::vector<sl::uint3> *triangles, std::vector<sl::float2> *uv, size_t numOfTriangles)
{
    // Transfer vertex data to VBO 0
    vertBuf.bind();
    vertBuf.allocate(vertices->data(), vertices->size() * sizeof(float) * 3);

    // Transfer texture uv data to VBO 1
    texBuf.bind();
    texBuf.allocate(uv->data(), uv->size() * sizeof(float) * 2);

    // Transfer index data to VBO 2
    indexBuf.bind();
    indexBuf.allocate(triangles->data(), triangles->size() * sizeof(unsigned int) * 3);
    this->numOfTriangles = indexBuf.size() / sizeof(unsigned int);

#if 0
    {
        float *p = static_cast<float*>(vertBuf.map(QOpenGLBuffer::ReadOnly));
        int size = 0;
        while(size < vertBuf.size() / (sizeof(float) * 3 ))
        {
            qDebug() << "vert(" << size << "): " << *p << "," << *(p+1) << "," << *(p+2);
            p+=3;
            size++;
        }
        vertBuf.unmap();
    }
#endif
#if 0
    {
        float *p = static_cast<float*>(texBuf.map(QOpenGLBuffer::ReadOnly));
        int size = 0;
        while(size < vertBuf.size() / (sizeof(float) * 2 ))
        {
            qDebug() << "uv(" << size << "): " << *p << "," << *(p+1);
            p+=2;
            size++;
        }
        texBuf.unmap();
    }
#endif
#if 0
    {
        unsigned int *p = static_cast<unsigned int*>(indexBuf.map(QOpenGLBuffer::ReadOnly));
        int size = 0;
        while(size < indexBuf.size() / (sizeof(unsigned int) * 3 ))
        {
            qDebug() << "inedx(" << size << "): " << *p << "," << *(p+1) << "," << *(p+2);
            p+=3;
            size++;
        }
        indexBuf.unmap();
    }
    qDebug() << "numOfTriangle:" << numOfTriangles;
#endif
}
