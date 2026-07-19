#ifndef SERIAL_THREAD_H
#define SERIAL_THREAD_H

#include <stdint.h>

// Тип callback для отриманих даних
typedef void (*SerialCallback)(const uint8_t *data, size_t len);
// Реєстрація callback
void registerSerialCallback(SerialCallback cb);
// Запуск окремого потоку для читання
void startSerialThread(const char *portName);

#endif // SERIAL_THREAD_H
