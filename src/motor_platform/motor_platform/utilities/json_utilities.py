import json

from motor_platform.types.header import Header
from motor_platform.types.input import Input
from motor_platform.types.measurement import Measurement
from motor_platform.types.state import State
from motor_platform.types.timestamp import Timestamp


class TimestampEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, Timestamp):
            return {"microseconds": obj.microseconds}

        return super().default(obj)


class HeaderEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, Header):
            timestamp_encoder = TimestampEncoder()
            return {
                "sequence": obj.sequence,
                "timestamp": timestamp_encoder.default(obj.timestamp),
            }

        return super().default(obj)


class InputEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, Input):
            header_encoder = HeaderEncoder()
            return {
                "header": header_encoder.default(obj.header),
                "voltage": obj.voltage,
            }

        return super().default(obj)


class MeasurementEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, Measurement):
            header_encoder = HeaderEncoder()
            return {
                "header": header_encoder.default(obj.header),
                "encoder_1_pos": obj.encoder_1_pos,
                "encoder_2_pos": obj.encoder_2_pos,
            }

        return super().default(self, obj)


class StateEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, State):
            header_encoder = HeaderEncoder()
            return {
                "header": header_encoder.default(obj.header),
                "joint_1_position_rad": obj.joint_1_position_rad,
                "joint_1_velocity_rps": obj.joint_1_velocity_rps,
                "joint_2_position_rad": obj.joint_2_position_rad,
                "joint_2_velocity_rps": obj.joint_2_velocity_rps,
            }

        return super().default(self, obj)
