#ifndef ETHLISTENER_H
#define ETHLISTENER_H

#include <QObject>
#include <QTcpSocket>

class EthListener : public QObject {
    Q_OBJECT

public:
    explicit EthListener(QObject *parent = nullptr);
    void startListening();

private:
    QTcpSocket *socket;

private slots:
    void onDataReceived();
};

#endif // ETHLISTENER_H
