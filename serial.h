#ifndef SERIAL_H
#define SERIAL_H
#include <windows.h>
#include <stdint.h>
HANDLE serialInit(const char *portName);
BOOL serialWrite(const uint8_t* buf, uint16_t len);
void serialClose(HANDLE hSerial);
#endif // SERIAL_H
