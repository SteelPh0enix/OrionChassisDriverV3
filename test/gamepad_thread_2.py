from threading import Lock, Thread, Event
from time import sleep
from copy import deepcopy
import Gamepad


class GamepadThread(Thread):
    def __init__(self, name="gamepad_thread", gamepad_id=1):
        super().__init__(name=name, daemon=True)

        if not Gamepad.available():
            raise RuntimeError("Gamepad is not connected!")

        self._gamepad = Gamepad.Xbox360(gamepad_id)
        self._current_state = dict()
        self._should_stop = Event()
        self._state_lock = Lock()

    def run(self):
        while not self._should_stop.is_set() and self._gamepad.isConnected():
            eventType, index, value = self._gamepad.getNextEvent()
            self._update_current_state(eventType, index, value)
        return

    def get_current_state(self):
        with self._state_lock:
            return deepcopy(self._current_state)

    def stop_listening(self):
        self._should_stop.set()

    def _update_current_state(self, eventType, index, value):
        with self._state_lock:
            if index == "LEFT-Y":
                self._current_state["AxisY"] = value
            elif index == "LEFT-X":
                self._current_state["AxisX"] = value
            # self._current_state[event.name] = event.value


def main():
    gamepad_thread = GamepadThread("gamepad_listener")
    gamepad_thread.start()
    try:
        while True:
            print(gamepad_thread.get_current_state())
            sleep(0.05)
    except KeyboardInterrupt:
        gamepad_thread.stop_listening()
        print("Goodbye!")


if __name__ == "__main__":
    main()
