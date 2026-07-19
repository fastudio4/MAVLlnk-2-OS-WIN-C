#include <stdio.h>
#include <stdint.h>
#include "serial_thread.h"
// #include "ardupilotmega/mavlink.h"

void myHandler(const uint8_t *data, size_t len) {
    printf("Read %lu bytes: ", len);
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main()
{
    if (startSerialThread("COM11", myHandler)) {
        getchar(); // чекаємо натискання клавіші
    }
  return 0;
}
