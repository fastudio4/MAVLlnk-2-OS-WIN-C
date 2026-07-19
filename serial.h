#ifndef SERIAL_H
#define SERIAL_H
#include <windows.h>
HANDLE serialInit(const char *portName);
int serialWrite(HANDLE hSerial, const char *msg);
int serialRead(HANDLE hSerial, char *buffer, int bufSize);
void serialClose(HANDLE hSerial);
#endif // SERIAL_H
