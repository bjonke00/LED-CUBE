#include <QApplication>
#include "window.h"
#include "myglwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;
    window.show();
    window.setMinimumSize(1000,600);

    return app.exec();
}

