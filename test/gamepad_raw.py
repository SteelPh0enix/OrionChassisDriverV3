import inputs


def main():
    if len(inputs.devices.gamepads) == 0:
        print("Error - no gamepads detected!")
        exit(1)

    gamepad = inputs.devices.gamepads[0]
    print(f"Using gamepad '{gamepad}'")

    while True:
        for event in gamepad.read():
            if event.ev_type != "Sync":
                print(
                    f"code: {event.code}, state: {event.state}, type: {event.ev_type}"
                )


if __name__ == "__main__":
    main()
