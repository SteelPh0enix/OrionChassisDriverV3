# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Chassis.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from .proto import nanopb_pb2 as nanopb__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='Chassis.proto',
  package='',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=b'\n\rChassis.proto\x1a\x0cnanopb.proto\"\r\n\x0bHealthCheck\"3\n\x10\x43hassisDirection\x12\r\n\x05power\x18\x01 \x01(\x05\x12\x10\n\x08rotation\x18\x02 \x01(\x05\"y\n\x03Log\x12\x17\n\x04type\x18\x01 \x01(\x0e\x32\t.Log.Type\x12\x17\n\x07\x63ontent\x18\x02 \x01(\tB\x06\x92?\x03p\xc8\x01\"@\n\x04Type\x12\x0b\n\x07INVALID\x10\x00\x12\t\n\x05\x44\x45\x42UG\x10\x01\x12\x08\n\x04INFO\x10\x02\x12\x0b\n\x07WARNING\x10\x03\x12\t\n\x05\x45RROR\x10\x04\"\xd6\x02\n\x0f\x43hassisFeedback\x12\x15\n\rchassis_power\x18\x01 \x01(\x05\x12\x18\n\x10\x63hassis_rotation\x18\x02 \x01(\x05\x12;\n\x06wheels\x18\x03 \x03(\x0b\x32\x1e.ChassisFeedback.WheelFeedbackB\x0b\x92?\x02\x10\x04\x92?\x03\x80\x01\x01\x1a\xd4\x01\n\rWheelFeedback\x12\x15\n\rcurrent_power\x18\x01 \x01(\x05\x12\x14\n\x0ctarget_power\x18\x02 \x01(\x05\x12\x14\n\x0c\x63urrent_draw\x18\x03 \x01(\x02\x12;\n\tdirection\x18\x04 \x01(\x0e\x32(.ChassisFeedback.WheelFeedback.Direction\x12\x11\n\x02id\x18\x05 \x01(\tB\x05\x92?\x02p2\"0\n\tDirection\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x07\x46ORWARD\x10\x01\x12\x0c\n\x08\x42\x41\x43KWARD\x10\x02\x62\x06proto3'
  ,
  dependencies=[nanopb__pb2.DESCRIPTOR,])



_LOG_TYPE = _descriptor.EnumDescriptor(
  name='Type',
  full_name='Log.Type',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='INVALID', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DEBUG', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='INFO', index=2, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='WARNING', index=3, number=3,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERROR', index=4, number=4,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=156,
  serialized_end=220,
)
_sym_db.RegisterEnumDescriptor(_LOG_TYPE)

_CHASSISFEEDBACK_WHEELFEEDBACK_DIRECTION = _descriptor.EnumDescriptor(
  name='Direction',
  full_name='ChassisFeedback.WheelFeedback.Direction',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='FORWARD', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='BACKWARD', index=2, number=2,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=517,
  serialized_end=565,
)
_sym_db.RegisterEnumDescriptor(_CHASSISFEEDBACK_WHEELFEEDBACK_DIRECTION)


_HEALTHCHECK = _descriptor.Descriptor(
  name='HealthCheck',
  full_name='HealthCheck',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=31,
  serialized_end=44,
)


_CHASSISDIRECTION = _descriptor.Descriptor(
  name='ChassisDirection',
  full_name='ChassisDirection',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='power', full_name='ChassisDirection.power', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='rotation', full_name='ChassisDirection.rotation', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=46,
  serialized_end=97,
)


_LOG = _descriptor.Descriptor(
  name='Log',
  full_name='Log',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='Log.type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='content', full_name='Log.content', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=b'\222?\003p\310\001', file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _LOG_TYPE,
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=99,
  serialized_end=220,
)


_CHASSISFEEDBACK_WHEELFEEDBACK = _descriptor.Descriptor(
  name='WheelFeedback',
  full_name='ChassisFeedback.WheelFeedback',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='current_power', full_name='ChassisFeedback.WheelFeedback.current_power', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='target_power', full_name='ChassisFeedback.WheelFeedback.target_power', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='current_draw', full_name='ChassisFeedback.WheelFeedback.current_draw', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='direction', full_name='ChassisFeedback.WheelFeedback.direction', index=3,
      number=4, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='id', full_name='ChassisFeedback.WheelFeedback.id', index=4,
      number=5, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=b'\222?\002p2', file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _CHASSISFEEDBACK_WHEELFEEDBACK_DIRECTION,
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=353,
  serialized_end=565,
)

