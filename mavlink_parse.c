#include "mavlink_parse.h"
#include <stdio.h>
// #include "common/mavlink_msg_command_long.h"
#include "ardupilotmega/mavlink.h"
#include "serial.h"
/**
 * Запитує конкретне повідомлення з певним інтервалом
 * @param msg_id ID повідомлення (наприклад, MAVLINK_MSG_ID_VFR_HUD)
 * @param interval_us Інтервал у мікросекундах (1000000us = 1Hz)
 */

void request_mavlink_message(uint16_t msg_id, int32_t interval_us) {
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];  // Використовуємо макс. довжину
    // Формуємо команду MAV_CMD_SET_MESSAGE_INTERVAL
    mavlink_msg_command_long_pack(
            1, 1,               // 1, 2. System ID та Component ID твого ПК
            &msg,               // 3. Вказівник на структуру (ЦЬОГО НЕ ВИСТАЧАЛО)
            1, 1,               // 4, 5. Target System та Component (Ardupilot)
            MAV_CMD_SET_MESSAGE_INTERVAL, // 6. Команда
            0,                  // 7. Confirmation (підтвердження)
            (float)msg_id,      // 8. Param 1: ID повідомлення, яке хочемо
            (float)interval_us, // 9. Param 2: Інтервал у мікросекундах
            0, 0, 0, 0, 0       // 10, 11, 12, 13, 14. Параметри 3-7 (не використовуються)
        );
    // Перетворюємо структуру повідомлення у буфер байтів
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    // Відправляємо через serialWrite
    if (serialWrite(buf, len)) {
        printf("Request for msg %d sent successfully.\n", msg_id);
    } else {
        printf("Failed to send request for msg %d.\n", msg_id);
    }
}

void processMavlinkPacket(mavlink_message_t* msg) {
    static BOOL data_requested = FALSE;

    switch (msg->msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:
            // Якщо це перший Heartbeat, запитуємо телеметрію
            if (!data_requested) {
                // Запитуємо VFR_HUD (швидкість, висота) 2 рази на секунду (500мс)
                request_mavlink_message(MAVLINK_MSG_ID_VFR_HUD, 500000);

                // Запитуємо ATTITUDE (крени) 5 разів на секунду (200мс)
                request_mavlink_message(MAVLINK_MSG_ID_ATTITUDE, 200000);

                data_requested = TRUE;
            }
            break;

        case MAVLINK_MSG_ID_VFR_HUD:
            // Тут вже будеш обробляти отримані дані швидкості
            break;
    }
}