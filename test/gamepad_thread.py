from threading import Lock, Thread, Event
from gamepad_manager import GamepadManager
from time import sleep
from copy import deepcopy


class GamepadThread(Thread):
    def __init__(
        self,
        name="gamepad_thread",
    ):
        super().__init__(name=name, daemon=True)

        self._gamepad_manager = GamepadManager()
        self._current_state = dict()
        self._should_stop = Event()
        self._state_lock = Lock()

    def run(self):
        while not self._should_stop.is_set():
            for event in self._gamepad_manager.events():
                self._update_current_state(event)
        return

    def get_current_state(self):
        with self._state_lock:
            return deepcopy(self._current_state)

    def stop_listening(self):
        self._should_stop.set()

    def _update_current_state(self, event):
        with self._state_lock:
            self._current_state[event.name] = event.value


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