_CHASSISFEEDBACK = _descriptor.Descriptor(
  name='ChassisFeedback',
  full_name='ChassisFeedback',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='chassis_power', full_name='ChassisFeedback.chassis_power', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='chassis_rotation', full_name='ChassisFeedback.chassis_rotation', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='wheels', full_name='ChassisFeedback.wheels', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=b'\222?\002\020\004\222?\003\200\001\001', file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[_CHASSISFEEDBACK_WHEELFEEDBACK, ],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=223,
  serialized_end=565,
)

_LOG.fields_by_name['type'].enum_type = _LOG_TYPE
_LOG_TYPE.containing_type = _LOG
_CHASSISFEEDBACK_WHEELFEEDBACK.fields_by_name['direction'].enum_type = _CHASSISFEEDBACK_WHEELFEEDBACK_DIRECTION
_CHASSISFEEDBACK_WHEELFEEDBACK.containing_type = _CHASSISFEEDBACK
_CHASSISFEEDBACK_WHEELFEEDBACK_DIRECTION.containing_type = _CHASSISFEEDBACK_WHEELFEEDBACK
_CHASSISFEEDBACK.fields_by_name['wheels'].message_type = _CHASSISFEEDBACK_WHEELFEEDBACK
DESCRIPTOR.message_types_by_name['HealthCheck'] = _HEALTHCHECK
DESCRIPTOR.message_types_by_name['ChassisDirection'] = _CHASSISDIRECTION
DESCRIPTOR.message_types_by_name['Log'] = _LOG
DESCRIPTOR.message_types_by_name['ChassisFeedback'] = _CHASSISFEEDBACK
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

HealthCheck = _reflection.GeneratedProtocolMessageType('HealthCheck', (_message.Message,), {
  'DESCRIPTOR' : _HEALTHCHECK,
  '__module__' : 'Chassis_pb2'
  # @@protoc_insertion_point(class_scope:HealthCheck)
  })
_sym_db.RegisterMessage(HealthCheck)

ChassisDirection = _reflection.GeneratedProtocolMessageType('ChassisDirection', (_message.Message,), {
  'DESCRIPTOR' : _CHASSISDIRECTION,
  '__module__' : 'Chassis_pb2'
  # @@protoc_insertion_point(class_scope:ChassisDirection)
  })
_sym_db.RegisterMessage(ChassisDirection)

Log = _reflection.GeneratedProtocolMessageType('Log', (_message.Message,), {
  'DESCRIPTOR' : _LOG,
  '__module__' : 'Chassis_pb2'
  # @@protoc_insertion_point(class_scope:Log)
  })
_sym_db.RegisterMessage(Log)

ChassisFeedback = _reflection.GeneratedProtocolMessageType('ChassisFeedback', (_message.Message,), {

  'WheelFeedback' : _reflection.GeneratedProtocolMessageType('WheelFeedback', (_message.Message,), {
    'DESCRIPTOR' : _CHASSISFEEDBACK_WHEELFEEDBACK,
    '__module__' : 'Chassis_pb2'
    # @@protoc_insertion_point(class_scope:ChassisFeedback.WheelFeedback)
    })
  ,
  'DESCRIPTOR' : _CHASSISFEEDBACK,
  '__module__' : 'Chassis_pb2'
  # @@protoc_insertion_point(class_scope:ChassisFeedback)
  })
_sym_db.RegisterMessage(ChassisFeedback)
_sym_db.RegisterMessage(ChassisFeedback.WheelFeedback)


_LOG.fields_by_name['content']._options = None
_CHASSISFEEDBACK_WHEELFEEDBACK.fields_by_name['id']._options = None
_CHASSISFEEDBACK.fields_by_name['wheels']._options = None
# @@protoc_insertion_point(module_scope)
