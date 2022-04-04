#include "mainwindow.h"

#include <QApplication>

#include <boost/version.hpp>
#include <iostream>

int main(int argc, char *argv[])
{

    std::cout << "Boost version: " << BOOST_VERSION / 100000
                << "." << BOOST_VERSION / 100 % 1000 << "."
                << BOOST_VERSION % 100 << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
