import json
import serial
from time import sleep

class JsonChassis:
    def __init__(self, com_port, baud_rate=250000):
        self._serial = serial.Serial(com_port, baud_rate, timeout=0.1)
        sleep(3) # bootup sleep

    def send_power_and_rotation(self, power, rotation):
        msg = json.dumps({"X": power, "Y": rotation}) + '\n'
        print("Sending: {}".format(msg))
        self._serial.write(msg.encode("ASCII"))

    def fetch_feedback_string(self):
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
