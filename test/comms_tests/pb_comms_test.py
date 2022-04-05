from chassis import Chassis
from time import sleep


def main():
    chassis = Chassis("COM5", 250000)

    for i in range(0, 20):
        feedback = chassis.drive(i * 100, 0)
        print(
            "Chassis power: {0}, rotation: {1}".format(
                feedback.chassis_power, feedback.chassis_rotation
            )
        )
        for index, wheel in enumerate(feedback.wheels):
            print(
                "Wheel {0} ({1}), Current/target power: {2}/{3}, current draw: {4:.2f}, direction: {5}".format(
                    index,
                    wheel.id,
                    wheel.current_power,
                    wheel.target_power,
                    wheel.current_draw,
                    wheel.direction,
                )
            )
        sleep(0.5)


if __name__ == "__main__":
    main()
