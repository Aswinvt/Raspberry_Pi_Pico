#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/timer.h"
#include "hardware/adc.h"

// Core 1 Main Code
void core1_func()
{
    bool flag;

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Secondary Core 1 Loop runs every 500ms
    while (1)
    {
        // POP the raw adc value from FIFO memory
        uint16_t raw = multicore_fifo_pop_blocking();
        // Temperature conversion
        const float conversion_factor = 3.3f / (1 << 12);
        float result = raw * conversion_factor;
        float temp = 27 - (result - 0.706) / 0.001721;


        // Set the Flag for warning light
        if (temp > 31.5)
            flag = true;
        else
            flag = false;

        printf("\r\nTemperature = %f C", temp);
        
        // Toggle the warning LED every 250ms if flag is set
        while (flag)
        {
            // POP the raw adc value from FIFO memory
            raw = multicore_fifo_pop_blocking();
            // Temperature conversion
            result = raw * conversion_factor;
            temp = 27 - (result - 0.706) / 0.001721;

            // Reset the Flag for warning light
            if (temp < 31.5)
                flag = false;
                
            printf("\r\nWarning! Temperature = %f C", temp);

            gpio_put(LED_PIN, 1);
            sleep_ms(250);
            gpio_put(LED_PIN, 0);
            sleep_ms(250);
        }
        sleep_ms(500);
    }
}

// Core 0 Main Code
int main(void)
{
    // Initialize the IO functions
    stdio_init_all();

    // Start the second core
    multicore_launch_core1(core1_func);

    // Configure ADC
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    // Primary Core 0 Loop runs every 100ms
    while (1)
    {
        // Read the raw ADC value
        uint16_t raw = adc_read();
        // PUSH the ADC value to FIFO memory
        multicore_fifo_push_blocking(raw);
        sleep_ms(100);
    }
}