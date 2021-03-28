# Raspberry Pi Pico
## Experimenting with Raspberry Pi Pico Multicore

> Core0 will read the ADC and PUSH the raw ADC value to memory every 100ms.
> Core1 will POP the raw ADC value from memory and convert it into equivalent temperature value every 500ms.
> If temperature goes beyond a predefined threshold value a Warning LED will toggel every 250ms.