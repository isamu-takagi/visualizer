#include "widgets/mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    return application.exec();
}

// #include <QSurfaceFormat>
// QSurfaceFormat format;
// format.setVersion(3, 0);
// format.setProfile(QSurfaceFormat::CoreProfile);
// QSurfaceFormat::setDefaultFormat(format);
