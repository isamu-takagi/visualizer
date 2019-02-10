#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "shaders/vizpointcloud.hpp"

#include <QOpenGLWidget>
#include <memory>
#include <vector>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

    public:
        GLWidget(QWidget *parent = 0);
        ~GLWidget();

    protected:

        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;

    private:

        std::unique_ptr<VizPointCloud> pcd;
        std::vector<GLfloat> vertices;
};

#endif // GLWIDGET_H
