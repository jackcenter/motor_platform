import json

from motor_platform.types.timestamp import Timestamp
import motor_platform.types as types


class TimestampDecoder(json.JSONDecoder):
    def decode(self, json_string):
        obj = super().decode(json_string)

        if "timestamp" in obj:
            return Timestamp(microseconds=obj["timestamp"]["microseconds"])

        return obj


class TimestampEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, Timestamp):
            return {"timestamp": {"microseconds": obj.microseconds}}

        return super().default(obj)


def decode_type(dct):
    if "timestamp" in dct:
        return types.Timestamp(dct["microseoncds"])

    return dct


def create_from_json(json_str: str):
    json_dict = json.loads(json_str)

    print(json_dict)

    {
        "input": {
            "header": types.Header(
                sequence=2, timestamp=types.Timestamp(microseconds=1)
            ),
            "voltage": 3.4,
        }
    }

    object_list = []
    for key, val in json_dict.items():

        if key == "input":
            object_list.append(types.Input(**val))

        if key == "measurement":
            object_list.append(types.Measurement(**val))

        if key == "state":
            object_list.append(types.State(**val))

        if key == "header":
            object_list.append(types.Header(**val))

        if key == "timestamp":
            object_list.append(types.Timestamp(**val))

    return object_list
