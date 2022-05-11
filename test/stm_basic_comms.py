import serial
import time
import struct


ARDUINO_COM_PORT = "COM9"
ARDUINO_BAUDRATE = 250000


class ChassisDriver:
    def __init__(
        self, port: str = ARDUINO_COM_PORT, baud: int = ARDUINO_BAUDRATE
    ) -> None:
        self.port = port
        self.baud = baud
        self.stm = None

    def connect(self) -> None:
        self.stm = serial.Serial(port=self.port, baudrate=self.baud)
        time.sleep(3.5)

    def send_speed_and_rotation(self, speed: int, rotation: int) -> None:
        print(f"Setting speed to {speed} and rotation to {rotation}")
        speed += 1000
        rotation += 1000
        if self.stm is not None:
            raw_data = struct.pack("<HHH", 0x2137, speed, rotation)
            self.stm.write(raw_data)
            while (self.stm.in_waiting < 6):
                time.sleep(0.01)
            print(f"Response: {self.stm.read_all()}")
