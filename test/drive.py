from stm_basic_comms import ChassisDriver
import time


def main():
    chassis = ChassisDriver()
    chassis.connect()

    chassis.send_speed_and_rotation(1000, 0)
    time.sleep(10)
    chassis.send_speed_and_rotation(-1000, 0)
    time.sleep(10)
    chassis.send_speed_and_rotation(500, 1000)
    time.sleep(10)
    chassis.send_speed_and_rotation(500, -1000)
    time.sleep(10)
    chassis.send_speed_and_rotation(0, 0)


if __name__ == "__main__":
    main()
