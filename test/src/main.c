#include "main.h"

int main(void) {
    // Настроить PA0 как выход
    DDRA |= (1 << PA0);

    while (1) {
        _delay_ms(1000);
        // Включить светодиод (логическая 1)
        PORTA ^= (1 << PA0);
    }
}
