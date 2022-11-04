import inputs


def main():
    if len(inputs.devices.gamepads) == 0:
        print("Error - no gamepads detected!")
        exit(1)

    gamepad = inputs.devices.gamepads[0]
    print("Using gamepad '{}'".format(gamepad))

    while True:
        for event in gamepad.read():
            if event.ev_type != "Sync":
                print(
                    "code: {}, state: {}, type: {}".format(
                        event.code, event.state, event.ev_type
                    )
                )


if __name__ == "__main__":
    main()
