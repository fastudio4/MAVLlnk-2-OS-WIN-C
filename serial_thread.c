#include "serial_thread.h"
#include "serial.h"
#include <stdio.h>
#include <windows.h>

static SerialCallback onSerialData = NULL;
static HANDLE hSerial = NULL;

void registerSerialCallback(SerialCallback cb) {
    onSerialData = cb;
}

DWORD WINAPI serialThreadProc(LPVOID param) {
    uint8_t buf[256];
    DWORD bytesRead;

    while (1) {
        if (ReadFile(hSerial, buf, sizeof(buf), &bytesRead, NULL)) {
            if (bytesRead > 0 && onSerialData) {
                onSerialData(buf, bytesRead); // виклик callback
            }
        }
        Sleep(10);
    }
    return 0;
}

void startSerialThread(const char *portName) {
    hSerial = serialInit(portName);
    HANDLE hThread = CreateThread(NULL, 0, serialThreadProc, NULL, 0, NULL);
    if (hThread == NULL) {
        printf("Failed to create thread (code %lu)\n", GetLastError());
    } else {
        serialClose(hSerial);
        CloseHandle(hThread);
    }
}