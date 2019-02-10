#include "glwidget.hpp"
#include <vector>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.75f, 1.0f, 0.75f, 1.0f);
    f->glEnable(GL_BLEND);
    f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    f->glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    vertices =
    {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    VizPointCloud::init(f);
    pcd = std::make_unique<VizPointCloud>(f);
    pcd->set_positions(f, vertices);
}

void GLWidget::resizeGL(int w, int h)
{
    (void)w;
    (void)h;
}

//
void GLWidget::paintGL()
{
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);


    pcd->draw(f);
}
