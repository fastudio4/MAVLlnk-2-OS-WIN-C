#include "serial_thread.h"
#include "serial.h"
#include <stdio.h>
#include <windows.h>

static SerialCallback onSerialData = NULL;
static HANDLE hSerial = NULL;

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

int startSerialThread(const char *portName, SerialCallback cb) {
    onSerialData = cb;
    hSerial = serialInit(portName);
    if(hSerial == NULL) {
        return 0;
    }
    HANDLE hThread = CreateThread(NULL, 0, serialThreadProc, NULL, 0, NULL);
    if (hThread == NULL) {
        printf("Failed to create thread (code %lu)\n", GetLastError());
        return 0;
    } else {
        CloseHandle(hThread);
    }
    return 1;
}