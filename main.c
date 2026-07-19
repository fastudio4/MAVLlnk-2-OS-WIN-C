#include <stdio.h>
#include <stdint.h>
#include "serial_thread.h"
#include "ardupilotmega/mavlink.h"

void myHandler(const uint8_t *data, size_t len) {
    printf("Read %lu bytes: ", len);
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}


/*
void myHandler(const uint8_t *data, size_t len) {
    mavlink_message_t msg;
    mavlink_status_t status;
    int parsedCount = 0;

    for (size_t i = 0; i < len; i++) {
        if (mavlink_parse_char(MAVLINK_COMM_0, data[i], &msg, &status)) {
            parsedCount++;

            switch (msg.msgid) {
                case MAVLINK_MSG_ID_HEARTBEAT: {
                    mavlink_heartbeat_t hb;
                    mavlink_msg_heartbeat_decode(&msg, &hb);
                    printf("HEARTBEAT: type=%d autopilot=%d base_mode=%d\n",
                           hb.type, hb.autopilot, hb.base_mode);
                } break;

                case MAVLINK_MSG_ID_ATTITUDE: {
                    mavlink_attitude_t att;
                    mavlink_msg_attitude_decode(&msg, &att);
                    printf("ATTITUDE: roll=%.2f pitch=%.2f yaw=%.2f\n",
                           att.roll, att.pitch, att.yaw);
                } break;

                default:
                    printf("Got MAVLink msgid=%d, payload len=%d\n",
                           msg.msgid, msg.len);
                    break;
            }
        }
    }

    // return parsedCount;
}
*/
int main()
{
    if (startSerialThread("COM11", myHandler)) {
        getchar(); // чекаємо натискання клавіші
    }
  return 0;
}
