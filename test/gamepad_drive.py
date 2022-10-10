from gamepad_thread import GamepadThread
from time import sleep
from chassis_json import JsonChassis

CHASSIS_COM_PORT = "/dev/ttyUSB0"

TRANSMISSION_DELAY_SECONDS = 0.1
SPEED_AXIS_NAME = "AxisY"
ROTATION_AXIS_NAME = "AxisX"


def main():
    try:
        gamepad_thread = GamepadThread()
    except RuntimeError as rt:
        print(f"Cannot create gamepad listener, reason: {rt}")
        exit(1)

    try:
        chassis = JsonChassis(CHASSIS_COM_PORT, 250000)
    except Exception as ex:
        print(f"Cannot connect to chassis, reason: {ex}")
        exit(2)

    gamepad_thread.start()
    while True:
        current_state = gamepad_thread.get_current_state()
        current_speed = 0
        current_rotation = 0

        if SPEED_AXIS_NAME in current_state:
            current_speed = int(current_state[SPEED_AXIS_NAME] * 1000)
        if ROTATION_AXIS_NAME in current_state:
            current_rotation = int(current_state[ROTATION_AXIS_NAME] * 1000)

        # print(f"Current speed: {current_speed}, rotation: {current_rotation}")
        chassis.send_power_and_rotation(current_speed, current_rotation)
        # print(chassis.fetch_feedback_string())
        sleep(TRANSMISSION_DELAY_SECONDS)


if __name__ == "__main__":
    main()
