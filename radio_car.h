#include <Arduino.h>

typedef int16_t data_t;
typedef uint8_t pin_t;
typedef uint8_t motor_dir_t;
typedef uint8_t action_t;
typedef String action_key_t;

typedef struct {
    action_t action;
    data_t data;
} command_t;
