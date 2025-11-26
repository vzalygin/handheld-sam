#include <avr/io.h>
#include <util/delay.h>

#include <inttypes.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define F_CPU 8000000UL
#define BAUD  9600UL
#define UBRR1_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void usart1_init(void)
{
    UBRR1H = (uint8_t)(UBRR1_VALUE >> 8);
    UBRR1L = (uint8_t)(UBRR1_VALUE);

    UCSR1A = 0;                                   // U2X1 = 0 (обычный режим)
    UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);           // 8 бит, без чётности, 1 стоп
    UCSR1B = (1<<RXEN1) | (1<<TXEN1);             // включить RX и TX
}

uint8_t usart1_receive()
{
    // Ждём, пока придёт байт
    while (!(UCSR1A & (1 << RXC1)))
        ;
    return UDR1;
}

void usart1_transmit(uint8_t data)
{
    // Ждём, пока буфер передачи освободится
    while (!(UCSR1A & (1 << UDRE1)))
        ;
    UDR1 = data;
}

void print(char * str) {
    uint8_t l = strlen(str);
    for (int i = 0; i < l; i++) {
        usart1_transmit(str[i]);
    }
}

int main()
{
    usart1_init();

    for (;;)
    {
        // uint8_t b = usart1_receive();   // Приняли байт по USART1
        // PORTA ^= (1 << PA0);
        // _delay_ms(100);
        // usart1_transmit('U');             // Отправили его обратно — эхо
        print("hello world\r\n");
    }
}
