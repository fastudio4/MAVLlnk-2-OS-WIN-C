#ifndef MAVLINK_PARSE_H
#define MAVLINK_PARSE_H

#include <stdint.h>
#include "mavlink_types.h"

void request_mavlink_message(uint16_t msg_id, int32_t interval_us);
void processMavlinkPacket(mavlink_message_t* msg);
#endif // MAVLINK_PARSE_H
