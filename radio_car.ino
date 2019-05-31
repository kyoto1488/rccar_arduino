#include <Arduino.h>
#include <Servo.h>
#include "radio_car.h"

Servo steeringWheel;

const pin_t PIN_MOTOR_DRIVER_ENA = 8;
const pin_t PIN_MOTOR_DRIVER_IN1 = 8;
const pin_t PIN_MOTOR_DRIVER_IN2 = 4;
const pin_t PIN_MOTOR_DRIVER_ENB = 5;
const pin_t PIN_MOTOR_DRIVER_IN3 = 7;
const pin_t PIN_MOTOR_DRIVER_IN4 = 8;
const pin_t PIN_SERVO_SIGNAL = 11;
const pin_t PIN_LED = 13;

const action_t ROTATE_ENGINE = 0x1;
const action_key_t KEY_ROTATE_ENGINE = "e";
const action_t ROTATE_SERVO = 0x2;
const action_key_t KEY_ROTATE_SERVO = "s";
const action_t SWITCH_LIGHTING = 0x3;
const action_key_t KEY_SWITCH_LIGHTING = "l";

const motor_dir_t DIRECTION_FORWARD = 0x1;
const motor_dir_t DIRECTION_BACKWARD = 0x2;

const uint8_t DEFAULT_STATE_LED = LOW;

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
 * @param input
 * @param key
 * @return
 */
String getSubstringValueFromKey(String input, String key) {
    int index = input.indexOf(key);

    if (index >= 0) {
        int start = input.indexOf(':', (unsigned int) index) + 1;
        int end = input.indexOf(';', (unsigned int) start);
        String substring = input.substring((unsigned int) start, (unsigned int) end);
        substring.trim();

        return substring;
    }

    return NULL;
}

/**
 * Функция возвращает действие для команды
 *
 * @param action
 * @return
 */
action_t createCommandAction(String action) {
    if (action != NULL) {
        if (action.equals(KEY_ROTATE_ENGINE))
            return ROTATE_ENGINE;
        else if (action.equals(KEY_ROTATE_SERVO))
            return ROTATE_SERVO;
        else if (action.equals(KEY_SWITCH_LIGHTING))
            return SWITCH_LIGHTING;
        // add new actions...
    }

    return NULL;
}

/**
 * Функция возвращает данные для команды
 *
 * @param data
 * @return
 */
data_t createCommandData(String data) {
    if (data != NULL)
        return (data_t) data.toDouble();

    return NULL;
}

/**
 * Функция создает и возвращает команду
 *
 * @param input
 * @return
 */
command_t createCommand(String input) {
    return command_t{
            createCommandAction(getSubstringValueFromKey(input, "at")),
            createCommandData(getSubstringValueFromKey(input, "dt"))
    };
}

/**
 * Проверка валидности комманды
 *
 * @param command
 * @return
 */
bool isValidCommand(command_t command) {
    return command.action != NULL && command.data != NULL;
}

/**
 * Вращает моторы
 *
 * @param data
 * @return
 */
bool rotateEngine(command_t command) {
    long power = (long) command.data;
    uint8_t signal = (uint8_t) map(power, -100, 100, 0, 255);
    motor_dir_t direction = power > 0 ? DIRECTION_FORWARD : DIRECTION_BACKWARD;
    setMotorDirection(direction);
    setMotorSignals(signal, signal);

    return true;
}

/**
 * Вращает серво привод
 *
 * @param data
 * @return
 */
bool rotateServo(command_t command) {
    long power = (long) command.data;
    uint8_t angle = (uint8_t) map(power, -100, 100, 0, 180);
    setSteeringWheelAngle(angle);

    return true;
}

/**
 * Переключает питание на светодиоды
 *
 * @return
 */
bool switchLighting(command_t command) {
    uint8_t state = (uint8_t)command.data == 1 ? HIGH : LOW;
    digitalWrite(PIN_LED, state);

    return true;
}

/**
 * Функция выполняет переданную комманду
 *
 * @param command
 * @return
 */
bool execute(command_t command) {
    switch (command.action) {
        case ROTATE_ENGINE:
            return rotateEngine(command);
        case ROTATE_SERVO:
            return rotateServo(command);
        case SWITCH_LIGHTING:
            return switchLighting(command);
        default:
            return false;
    }
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
    digitalWrite(PIN_LED, DEFAULT_STATE_LED);
}

/**
 * Default arduino function
 */
void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        command_t command = createCommand(input);

        if (isValidCommand(command)) {
            bool isExecuted = execute(command);
            Serial.print("Input: ");
            Serial.print(input);
            Serial.println();
            Serial.print("Execute: ");
            Serial.print(isExecuted ? "true" : "false");
            Serial.println();
        } else {
            Serial.print("Input: ");
            Serial.print(input);
            Serial.println();
            Serial.println("Invalid command!");
        }
    }
}