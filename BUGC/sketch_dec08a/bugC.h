#ifndef __BUG_C_H
#define __BUG_C_H

#include "Arduino.h"

#define BUGC_ADDR 0x38

#define FRONT_LEFT  0
#define FRONT_RIGHT 1
#define REAR_LEFT   2
#define REAR_RIGHT  3

class BUGC {
   public:
    void Init();
    void BugCSetSpeed(uint8_t pos, int8_t speed);
    void BugCSetAllSpeed(int8_t speed_0, int8_t speed_1, int8_t speed_2, int8_t speed_3);
    void BugCSetColor(uint32_t color_left, uint32_t color_right);

   private:
    void Write1Byte(uint8_t address, uint8_t Register_address, uint8_t data);
    void Write2Byte(uint8_t address, uint8_t Register_address, uint16_t data);
    void WriteBytes(uint8_t address, uint8_t Register_address, uint8_t* data, size_t size);
    uint8_t ReadBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t* dest);
};

#endif
