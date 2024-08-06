#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>


#include <QPainter>

#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include "TxRxEth.h"


std::map <std::string, std::string > commands =
{                                           //push up long      push up short     push down
    {"Button1", "\x05\x83\x02\x57\x7A"},          //05 83 01 57 C1    05 83 02 57 7A    05 83 00 57 A8
    {"Button2", "\x05\x89\x02\x57\x24"},          //05 89 01 57 9F    05 89 02 57 24    05 89 00 57 F6
    {"Button3", "\x05\x84\x02\x57\xB5"},          //05 84 01 57 0E    05 84 02 57 B5    05 84 02 57 67
    {"Button4", "\x05\x8A\x02\x57\xB4"},          //05 8A 01 57 0F    05 8A 02 57 B4    05 8A 00 57 66
    {"Button5", "\x05\x85\x02\x57\xC5"},          //05 85 01 57 7E    05 85 02 57 C5    05 85 00 57 17

    {"lightButton", "\x05\x54\x01\x57\xA4"},          //05 54 01 57 A4                                            button_light
    {"homeButton", "\x05\x81\x01\x57\x21"},          //05 81 01 57 21                                            button_home
    {"powerButton", "\x05\x84\x02\x57\xB5"},                                                                    //button_power
    {"emergencyButton", "\x05\x94\x01\x57\xED"},         //05 94 01 57 ED                      05 94 00 57 84        button_emergency

    {"leftButton", "\x05\x04\x01\x57\xF5"},          //05 04 01 57 F5                                            button_arrow_left
    {"rightButton", "\x05\x04\xFF\x57\xCC"}           //05 04 FF 57 CC                                            button_arrow_right
};


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{
    ui->setupUi(this);






    // Подключение слота к сигналу clicked() каждой кнопки
    connect(ui->Button1, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);
    connect(ui->Button2, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);
    connect(ui->Button3, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);
    connect(ui->Button4, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);
    connect(ui->Button5, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);

    connect(ui->powerButton, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);
    connect(ui->homeButton, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);
    connect(ui->lightButton, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAnyButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender()); // Получение указателя на нажатую кнопку

    if(clickedButton)
    {
        QString buttonName = clickedButton->objectName(); // Получение названия кнопки

        // Преобразование QString в std::string для использования в словаре
        std::string buttonNameStd = buttonName.toStdString();

        // Поиск соответствующего значения в словаре
        auto it = commands.find(buttonNameStd);
        if (it != commands.end())
        {
            std::string commandValue = it->second;
            ui->textEdit->setText(QString("Нажата кнопка %1, значение из словаря: %2").arg(buttonName).arg(QString::fromStdString(commandValue)));
            //transmit_eth();

        }
        else
        {
            ui->textEdit->setText("Команда для кнопки не найдена");
        }
    }
}
