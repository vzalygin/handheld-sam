// #include <avr/io.h>
// #include <avr/interrupt.h>

#include <inttypes.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "uart.h"
#include "sam.h"
#include "help.h"

extern int debug;

// // ������������ ���� �������� �������
// // ������������ ���� C
// // ��������� ������� ������ (�������� XMEM)
// void init_xmem() {
//    XMCRA = 0;
//    XMCRB = 0;
//    MCUCR = (1<<SRE);
// }

// void init_uart() {
//    UBRR0L = 51; // 9600 ��� �� 8 ���
//    UCSR0B = (1<<TXEN) | (1<<RXEN);
//    UCSR0C = (3<<UCSZ00);

//    stdout = &uart_stdout;
//    stdin = &uart_stdin;
// }

// void init_io() {
//    DDRB = 0b11111111;     // ��������� PA ��� �����   
//    PORTB = 0b10101010;
// }

void say(char * input, int phonetic) {
   strncat(input, " ", 255);
   int i;
   for(i=0; input[i] != 0; i++) input[i] = toupper((int)input[i]);
   if (debug) {
      if (phonetic) {
	 printf("phonetic input: %s\n", input);
      } else {
	 printf("text input: %s\n", input);
      }
   }

   if (!phonetic) {
      strncat(input, "[", 255);
      if (!TextToPhonemes((unsigned char *)input)) {
	 return;
      }
      if (debug) {
	 printf("phonetic input: %s\n", input);
      }
   } else {
      strncat(input, "\x9b", 255);
   }

   SetInput(input);
   if (!SAMMain()) {
      print_usage();
   }
}

int main() {
   // init_xmem();
   // init_uart();
   // init_io();
   char input[256];
   int i;
   int phonetic = 0;
   unsigned char number;

   for(i=0; i<=255; ++i) input[i] = 0;
   debug = 1;

   printf("READY\n");

   while(1) {
      printf("> ");
      scanf("%255s", input);
      if (input[0] != '-') {
	 say(input, phonetic);
      } else if (strcmp(input, "-help") == 0) {
	 print_usage();
      } else if (strcmp(input, "-debug") == 0) {
	 debug = 1;
	 printf("debug enabled\n");
      } else if (strcmp(input, "-pitch") == 0) {
	 scanf("%hhu", &number);
	 SetPitch(number);
	 printf("set pitch %hhu\n", number);
      } else if (strcmp(input, "-speed") == 0) {
	 scanf("%hhu", &number);
	 SetSpeed(number);
	 printf("set speed %hhu\n", number);
      } else {
	 printf("unknown command %s\n", input);
      }
   }

   return 0;
}
