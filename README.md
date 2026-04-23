# ATmega Xplained Mini / ATmega328P — Embedded Demo Projects

This repository contains small, focused demo projects for the ATmega328P (ATmega Xplained Mini style) microcontroller. Each demo is intended to illustrate a single peripheral or feature (ADC, PWM, EEPROM, USART, keypad handling, interrupts, etc.) and is kept intentionally small for learning and reuse.

## Repository layout

Top-level folders contain self-contained example projects. Each project follows a simple pattern: a `src/` folder with C source files and minimal helper code.

- `adc-led-control/` — read ADC values and control an LED (brightness or state) from analog input
  - `src/led_adc.c`, `src/led.c`, `src/led_interrupt.c`
- `eeprom-state-persistence/` — save and restore simple runtime state to EEPROM
  - `src/eeprom.c`
- `keypad-musical-keyboard/` — scan a keypad and map keys to musical notes (simple keyboard demo)
  - `src/music.c`
- `pwm-brightness-control/` — demonstrate PWM configuration for LED brightness control
  - `src/pwm.c`
- `usart-communication/` — keypad integration + USART transmit/receive examples with interrupts
  - `src/keypad.c`, `src/usart.c`, `src/usart_interrupt.c`

