#include "vizpointcloud.hpp"
#include <iostream>

const char* vshader_source =
R"(
    #version 300 es
    #undef mediump
    in mediump vec3 position;
    void main()
    {
        gl_PointSize = 5.0;
        gl_Position = vec4(position, 1);
    }
)";

const char* fshader_source =
R"(
    #version 300 es
    #undef mediump
    uniform mediump vec4 color;
    out mediump vec4 my_FlagColor;
    void main()
    {
        my_FlagColor = color;
    }
)";

QOpenGLShaderProgram VizPointCloud::program;
GLint VizPointCloud::location_vertex = -1;
GLint VizPointCloud::location_color  = -1;

void VizPointCloud::init(QOpenGLFunctions *f)
{
    if(!program.addShaderFromSourceCode(QOpenGLShader::Vertex, vshader_source))
    {
        std::cerr << program.log().toStdString() << std::endl;
    }

    if(!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fshader_source))
    {
        std::cerr << program.log().toStdString() << std::endl;
    }

    if(!program.link())
    {
        std::cerr << program.log().toStdString() << std::endl;
    }

    location_vertex = program.attributeLocation("position");
    location_color  = program.uniformLocation("color");

    printf("location_vertex: %d\n", location_vertex);
    printf("location_color : %d\n", location_color);
}

VizPointCloud::VizPointCloud(QOpenGLFunctions* f)
{
    vbo.create();
}

void VizPointCloud::draw(QOpenGLFunctions* f)
{
    printf("Draw: location=%d size=%d\n", location_vertex, size);
    program.bind();
    vbo.bind();
    program.setUniformValue(location_color, 1.0, 0.0, 0.0, 0.5);
    program.enableAttributeArray(location_vertex);
    program.setAttributeBuffer(location_vertex, GL_FLOAT, 0, 3, 0);
    f->glDrawArrays(GL_POINTS, 0, size);
    program.disableAttributeArray(location_vertex);
    vbo.release();
    program.release();
}

void VizPointCloud::set_positions(QOpenGLFunctions* f, std::vector<GLfloat> positions)
{
    size = positions.size() / 3;
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(positions.data(), positions.size() * sizeof(GLfloat));
}

