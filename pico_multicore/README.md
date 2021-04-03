# Raspberry Pi Pico
## Experimenting with Raspberry Pi Pico Multicore
### Read temperature from internal temperature sensor of Pico

- Core0 will read the ADC and PUSH the raw ADC value to FIFO memory every 10ms.
- Core1 will POP the raw ADC value from FIFO memory and convert it into equivalent temperature value every 500ms.
- If temperature goes beyond a predefined threshold value a Warning LED will toggel every 250ms.
>
- tempcalc_fun() -  will convert the raw adc value to actual temperature value
- filter_pt1_fun() -  will filter the temperature reading

#### Raw temperature data vs filtered temperature data
![Alt Text](https://github.com/Aswinvt/Raspberry_Pi_Pico/blob/main/pico_multicore/temperaturesensorplot.JPG)