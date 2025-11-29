#include "translator.h"

#include <string.h>

#include "memmanagment.h"

#define RULE_SIZE 3

const char RU_TABLE[][RULE_SIZE] PROGMEM = {
    "AE",  // À
    "B",   // Á
    "V",   // Â
    "G",   // Ã
    "D",   // Ä
    "A",   // Å
    "ZH",  // Æ
    "Z",   // Ç
    "EE",  // È
    "EI",  // É
    "K",   // Ê
    "L",   // Ë
    "M",   // Ì
    "N",   // Í
    "O",   // Î
    "P",   // Ï
    "R",   // Ð
    "S",   // Ñ
    "T",   // Ò
    "U",   // Ó
    "F",   // Ô
    "H",   // Õ
    "C",   // Ö
    "CH",  // ×
    "SH",  // Ø
    "SH",  // Ù
    "",    // Ú
    "E",   // Û
    "",    // Ü
    "A",   // Ý
    "U",   // Þ
    "IYA"  // ß
};

int is_russian_upper(char ch) { return (ch >= 'À' && ch <= 'ß') || ch == '¨'; }

int is_russian_lowest(char ch) { return (ch >= 'à' && ch <= 'ÿ') || ch == '¸'; }

int is_russian(char ch) {
    return is_russian_lowest(ch) || is_russian_upper(ch);
}

const char* get_translation(char ch) {
    if (is_russian_upper(ch)) {
        if (ch == '¨') ch = 'Å';
        return copy_pgm_str(RU_TABLE[ch - 'À']);
    } else {
        if (ch == '¸') ch = 'å';
        return copy_pgm_str(RU_TABLE[ch - 'à']);
    }
}

void translate(char* dst, char* src, int dstsize) {
    int srcsize = strlen(src);
    int size = 0;
    for (int i = 0; i < srcsize && size - RULE_SIZE <= dstsize; ++i) {
        char ch = src[i];
        if (is_russian(ch)) {
            const char* translated = get_translation(ch);
            strncat(dst, translated, RULE_SIZE);
            size += strlen(translated);
        } else {
            strncat(dst, &ch, 1);
            size++;
        }
    }
}
