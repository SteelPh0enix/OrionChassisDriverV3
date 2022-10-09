import json
import serial


class JsonChassis:
    def __init__(self, com_port: str, baud_rate: int = 250000) -> None:
        self._serial = serial.Serial(com_port, baud_rate, timeout=0.1)

    def send_power_and_rotation(self, power: int, rotation: int) -> None:
        msg = json.dumps({"X": power, "Y": rotation})
        print(f"Sending: {msg}")
        self._serial.write(msg.encode("ASCII"))

    def fetch_feedback_string(self) -> str:
        return self._serial.read_until().decode("ASCII")


def test_json_chassis():
    from serial.serialutil import SerialException

    try:
        chassis = JsonChassis("COM-1")
    except SerialException:
        print("Couldn't open COM-1!")

    chassis = JsonChassis("COM5")


if __name__ == "__main__":
    test_json_chassis()
