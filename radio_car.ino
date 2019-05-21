#include <Arduino.h>
#include <Servo.h>
#include "radio_car.h"

Servo steeringWheel;

const pin_t PIN_MOTOR_DRIVER_ENA = 3;
const pin_t PIN_MOTOR_DRIVER_IN1 = 2;
const pin_t PIN_MOTOR_DRIVER_IN2 = 4;
const pin_t PIN_MOTOR_DRIVER_ENB = 5;
const pin_t PIN_MOTOR_DRIVER_IN3 = 7;
const pin_t PIN_MOTOR_DRIVER_IN4 = 8;
const pin_t PIN_SERVO_SIGNAL = 11;
const pin_t PIN_LED = 13;

const action_t ROTATE_ENGINE = 0x1;
const action_str_t ACTION_ROTATE_ENGINE = "engine";
const action_t ROTATE_SERVO = 0x2;
const action_str_t ACTION_ROTATE_SERVO = "servo";
const action_t SWITCH_LIGHTING = 0x3;
const action_str_t ACTION_SWITCH_LIGHTING = "lighting";
const action_t UNKNOWN = 0x4;

const motor_dir_t DIRECTION_FORWARD = 0x1;
const motor_dir_t DIRECTION_BACKWARD = 0x2;

bool DEFAULT_STATE_LED = true;

/**
 * Функция устанавливает направление моторов
 * за счет переключения полярности пинов
 *
 * @param direction
 */
void setMotorDirection(motor_dir_t direction) {
    switch (direction) {
        case DIRECTION_FORWARD:
            digitalWrite(PIN_MOTOR_DRIVER_IN1, HIGH);
            digitalWrite(PIN_MOTOR_DRIVER_IN2, LOW);
            digitalWrite(PIN_MOTOR_DRIVER_IN3, HIGH);
            digitalWrite(PIN_MOTOR_DRIVER_IN4, LOW);
            break;
        case DIRECTION_BACKWARD:
            digitalWrite(PIN_MOTOR_DRIVER_IN1, LOW);
            digitalWrite(PIN_MOTOR_DRIVER_IN2, HIGH);
            digitalWrite(PIN_MOTOR_DRIVER_IN3, LOW);
            digitalWrite(PIN_MOTOR_DRIVER_IN4, HIGH);
            break;
    }
}

/**
 * Функция подает ШИМ питание на моторы
 *
 * @param signal_ena
 * @param signal_enb
 */
void setMotorSignals(uint8_t signal_ena, uint8_t signal_enb) {
    analogWrite(PIN_MOTOR_DRIVER_ENA, signal_ena);
    analogWrite(PIN_MOTOR_DRIVER_ENB, signal_enb);
}

/**
 * Функция устанавливает угол на серво приводе
 *
 * @param angle
 */
void setSteeringWheelAngle(uint8_t angle) {
    steeringWheel.write(angle);
}

/**
 * Функция устанавливает сигнальный пин для серво
 *
 * @param pin
 */
void setSteeringWheelPin(pin_t pin) {
    steeringWheel.attach(pin);
}

/**
 * Функция парсит данные из переданного ключа
 * @example $data = cmd: action; data: 1.222; -> f(data, "cmd") -> "action"
 *
 * @param data
 * @param key
 * @return
 */
 String getSubstringKeyValue(String data, String key) {
    int index = data.indexOf(key);

    if (index >= 0) {
        int start = data.indexOf(':', (unsigned int)index) + 1;
        int end = data.indexOf(';', (unsigned int)start);
        String substring = data.substring((unsigned int)start,(unsigned int)end);
        substring.trim();
        return substring;
    }

    return "";
}

/**
 * Функция возвращает действие для команды
 *
 * @param data
 * @return
 */
action_t createCommandAction(String data) {
    if (data.length() > 0) {
        if (data.equals(ACTION_ROTATE_ENGINE)) {
            return ROTATE_ENGINE;
        } else if (data.equals(ACTION_ROTATE_SERVO)) {
            return ROTATE_SERVO;
        } else if (data.equals(ACTION_SWITCH_LIGHTING)) {
            return SWITCH_LIGHTING;
        }
    }

    return UNKNOWN;
}

/**
 * Функция возвращает данные для команды
 *
 * @param data
 * @return
 */
data_t createCommandData(String data) {
    if (data.length() > 0) {
        return data.toDouble();
    }

    return NULL;
}

/**
 * Функция создает и возвращает команду
 *
 * @param input
 * @return
 */
command_t createCommand(String input) {
    return command_t {
            createCommandAction(getSubstringKeyValue(input, "cmd")),
            createCommandData(getSubstringKeyValue(input, "data"))
    };
}

/**
 * Функция выполняет переданную комманду
 *
 * @param command
 * @return bool
 */
bool execute(command_t command) {
    action_t action = command.action;

    if (action == ROTATE_ENGINE && command.data != NULL) {
        long power = (long)command.data;
        uint8_t signal = (uint8_t)map(power, -100, 100, 0, 255);
        setMotorDirection(power > 0 ? DIRECTION_FORWARD : DIRECTION_BACKWARD);
        setMotorSignals(signal, signal);

        return true;
    } else if (action == ROTATE_SERVO && command.data != NULL) {
        long power = (long)command.data;
        uint8_t angle = (uint8_t)map(power, -100, 100, 0, 180);
        setSteeringWheelAngle(angle);

        return true;
    } else if (action == SWITCH_LIGHTING) {
        DEFAULT_STATE_LED = !DEFAULT_STATE_LED;
        digitalWrite(PIN_LED, DEFAULT_STATE_LED ? HIGH : LOW);

        return true;
    }

    return false;
}

/**
 * Функция установок при запуске
 *
 * Default arduino function
 */
void setup() {
    Serial.begin(9600);
    pinMode(PIN_MOTOR_DRIVER_IN1, OUTPUT);
    pinMode(PIN_MOTOR_DRIVER_IN2, OUTPUT);
    pinMode(PIN_MOTOR_DRIVER_IN3, OUTPUT);
    pinMode(PIN_MOTOR_DRIVER_IN4, OUTPUT);
    pinMode(PIN_MOTOR_DRIVER_ENA, OUTPUT);
    pinMode(PIN_MOTOR_DRIVER_ENB, OUTPUT);

    setMotorDirection(DIRECTION_FORWARD);

    pinMode(PIN_SERVO_SIGNAL, OUTPUT);
    setSteeringWheelPin(PIN_SERVO_SIGNAL);
    // Базовый угол для серво
    setSteeringWheelAngle(90);

    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, DEFAULT_STATE_LED ? HIGH : LOW);
}

/**
 * Default arduino function
 */
void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');

//        unsigned long start = micros();

        execute(createCommand(input));

//        unsigned long delta = micros() - start;
//        Serial.print("Delta Time: ");
//        Serial.print(delta);
//        Serial.println();
//        Serial.print("Count in seconds: ");
//        Serial.print(1000000 / delta);
//        Serial.println();
    }
}