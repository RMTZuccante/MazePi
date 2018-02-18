#include <iostream>
#include "LCD.h"

int main() {
    LCD lcd("0x27");
    lcd.setBackLight(1);
    lcd.print("Ciao");
    return 0;
}
