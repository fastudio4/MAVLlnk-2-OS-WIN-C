#ifndef SERIAL_THREAD_H
#define SERIAL_THREAD_H

#include <stdint.h>

// Тип callback для отриманих даних
typedef void (*SerialCallback)(const uint8_t *data, size_t len);

// Запуск окремого потоку для читання
int startSerialThread(const char *portName, SerialCallback cb);

#endif // SERIAL_THREAD_H
