#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

/*
    freq_PWM = 50Hz
    Wrap = 20000 
    freq_clk_sys = 125 * 10^6 Hz
    pwm_clk_div = freq_clk_sys / freq_PWM * (Wrap + 1)
*/

#define led_pin 13
#define servo_pin 22
#define pwm_wrap 20000 // Periodo de 20ms (50hz) para o servomotor 
#define pwm_clk_div 125

#define dutyCycle_180 0.12 
#define dutyCycle_90 0.0735
#define dutyCycle_0 0.025

#define level_0 (dutyCycle_0 * pwm_wrap) 
#define level_90 (dutyCycle_90 * pwm_wrap)
#define level_180 (dutyCycle_180 * pwm_wrap)
#define step 5

volatile bool estado = true;

void inicializar_pwm();
void ajustar_angulo(uint gpio, uint angulo);

int main()
{
    stdio_init_all();
    inicializar_pwm();

    ajustar_angulo(servo_pin, 180);
    ajustar_angulo(led_pin, 180);
    printf("Ângulo = 180°\n");
    sleep_ms(5000);
    ajustar_angulo(servo_pin, 90);
    ajustar_angulo(led_pin, 90);
    printf("Ângulo = 90°\n");
    sleep_ms(5000);
    ajustar_angulo(servo_pin, 0);
    ajustar_angulo(led_pin, 0);
    printf("Ângulo = 0°\n");
    sleep_ms(5000);
        
    while (true) {
        static uint16_t level = level_0;
        pwm_set_gpio_level(servo_pin, level);
        pwm_set_gpio_level(led_pin, level);

        if(estado){
            level += step;
            printf("incrementando: %i\n", level);
            if(level >= level_180){
                estado = false;
            }
        }else{
            level -= step;
            printf("decrementando: %i\n", level);
            if(level <= level_0){
                estado = true;
            }
        }
        sleep_ms(10);
    }
}

void inicializar_pwm(){
    gpio_set_function(led_pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(led_pin);
    pwm_set_wrap(slice, pwm_wrap);
    pwm_set_clkdiv(slice, pwm_clk_div);
    pwm_set_enabled(slice, true);

    gpio_set_function(servo_pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(servo_pin);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, pwm_clk_div);
    pwm_config_set_wrap(&config, pwm_wrap);
    pwm_init(slice_num, &config, true);
}


void ajustar_angulo(uint gpio, uint angulo){   
    if(!angulo){
        pwm_set_gpio_level(gpio, level_0);
    }else{
        if(angulo == 90){
            pwm_set_gpio_level(gpio, level_90);
        }else{
            if(angulo == 180){
                pwm_set_gpio_level(gpio, level_180);
            }
        }
    }
}
