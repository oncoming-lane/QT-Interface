#include <iostream>
#include <string>
#include <vector>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>

#include "EthListener.h"
#include "mainwindow.h"

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        QPushButton *button = new QPushButton("Начать прослушивание", this);
        label = new QLabel(this);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(button);
        layout->addWidget(label);

        connect(button, &QPushButton::clicked, this, &MyWidget::onStartListening);

        listener = new EthListener(this);
        connect(listener, &EthListener::dataReceived, this, &MyWidget::onDataReceived);
    }

private slots:
    void onStartListening()
    {
        listener->start();
    }

    void onDataReceived(const QString &data)
    {
        label->setText("Получены данные: " + data);
    }

private:
    QLabel *label;
    EthListener *listener;
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
