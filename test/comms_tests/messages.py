from .Chassis_pb2 import HealthCheck, Log, ChassisDirection, ChassisFeedback
from enum import IntEnum


class MessageID(IntEnum):
    Invalid = 0x00
    HealthCheck = 0x01
    Log = 0x20
    ChassisDirection = 0x40
    ChassisFeedback = 0x50


message_types = [
    (HealthCheck, MessageID.HealthCheck),
    (Log, MessageID.Log),
    (ChassisDirection, MessageID.ChassisDirection),
    (ChassisFeedback, MessageID.ChassisFeedback),
]


def get_message_id_by_type(message):
    for (msg_type, msg_id) in message_types:
        if msg_type == type(message):
            return msg_id
    return None


def get_message_type_by_id(message_id):
    for (msg_type, msg_id) in message_types:
        if msg_id == message_id:
            return msg_type
    return None
