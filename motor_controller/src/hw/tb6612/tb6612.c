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
#define MOTOR3_PWM_PIN                  3
/** Motor left dir 1 pin number - PA04. */
#define MOTOR3_CH1_PIN                  4
/** Motor left dir 2 pin number - PA05. */
#define MOTOR3_CH2_PIN                  5

/** Motor right PWM pin number - PA02. */
#define MOTOR4_PWM_PIN                  2
/** Motor right dir 1 pin number - PA06. */
#define MOTOR4_CH1_PIN                  6
/** Motor right dir 2 pin number - PA07. */
#define MOTOR4_CH2_PIN                  7

/** Offset of bitfield CMS MODE in TIM_CR1 register. */
#define TIM_CR1_CMS_MODE_CA3_BIT        5
/** Offset of bitwield OC1M in TIM_CCMR1 register. */
#define TIM_CCMR1_OC1M_BIT              4
/** Offset of bitwield OC2M in TIM_CCMR1 register. */
#define TIM_CCMR1_OC2M_BIT              12
/** Offset of bitwield OC3M in TIM_CCMR2 register. */
#define TIM_CCMR2_OC3M_BIT              4
/** Offset of bitwield OC4M in TIM_CCMR2 register. */
#define TIM_CCMR2_OC4M_BIT              12

static void gpio_init(void);
static void timer_init(void);

void tb6612_init(void)
{
    gpio_init();
    timer_init();
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

static void timer_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->CR1 = (3 << TIM_CR1_CMS_MODE_CA3_BIT);    /* Center aligned mode 3 */
    TIM2->CCMR1 = (6 << TIM_CCMR1_OC1M_BIT) |       /* Channel 1 PWM mode 1 */
            (6 << TIM_CCMR1_OC2M_BIT);              /* Channel 2 PWM mode 1 */
    TIM2->CCMR2 = (6 << TIM_CCMR2_OC3M_BIT) |       /* Channel 3 PWM mode 1 */
            (6 << TIM_CCMR2_OC4M_BIT);              /* Channel 4 PWM mode 1 */
    TIM2->CCER = TIM_CCER_CC1E
            | TIM_CCER_CC2E
            | TIM_CCER_CC3E
            | TIM_CCER_CC4E;

    /* Single timer tick is 0.1us, full cycle is 100us */
    TIM2->PSC = APB1_CLOCK_FREQ / 10000000 - 1;
    TIM2->ARR = 1000;

    /* Set initial duty cycle */
    TIM2->CCR1 = 500 - 1;
    TIM2->CCR2 = 250 - 1;
    TIM2->CCR3 = 750 - 1;
    TIM2->CCR4 = 1000 - 1;

    /* Enable timer */
    TIM2->CR1 |= TIM_CR1_CEN;
}
