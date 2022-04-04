#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "calculate.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void BtnPressed();
private:
    Ui::MainWindow *ui;
    Calculate *co;

    using o_pair = std::pair<std::string, Calculate::operations>;
    std::vector<o_pair> mnemonics;



};
#endif // MAINWINDOW_H
