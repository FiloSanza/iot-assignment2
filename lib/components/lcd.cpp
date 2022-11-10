#include "lcd.h"

namespace Components {
    LCD::LCD() : LCD(DEFAULT_LCD_ROWS, DEFAULT_LCD_COLUMNS) {}
    LCD::LCD(uint32_t rows, uint32_t columns, uint32_t i2c_address = LCD_I2C_ADDRESS) 
        : lcd(i2c_address, columns, rows) {
        lcd.init();
        lcd.backlight();
    }

    void LCD::clear() {
        lcd.clear();
    }

    void LCD::displayMessage(LCDLine* message, uint32_t number_of_lines) {
        for (int i=0; i<number_of_lines; i++) {
            lcd.setCursor(message[i].column, message[i].row);
            lcd.print(message[i].text);
        }
    }
}