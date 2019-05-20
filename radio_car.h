#include <Arduino.h>

typedef double data_t;
typedef uint8_t action_t;
typedef String action_str_t;
typedef uint8_t pin_t;
typedef uint8_t motor_dir_t;

typedef struct {
    action_t action;
    data_t data;
} command_t;
