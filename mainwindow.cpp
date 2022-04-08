#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <vector>
#include <utility>
#include <stdexcept>

#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    co = new Calculate;

    mnemonics.reserve(20);

    auto objName = [](const QPushButton * b)->std::string{ return b->objectName().toStdString(); };

    auto registr_button = [&](const QPushButton * b, Calculate::operations o){
        connect(b, &QPushButton::clicked, this, &MainWindow::BtnPressed);
        mnemonics.emplace_back(objName(b), o);
    };

    registr_button(ui->b0, Calculate::operations::zero);

    registr_button(ui->b0, Calculate::operations::zero);
    registr_button(ui->b1, Calculate::operations::one);
    registr_button(ui->b2, Calculate::operations::two);
    registr_button(ui->b3, Calculate::operations::three);
    registr_button(ui->b4, Calculate::operations::four);
    registr_button(ui->b5, Calculate::operations::five);
    registr_button(ui->b6, Calculate::operations::six);
    registr_button(ui->b7, Calculate::operations::seven);
    registr_button(ui->b8, Calculate::operations::eight);
    registr_button(ui->b9, Calculate::operations::nine);

    registr_button(ui->bplus, Calculate::operations::plus);
    registr_button(ui->bminus, Calculate::operations::minus);
    registr_button(ui->bmul, Calculate::operations::multiplication);
    registr_button(ui->bdiv, Calculate::operations::division);
    registr_button(ui->bres, Calculate::operations::res);

    registr_button(ui->beval, Calculate::operations::eval);
    registr_button(ui->bbl, Calculate::operations::left_bracket);
    registr_button(ui->bbr, Calculate::operations::right_bracket);

    registr_button(ui->bclean_all, Calculate::operations::clear_all);
    registr_button(ui->b_backs, Calculate::operations::backspace);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete co;
}

void MainWindow::BtnPressed()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    assert(button != nullptr);

    auto ito = std::find_if(mnemonics.begin(), mnemonics.end(), [&button](const o_pair & xx){return button->objectName().toStdString() == xx.first;});

    if(ito != mnemonics.end())
        ui->lineEdit->setText(co->recive(ito->second).c_str());

}

