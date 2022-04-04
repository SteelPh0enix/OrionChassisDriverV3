from email import message
import serial
import time
import struct
from Chassis_pb2 import HealthCheck, Log
from messages import get_message_id_by_type, get_message_type_by_id


class Chassis:
    def __init__(self, com_port, baudrate) -> None:
        self.arduino = serial.Serial(port=com_port, baudrate=baudrate)
        print("Chassis COM port {}. Waiting for boot...".format("opened" if self.arduino.is_open else "NOT opened!!!"))
        time.sleep(3)
        print("Boot wait finished!")

    def send_message(self, message):
        self.arduino.write(self._message_to_bytes(message))

    def read_message(self):
        length_bytes = self.arduino.read(2)
        if len(length_bytes) == 2:
            message_length = struct.unpack("<H", length_bytes)
            if message_length > 0:
                message_data = self.arduino.read(message_length)
                return self._message_from_bytes(message_data)
        return None

    def print_incoming_data(self):
        read_data = self.arduino.read_all()
        if len(read_data) > 0:
            print(read_data)
    
    def _message_to_bytes(self, message):
        message_data = message.SerializeToString()
        message_length = len(message_data) + 1
        message_header = struct.pack(">HB", message_length, get_message_id_by_type(message))

        return message_header + message_data

    def _message_from_bytes(self, message_bytes):
        message = get_message_type_by_id(message_bytes[0])()
        message.ParseFromString(message_bytes[1:])
        return message