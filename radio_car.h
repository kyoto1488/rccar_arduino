#include <Arduino.h>

#define FORWARD 0x1
#define BACKWARD 0x2

#define PIN_MOTOR_DRIVER_ENA 8
#define PIN_MOTOR_DRIVER_IN1 8
#define PIN_MOTOR_DRIVER_IN2 4
#define PIN_MOTOR_DRIVER_ENB 5
#define PIN_MOTOR_DRIVER_IN3 7
#define PIN_MOTOR_DRIVER_IN4 8
#define PIN_SERVO_SIGNAL 11
#define PIN_LED 13

#define ROTATE_ENGINE 0x1
#define KEY_ROTATE_ENGINE "e"
#define ROTATE_SERVO 0x2
#define KEY_ROTATE_SERVO "s"
#define SWITCH_LIGHTING 0x3
#define KEY_SWITCH_LIGHTING "l"
#define DEBUG_MODE 0x4
#define KEY_DEBUG_MODE "d"

#define DEFAULT_STATE_LED LOW

typedef int16_t data_t;
typedef uint8_t action_t;

typedef struct {
    action_t action;
    data_t data;
} command_t;
