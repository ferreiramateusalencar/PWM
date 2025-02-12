#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_PIN 22
#define DIV 25
#define WRAP (uint16_t)100000

#define ANG_180 12000 // WRAP * 0,12 = 12000 para aproximadamente 180 graus
#define ANG_90 7350 // WRAP * 0,0735 = 7350 para aproximadamente 90 graus
#define ANG_0 2500 // WRAP * 0,025 = 2500 para aproximadamente 0 graus

#define STEP 5
int main() {
    stdio_init_all();
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    uint slice = pwm_gpio_to_slice_num(PWM_PIN);

    pwm_set_clkdiv(slice, DIV);
    pwm_set_wrap(slice, WRAP);

    pwm_set_enabled(slice, true);

    pwm_set_gpio_level(PWM_PIN, ANG_180);
    sleep_ms(5000);

    pwm_set_gpio_level(PWM_PIN, ANG_90);
    sleep_ms(5000);

    pwm_set_gpio_level(PWM_PIN, ANG_0);
    sleep_ms(5000);

    uint level = ANG_0;
    bool positive_direction = true;
    
    while (true) {
        if (positive_direction) {
            level += STEP;
        } else {
            level -= STEP;
        }

        pwm_set_gpio_level(PWM_PIN, level);

        if (level <= ANG_0) {
            positive_direction = true;
        }
        if (level >= ANG_180) {
            positive_direction = false;
        }

        sleep_ms(10);
    }
}
