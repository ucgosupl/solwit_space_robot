#include "platform_specific.h"

#include "hw/gpio_f4/gpio_f4.h"

#include "tb6612.h"

    /*
     * TIM2:
     * CH1: PA0
     * CH2: PA1
     * CH3: PA2
     * CH4: PA3
     *
     * MOTOR 1:
     * IN1: PC0
     * IN2: PC1
     *
     * MOTOR 2:
     * IN1: PC2
     * IN2: PC3
     *
     * MOTOR 3:
     * IN1: PA4
     * IN2: PA5
     *
     * MOTOR 4:
     * IN1: PA6
     * IN2: PA7
     */

/** Motor left PWM pin number - PA01. */
#define MOTOR1_PWM_PIN                  1
/** Motor left dir 1 pin number - PC00. */
#define MOTOR1_CH1_PIN                  0
/** Motor left dir 2 pin number - PC01. */
#define MOTOR1_CH2_PIN                  1

/** Motor right PWM pin number - PA00. */
#define MOTOR2_PWM_PIN                  0
/** Motor right dir 1 pin number - PC02. */
#define MOTOR2_CH1_PIN                  2
/** Motor right dir 2 pin number - PC03. */
#define MOTOR2_CH2_PIN                  3

/** Motor left PWM pin number - PA03. */
#define MOTOR3_PWM_PIN                  1
/** Motor left dir 1 pin number - PA04. */
#define MOTOR3_CH1_PIN                  4
/** Motor left dir 2 pin number - PA05. */
#define MOTOR3_CH2_PIN                  5

/** Motor right PWM pin number - PA02. */
#define MOTOR4_PWM_PIN                  0
/** Motor right dir 1 pin number - PA06. */
#define MOTOR4_CH1_PIN                  6
/** Motor right dir 2 pin number - PA07. */
#define MOTOR4_CH2_PIN                  7

static void gpio_init(void);

void tb6612_init(void)
{
    gpio_init();
}

void tb6612_test(void)
{
    GPIOC->BSRRL = (1 << MOTOR1_CH1_PIN);
    GPIOC->BSRRH = (1 << MOTOR1_CH1_PIN);

    GPIOC->BSRRL = (1 << MOTOR1_CH2_PIN);
    GPIOC->BSRRH = (1 << MOTOR1_CH2_PIN);

    GPIOC->BSRRL = (1 << MOTOR2_CH1_PIN);
    GPIOC->BSRRH = (1 << MOTOR2_CH1_PIN);

    GPIOC->BSRRL = (1 << MOTOR2_CH2_PIN);
    GPIOC->BSRRH = (1 << MOTOR2_CH2_PIN);

    GPIOA->BSRRL = (1 << MOTOR3_CH1_PIN);
    GPIOA->BSRRH = (1 << MOTOR3_CH1_PIN);

    GPIOA->BSRRL = (1 << MOTOR3_CH2_PIN);
    GPIOA->BSRRH = (1 << MOTOR3_CH2_PIN);

    GPIOA->BSRRL = (1 << MOTOR4_CH1_PIN);
    GPIOA->BSRRH = (1 << MOTOR4_CH1_PIN);

    GPIOA->BSRRL = (1 << MOTOR4_CH2_PIN);
    GPIOA->BSRRH = (1 << MOTOR4_CH2_PIN);
}

static void gpio_init(void)
{
    /*GPIO init*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

    /* PWM pins */
    gpio_mode_config(GPIOA, MOTOR1_PWM_PIN, GPIO_MODE_AF);
    gpio_mode_config(GPIOA, MOTOR2_PWM_PIN, GPIO_MODE_AF);
    gpio_mode_config(GPIOA, MOTOR3_PWM_PIN, GPIO_MODE_AF);
    gpio_mode_config(GPIOA, MOTOR4_PWM_PIN, GPIO_MODE_AF);
    gpio_af_config(GPIOA, MOTOR1_PWM_PIN, GPIO_AF_TIM2);
    gpio_af_config(GPIOA, MOTOR2_PWM_PIN, GPIO_AF_TIM2);
    gpio_af_config(GPIOA, MOTOR3_PWM_PIN, GPIO_AF_TIM2);
    gpio_af_config(GPIOA, MOTOR4_PWM_PIN, GPIO_AF_TIM2);

    /* GPIO pins */
    gpio_mode_config(GPIOC, MOTOR1_CH1_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, MOTOR1_CH2_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, MOTOR2_CH1_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, MOTOR2_CH2_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOA, MOTOR3_CH1_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOA, MOTOR3_CH2_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOA, MOTOR4_CH1_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOA, MOTOR4_CH2_PIN, GPIO_MODE_OUTPUT);

    /* Set all channel pins to 0 */
    GPIOA->BSRRH = (1 << MOTOR3_CH1_PIN)
            | (1 << MOTOR3_CH2_PIN)
            | (1 << MOTOR4_CH1_PIN)
            | (1 << MOTOR4_CH2_PIN);

    GPIOC->BSRRH = (1 << MOTOR1_CH1_PIN)
            | (1 << MOTOR1_CH2_PIN)
            | (1 << MOTOR2_CH1_PIN)
            | (1 << MOTOR2_CH2_PIN);
}
