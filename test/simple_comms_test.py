import serial
import struct
import time

ARDUINO_COM_PORT = "COM5"
ARDUINO_BAUDRATE = 9600

def main():
    stm = serial.Serial(ARDUINO_COM_PORT, ARDUINO_BAUDRATE)
    time.sleep(2)
    test_echo_data = struct.pack("<HHH", 0x2137, 500, 1000)
    print(f"Sending {test_echo_data}")
    stm.write(test_echo_data)

    while stm.in_waiting < 6:
        time.sleep(0.01)

    print(stm.read_all())


if __name__ == "__main__":
    main()
