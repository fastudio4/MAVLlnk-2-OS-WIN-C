#include "serial.h"
#include <stdio.h>
#include <windows.h>

static HANDLE localSerial = NULL;

HANDLE serialInit(const char *portName) {
    char fullPortName[32];
    sprintf_s(fullPortName, sizeof(fullPortName), "\\\\.\\%s", portName);
// Відкриваємо COM
    HANDLE hSerial = CreateFile(
        fullPortName,                // ім'я порту
        GENERIC_READ | GENERIC_WRITE, // доступ
        0,                            // без спільного доступу
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );
    if (hSerial == INVALID_HANDLE_VALUE) {
      printf("Opening error COM Port (code %lu)\n", GetLastError());
      return NULL;
    }
// Налаштовуємо параметри порту
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Failed to get port status\n");
        CloseHandle(hSerial);
        return NULL;
    }
    dcbSerialParams.BaudRate = CBR_57600;   // швидкість
    dcbSerialParams.ByteSize = 8;          // 8 біт
    dcbSerialParams.StopBits = ONESTOPBIT; // 1 стоп-біт
    dcbSerialParams.Parity   = NOPARITY;   // без парності
    dcbSerialParams.fOutxCtsFlow = FALSE;   // без CTS
    dcbSerialParams.fOutxDsrFlow = FALSE;   // без DSR
    dcbSerialParams.fOutX = FALSE;          // без XON/XOFF
    dcbSerialParams.fInX  = FALSE;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Failed to set port parameters\n");
        CloseHandle(hSerial);
        return NULL;
    }
// Таймаути
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Failed to set timeouts\n");
        CloseHandle(hSerial);
        return NULL;
    }
    localSerial = hSerial;
    return hSerial;
}

BOOL serialWrite(const uint8_t* buf, uint16_t len) {
    DWORD bytesWritten;
    if (WriteFile(localSerial, buf, len, &bytesWritten, NULL)) {
        return (bytesWritten == len);
    }
    return FALSE;
}

void serialClose(HANDLE hSerial) {
  CloseHandle(hSerial);
}