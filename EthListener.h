#ifndef ETHLISTENER_H
#define ETHLISTENER_H

#include <QThread>
#include <QTcpSocket>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class EthListener : public QThread
{
    Q_OBJECT

public:
    EthListener(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() override
    {
        std::string result = receive_eth();
        emit dataReceived(QString::fromStdString(result));
    }

signals:
    void dataReceived(const QString &data);

private:
    std::string receive_eth()
    {
        int sockfd, newsockfd;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int n;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            std::cerr << "Error opening socket" << std::endl;
            std::exit(1);
        }

        int optval = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

        memset((char *)&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(12345); // Ваш порт

        if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cerr << "Error on binding" << std::endl;
            std::exit(1);
        }

        listen(sockfd, 5);
        clilen = sizeof(cli_addr);

        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
            std::cerr << "Error on accept" << std::endl;
            std::exit(1);
        }

        memset(buffer, 0, sizeof(buffer));
        time_t start_time = time(NULL);
        while ((time(NULL) - start_time) < 0.5) {
            n = read(newsockfd, buffer, sizeof(buffer) - 1);
            if (n < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    continue;
                else {
                    std::cerr << "Error reading from socket" << std::endl;
                    exit(1);
                }
            }
            if (n > 0)
                break;
        }

        std::string str(buffer, n);

        close(newsockfd);
        close(sockfd);

        return str;
    }
};

#endif // ETHLISTENER_H
