#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <string>
#include <QApplication>
#include "UI/mainwindow.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <string>
#include <QApplication>
#include "UI/mainwindow.h"

using namespace std;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();
    return 0;
}