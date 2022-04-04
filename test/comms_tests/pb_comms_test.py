from Chassis_pb2 import HealthCheck, Log
from chassis import Chassis

def main():
    chassis = Chassis("COM9", 250000)

    chassis.send_message(HealthCheck())
    print(chassis.read_message())

if __name__ == "__main__":
    main()
