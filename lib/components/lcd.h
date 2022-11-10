#ifndef __LCD_H_INCLUDED
#define __LCD_H_INCLUDED

#include <LiquidCrystal_I2C.h>

#include "lib.h"
#include "consts.h"

namespace Components {    
    class LCD {
    public:
        LCD();
        LCD(uint32_t rows, uint32_t columns, uint32_t i2c_address = LCD_I2C_ADDRESS);

        void clear();
        void displayMessage(LCDLine* message, uint32_t number_of_lines);
    private:
        LiquidCrystal_I2C lcd;
    };
}

#endif