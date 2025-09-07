Port of a tiny TTS program SAM for ATmega microcontrollers
===

Software Automatic Mouth - Tiny Speech Synthesizer

С информацией по исходному коду SAM можно ознакомиться в исходном репозитории [s-macke/SAM](https://github.com/s-macke/SAM).

Этот репозиторий также использует фиксы от [RaafatTurki](https://github.com/s-macke/SAM/pull/14).

===

Проект [`handheld-sam`](https://github.com/vzalygin/handheld-sam) (`SAM` на ладони) -- система озвучивания текста (`TTS`) для схем под управлением МК компании `ATmega` на основе оригинальной программы `SAM`, созданной для персонального компьютера `Commodore C64` компанией `Don't Ask Software` в 1982 году.

Благодаря весьма скромным размерам (требования по размерам областей памяти: 13Кб кода, 8Кб статических данных и 43Кб динамических данных) запуск синтезатора возможен даже на маленьких микроконтроллерах.

Программа требует наличие 64Кб внешней памяти (в ней размещаются динамические данные).

Для сборки:

```bash
make sam.avr
```
