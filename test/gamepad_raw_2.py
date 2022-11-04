import Gamepad

# ANSI colour code sequences
GREEN = "\033[0;32m"
CYAN = "\033[0;36m"
BLUE = "\033[1;34m"
RESET = "\033[0m"


def main():
    if not Gamepad.available():
        print("No gamepad detected!")
        exit(1)

    pad = Gamepad.Xbox360(1)

    while pad.isConnected():
        eventType, index, value = pad.getNextEvent()

        print(
            BLUE
            + eventType
            + RESET
            + ",\t  "
            + GREEN
            + str(index)
            + RESET
            + ",\t"
            + CYAN
            + str(value)
            + RESET
        )


if __name__ == "__main__":
    main()
