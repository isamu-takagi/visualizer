#ifndef VIZPOINTCLOUD_HPP
#define VIZPOINTCLOUD_HPP

#include <QOpenGLFunctions>

class VizPointCloud
{
    public:

        static void init(QOpenGLFunctions* f);

        VizPointCloud(QOpenGLFunctions* f);
        void draw(QOpenGLFunctions *f);
        void set_positions(QOpenGLFunctions* f, std::vector<GLfloat> positions);

    private:

        static GLint program;
        static GLint location_vertex;
        static GLint location_color;

        GLuint vbo;
        int size;

};

#endif // VIZPOINTCLOUD_HPP
