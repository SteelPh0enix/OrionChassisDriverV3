from typing import Dict, List
import inputs
from enum import Enum
from utils import interpolate


class GamepadInputType(Enum):
    NONE = 0
    BUTTON = 1
    AXIS = 2
    AXIS_SINGLE = 3

    def __str__(self):
        if self is GamepadInputType.NONE:
            return "None"
        elif self is GamepadInputType.BUTTON:
            return "Button"
        elif self is GamepadInputType.AXIS:
            return "Axis"
        elif self is GamepadInputType.AXIS_SINGLE:
            return "Singular axis"


GAMEPAD_MAPPINGS = {
    "Microsoft X-Box 360 pad": {
        "BTN_NORTH": {
            "type": GamepadInputType.BUTTON,
            "name": "Y",
            "state_pressed": 1,
            "state_released": 0,
        },
        "BTN_EAST": {
            "type": GamepadInputType.BUTTON,
            "name": "B",
            "state_pressed": 1,
            "state_released": 0,
        },
        "BTN_WEST": {
            "type": GamepadInputType.BUTTON,
            "name": "X",
            "state_pressed": 1,
            "state_released": 0,
        },
        "BTN_SOUTH": {
            "type": GamepadInputType.BUTTON,
            "name": "A",
            "state_pressed": 1,
            "state_released": 0,
        },
        "BTN_START": {
            "type": GamepadInputType.BUTTON,
            "name": "Start",
            "state_pressed": 1,
            "state_released": 0,
        },
        "BTN_SELECT": {
            "type": GamepadInputType.BUTTON,
            "name": "Select",
            "state_pressed": 1,
            "state_released": 0,
        },
        "BTN_TL": {
            "type": GamepadInputType.BUTTON,
            "name": "TriggerLeft",
            "state_pressed": 1,
            "state_released": 0,
        },
        "BTN_TR": {
            "type": GamepadInputType.BUTTON,
            "name": "TriggerRight",
            "state_pressed": 1,
            "state_released": 0,
        },
        "ABS_HAT0Y": {
            "type": GamepadInputType.AXIS,
            "name": "HatY",
            "minimum_value": 1,
            "maximum_value": -1,
            "dead_zone": 0,
        },
        "ABS_HAT0X": {
            "type": GamepadInputType.AXIS,
            "name": "HatX",
            "minimum_value": -1,
            "maximum_value": 1,
            "dead_zone": 0,
        },
        "ABS_Z": {
            "type": GamepadInputType.AXIS_SINGLE,
            "name": "AxisZ",
            "minimum_value": 0,
            "maximum_value": 255,
            "dead_zone": 0,
        },
        "ABS_RZ": {
            "type": GamepadInputType.AXIS_SINGLE,
            "name": "AxisRightZ",
            "minimum_value": 0,
            "maximum_value": 255,
            "dead_zone": 0,
        },
        "ABS_X": {
            "type": GamepadInputType.AXIS,
            "name": "AxisX",
            "minimum_value": -32768,
            "maximum_value": 32768,
            "dead_zone": 3000,
        },
        "ABS_Y": {
            "type": GamepadInputType.AXIS,
            "name": "AxisY",
            "minimum_value": -32768,
            "maximum_value": 32768,
            "dead_zone": 3000,
        },
        "ABS_RX": {
            "type": GamepadInputType.AXIS,
            "name": "AxisRightX",
            "minimum_value": -32768,
            "maximum_value": 32768,
            "dead_zone": 3000,
        },
        "ABS_RY": {
            "type": GamepadInputType.AXIS,
            "name": "AxisRightY",
            "minimum_value": -32768,
            "maximum_value": 32768,
            "dead_zone": 3000,
        },
    }
}
GAMEPAD_MAPPINGS["Logitech Gamepad F710"] = GAMEPAD_MAPPINGS["Microsoft X-Box 360 pad"]


class GamepadInputEvent:
    """Value is always in range -1 : 1, every axis input is mapped to this range, buttons have only True/False states"""

    def __init__(self, type, name, value):
        self.type = type
        self.name = name
        self.value = value

    def valid(self):
        return self.type is not GamepadInputType.NONE

    def __str__(self):
        return "Type: {0}, name: {1}, value: {2}".format(
            str(self.type), self.name, self.value
        )


class GamepadManager:
    def __init__(self, gamepad=None):
        self._gamepad = None

        if gamepad is None and len(inputs.devices.gamepads) > 0:
            self._gamepad = inputs.devices.gamepads[0]
        elif gamepad is not None:
            self._gamepad = gamepad
        else:
            raise RuntimeError("No gamepad detected!")

    def events(self):
        event_list = list()
        for event in self._gamepad.read():
            # self._print_gamepad_event(event, "ABS_Z")
            input_event = self._parse_gamepad_event(event)
            if input_event.valid():
                event_list.append(input_event)

        return event_list

    @staticmethod
    def _print_gamepad_event(event, code_filter=None):
        if code_filter is None or event.code == code_filter:
            print(
                "Device: {0}, timestamp: {1}, code: {2}, state: {3}, ev_type: {4}".format(
                    event.device,
                    event.timestamp,
                    event.code,
                    event.state,
                    event.ev_type,
                )
            )

    @staticmethod
    def _find_gamepad_mapping(device_name):
        if device_name in GAMEPAD_MAPPINGS:
            return GAMEPAD_MAPPINGS[device_name]
        else:
            return dict()

    @staticmethod
    def _map_input_event(event, mapping):
        if mapping is None or bool(mapping) is False or event is None:
            return GamepadInputEvent(GamepadInputType.NONE, "", 0)

        mapping_type = mapping["type"]

        if mapping_type is GamepadInputType.BUTTON:
            button_state = True if event.state == mapping["state_pressed"] else False
            return GamepadInputEvent(
                GamepadInputType.BUTTON, mapping["name"], button_state
            )
        elif mapping_type is GamepadInputType.AXIS:
            mapped_axis_value = 0
            if abs(event.state) >= mapping["dead_zone"]:
                mapped_axis_value = interpolate(
                    event.state,
                    (mapping["minimum_value"], mapping["maximum_value"]),
                    (-1, 1),
                )
            return GamepadInputEvent(
                GamepadInputType.AXIS, mapping["name"], mapped_axis_value
            )
        elif mapping_type is GamepadInputType.AXIS_SINGLE:
            mapped_axis_value = 0
            if abs(event.state) >= mapping["dead_zone"]:
                mapped_axis_value = interpolate(
                    event.state,
                    (mapping["minimum_value"], mapping["maximum_value"]),
                    (0, 1),
                )
            return GamepadInputEvent(
                GamepadInputType.AXIS_SINGLE, mapping["name"], mapped_axis_value
            )

        return GamepadInputEvent(GamepadInputType.NONE, "", 0)

    @staticmethod
    def _parse_gamepad_event(event):
        # mapping should contain a map with event codes as keys
        mapping = GamepadManager._find_gamepad_mapping(str(event.device))
        if not bool(mapping):
            raise RuntimeError(
                "No mapping found for controller '{0}'!".format(event.device)
            )

        if event.code in mapping:
            return GamepadManager._map_input_event(event, mapping[event.code])

        return GamepadInputEvent(GamepadInputType.NONE, "", 0)


def main():
    gamepad_manager = GamepadManager()

    while True:
        events = gamepad_manager.events()
        print(f"Events count: {len(events)}")
        for event in events:
            print(event)


if __name__ == "__main__":
    main()
