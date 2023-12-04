#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app (argc, argv);

    Stopwatch stopwatch;
    stopwatch.setWindowTitle("Stopwatch");
    stopwatch.resize(700, 500);
    stopwatch.show();

    return app.exec();
}
