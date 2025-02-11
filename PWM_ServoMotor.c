#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

/*
    freq_PWM = 50Hz
    wrap = 20000 
    freq_clk_sys = 125 * 10^6 Hz
    pwm_clk_div = freq_clk_sys / freq_PWM * (wrap + 1)
*/

#define led_pin 12
#define servo_pin 22
#define pwm_wrap 20000 // Periodo de 20ms (50hz) para o servomotor 
#define pwm_clk_div 125 

// Define o duty cycle dos ângulos 0°, 90° e 180°
#define dutyCycle_0 0.025
#define dutyCycle_90 0.0735
#define dutyCycle_180 0.12 

// Define o incremente/decremento do level de PWM
#define step 5

// Define o level de PWM para o ângulos 0°, 90° e 180°
const uint16_t level_0 = (dutyCycle_0 * pwm_wrap); 
const uint16_t level_90 = (dutyCycle_90 * pwm_wrap);
const uint16_t level_180 = (dutyCycle_180 * pwm_wrap);

// Define um estado do movimento 
volatile bool estado = true;

// Declara as funções utilizadas 
void inicializar_pwm(uint gpio);
void ajustar_angulo(uint gpio, uint angulo);

int main()
{
    stdio_init_all();

    inicializar_pwm(servo_pin); // Chama a função para inicializar PWM do servomotor
    inicializar_pwm(led_pin);   // Chama a função para inicializar PWM do LED

    // Ajusta movimento do servomotor e intensidade do LED  
    ajustar_angulo(servo_pin, 180); 
    ajustar_angulo(led_pin, 180);
    printf("Ângulo = 180°\n");
    sleep_ms(5000); // Delay de 5s

    ajustar_angulo(servo_pin, 90);
    ajustar_angulo(led_pin, 90);
    printf("Ângulo = 90°\n");
    sleep_ms(5000); // Delay de 5s

    ajustar_angulo(servo_pin, 0);
    ajustar_angulo(led_pin, 0);
    printf("Ângulo = 0°\n");
    sleep_ms(5000); // Delay de 5s
        
    while (true) {
        static uint16_t level = level_0;

        // Aplica o level PWM atual para servo e LED
        pwm_set_gpio_level(servo_pin, level);
        pwm_set_gpio_level(led_pin, level);

        // Alterna entre aumento e redução do level PWM 
        if(estado){
            level += step; // Incrementa o level de PWM
            if(level >= level_180){
                estado = false; // Alterna o estado do movimento 
            }
        }else{
            level -= step;  // Decrementa o level de PWM
            if(level <= level_0){
                estado = true;  // Alterna o estado do movimento 
            }
        }
        sleep_ms(10); // Delay 10ms 
    }
}

/*
 *Inicializa os GPIOS e configura o PWM
 *Configura o divisor de clock, wrap e habilita o PWM
 */ 
void inicializar_pwm(uint gpio){
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, pwm_clk_div);
    pwm_config_set_wrap(&config, pwm_wrap);
    pwm_init(slice_num, &config, true);
}

// Ajusta o level de PWM no GPIO com base no ângulo especificado (0°, 90° ou 180°)
void ajustar_angulo(uint gpio, uint angulo){   
    switch (angulo){
    case 0:
        pwm_set_gpio_level(gpio, level_0);
        break;
    case 90:
        pwm_set_gpio_level(gpio, level_90);
        break;
    case 180:
        pwm_set_gpio_level(gpio, level_180);
        break;
    }
}
