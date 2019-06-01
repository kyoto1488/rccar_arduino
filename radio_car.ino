#include <Arduino.h>
#include <Servo.h>
#include <radio_car.h>

Servo steeringWheel;
bool DEBUG = false;

/**
 * Функция устанавливает направление моторов
 * за счет переключения полярности пинов
 *
 * @param direction
 */
void setMotorDirection(uint8_t direction) {
    switch (direction) {
        case FORWARD:
            digitalWrite(PIN_MOTOR_DRIVER_IN1, HIGH);
            digitalWrite(PIN_MOTOR_DRIVER_IN2, LOW);
            digitalWrite(PIN_MOTOR_DRIVER_IN3, HIGH);
            digitalWrite(PIN_MOTOR_DRIVER_IN4, LOW);
            break;
        case BACKWARD:
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
void setSteeringWheelPin(uint8_t pin) {
    steeringWheel.attach(pin);
}

/**
 * Функция парсит данные из переданной строки и ключа
 * @example $data = "cmd: action; data: 1.222;" -> f(data, "cmd") -> "action"
 *
 * @param input
 * @param key
 * @return value of NULL if not found key
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
        else if (action.equals(KEY_DEBUG_MODE))
            return DEBUG_MODE;
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
        return (data_t) data.toInt();

    return -9999;
}

/**
 * Функция создает и возвращает команду
 *
 * @param input
 * @return
 */
command_t createCommand(String input) {
    return command_t {
            createCommandAction(getSubstringValueFromKey(input, "at")),
            createCommandData(getSubstringValueFromKey(input, "dt"))
    };
}

/**
 * Проверка валидности действия команды
 *
 * @param command
 * @return
 */
bool isValidCommandAction(command_t command) {
    return command.action != NULL;
}

/**
 * Проверка валидности данных команды
 * Данные не должны выходить за диапазон [-128,127]
 *
 * @param command
 * @return
 */
bool isValidCommandData(command_t command) {
    return command.data >= -128 && command.data <= 127;
}

/**
 * Вращает моторы
 *
 * @param data
 * @return
 */
bool rotateEngine(command_t command) {
    long power = (long) command.data;
    uint8_t signal = (uint8_t) map(power < 0 ? power * -1 : power, 0, 100, 0, 255);
    setMotorDirection(power > 0 ? FORWARD : BACKWARD);
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
    digitalWrite(PIN_LED, command.data > 0 ? HIGH : LOW);

    return true;
}

/**
 * Включает/выключает режим отладки
 *
 * @param command
 * @return
 */
bool debugMode(command_t command) {
    DEBUG = command.data > 0;

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
        case DEBUG_MODE:
            return debugMode(command);
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

    setMotorDirection(FORWARD);

    pinMode(PIN_SERVO_SIGNAL, OUTPUT);
    setSteeringWheelPin(PIN_SERVO_SIGNAL);
    // Базовый угол для серво
    setSteeringWheelAngle(90);

    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, DEFAULT_STATE_LED);
}

/**
 * @example command: "at: e; dt: 100";
 * @details at = action, e = engine, dt = data, 100 = data value
 *
 * Default arduino function
 */
void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        command_t command = createCommand(input);

        if (isValidCommandAction(command) && isValidCommandData(command)) {
            long startExecutionTime = micros();
            bool isExecuted = execute(command);
            long endExecutionTime = micros();

            if (DEBUG) {
                String logData = "Input: ";
                logData.concat(input);
                logData.concat("\nExecuted: ");
                logData.concat(isExecuted ? "true" : "false");
                logData.concat("\nDelta time: ");
                logData.concat(endExecutionTime - startExecutionTime);
                logData.concat("\nCommands in seconds: ");
                logData.concat(1000000 / (endExecutionTime - startExecutionTime));
                logData.concat("\n--------------------\n");
                Serial.print(logData);
            }
        } else {
            if (DEBUG) {
                String logData = "Input: ";
                logData.concat(input);
                logData.concat("\nInvalid command!");
                logData.concat("\n--------------------\n");
                Serial.print(logData);
            }
        }
    }
}