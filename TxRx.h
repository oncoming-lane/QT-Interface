#ifndef TXRX_H
#define TXRX_H


#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <iostream>
#include <sys/ioctl.h>

char *find_ttyUSB_port();

int transmit(std::string message1);

void receive();

#endif // TXRX_H
