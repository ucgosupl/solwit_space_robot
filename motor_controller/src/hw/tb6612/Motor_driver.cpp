#include "Motor_driver.hpp"

namespace hw
{
namespace tb6612
{

/** Motor left PWM pin number - PA01. */
constexpr uint32_t MOTOR1_PWM_PIN = 1;
/** Motor left dir 1 pin number - PC00. */
constexpr uint32_t MOTOR1_CH1_PIN = 0;
/** Motor left dir 2 pin number - PC01. */
constexpr uint32_t MOTOR1_CH2_PIN = 1;

#define MOTOR1_TIM_REG (reinterpret_cast<uint32_t>(&TIM2->CCR2))

/** Motor right PWM pin number - PA00. */
constexpr uint32_t MOTOR2_PWM_PIN = 0;
/** Motor right dir 1 pin number - PC02. */
constexpr uint32_t MOTOR2_CH1_PIN = 2;
/** Motor right dir 2 pin number - PC03. */
constexpr uint32_t MOTOR2_CH2_PIN = 3;

#define MOTOR2_TIM_REG (reinterpret_cast<uint32_t>(&TIM2->CCR1))

/** Motor left PWM pin number - PA03. */
constexpr uint32_t MOTOR3_PWM_PIN = 3;
/** Motor left dir 1 pin number - PA04. */
constexpr uint32_t MOTOR3_CH1_PIN = 4;
/** Motor left dir 2 pin number - PA05. */
constexpr uint32_t MOTOR3_CH2_PIN = 5;

#define MOTOR3_TIM_REG (reinterpret_cast<uint32_t>(&TIM2->CCR4))

/** Motor right PWM pin number - PA02. */
constexpr uint32_t MOTOR4_PWM_PIN = 2;
/** Motor right dir 1 pin number - PA06. */
constexpr uint32_t MOTOR4_CH1_PIN = 6;
/** Motor right dir 2 pin number - PA07. */
constexpr uint32_t MOTOR4_CH2_PIN = 7;

#define MOTOR4_TIM_REG (reinterpret_cast<uint32_t>(&TIM2->CCR3))

constexpr uint32_t STBY_MOTOR12_PIN = 4;
constexpr uint32_t STBY_MOTOR34_PIN = 5;

/** Offset of bitfield CMS MODE in TIM_CR1 register. */
constexpr uint32_t TIM_CR1_CMS_MODE_CA3_BIT = 5;
/** Offset of bitwield OC1M in TIM_CCMR1 register. */
constexpr uint32_t TIM_CCMR1_OC1M_BIT = 4;
/** Offset of bitwield OC2M in TIM_CCMR1 register. */
constexpr uint32_t TIM_CCMR1_OC2M_BIT = 12;
/** Offset of bitwield OC3M in TIM_CCMR2 register. */
constexpr uint32_t TIM_CCMR2_OC3M_BIT = 4;
/** Offset of bitwield OC4M in TIM_CCMR2 register. */
constexpr uint32_t TIM_CCMR2_OC4M_BIT = 12;

static constexpr uint32_t motor_id_get(motor_id_t id)
{
    return static_cast<uint32_t>(id);
}

Motor_driver::Motor_driver()
    : _motors {
        Motor{GPIOC,
            GPIOA,
            MOTOR1_CH1_PIN,
            MOTOR1_CH2_PIN,
            MOTOR1_PWM_PIN,
            MOTOR1_TIM_REG},
        Motor{GPIOC,
            GPIOA,
            MOTOR2_CH1_PIN,
            MOTOR2_CH2_PIN,
            MOTOR2_PWM_PIN,
            MOTOR2_TIM_REG},
        Motor{GPIOA,
            GPIOA,
            MOTOR3_CH1_PIN,
            MOTOR3_CH2_PIN,
            MOTOR3_PWM_PIN,
            MOTOR3_TIM_REG},
        Motor{GPIOA,
            GPIOA,
            MOTOR4_CH1_PIN,
            MOTOR4_CH2_PIN,
            MOTOR4_PWM_PIN,
            MOTOR4_TIM_REG}
    }
{
}

void Motor_driver::init()
{
    gpio_init();
    timer_init();

    for (Motor motor : _motors)
    {
        motor.init();
    }
}

void Motor_driver::motor_speed_set(motor_id_t motor_id, motor_speed_t speed)
{
    _motors.at(motor_id_get(motor_id)).speed_set(speed);
}

void Motor_driver::gpio_init(void)
{
    /*GPIO init*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

    /* STBY pin - must be always high */
    gpio_mode_config(GPIOC, STBY_MOTOR12_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, STBY_MOTOR34_PIN, GPIO_MODE_OUTPUT);
    GPIOC->BSRRL = (1 << STBY_MOTOR12_PIN);
    GPIOC->BSRRL = (1 << STBY_MOTOR34_PIN);
}

void Motor_driver::timer_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->CR1 = (3 << TIM_CR1_CMS_MODE_CA3_BIT);    // Center aligned mode 3
    TIM2->CCMR1 = (6 << TIM_CCMR1_OC1M_BIT) |       // Channel 1 PWM mode 1
            (6 << TIM_CCMR1_OC2M_BIT);              // Channel 2 PWM mode 1
    TIM2->CCMR2 = (6 << TIM_CCMR2_OC3M_BIT) |       // Channel 3 PWM mode 1
            (6 << TIM_CCMR2_OC4M_BIT);              // Channel 4 PWM mode 1
    TIM2->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;

    // Single timer tick is 0.1us, full cycle is 100us
    TIM2->PSC = APB1_CLOCK_FREQ / 10000000 - 1;
    TIM2->ARR = 1000;

    // Set initial duty cycle
    TIM2->CCR1 = 0;
    TIM2->CCR2 = 0;
    TIM2->CCR3 = 0;
    TIM2->CCR4 = 0;

    // Enable timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

}
}

