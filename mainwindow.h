#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAnyButtonClicked();

    void on_lightButton_clicked();

private:
    enum ButtonId { Button1, Button2, Button3, Button4, Button5 };


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
