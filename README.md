# OrionChassisDriverV3

Orion Chassis Driver, version 3.0!

...and back to the JSON we go!

## Using the scripts for driving

0) Install `inputs` and `pyserial` packages (do it as root via `sudo` if you haven't set up udev rules for USB UART, otherwise do it locally):
    ```pip3 install inputs pyserial```
1) Go to `test` directory
2) Make sure the correct device is set as UART output - check the `CHASSIS_COM_PORT` constant in `gamepad_drive.py` script, change if necessary
3) Run `gamepad_drive.py` script (as root, if you get permission error)
    ```python3 ./gamepad_drive.py```

If you get gamepad binding error, you have to create a proper binding (or copy existing) in `gamepad_manager.py`. Modify `GAMEPAD_MAPPINGS` constant.
