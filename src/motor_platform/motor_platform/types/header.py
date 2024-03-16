from typing import NamedTuple

from motor_platform.types.timestamp import Timestamp

class Header(NamedTuple):
    sequence: int
    timestamp: Timestamp


    @staticmethod
    def decode(json_value):
        return Header(sequence=json_value["sequence"], timestamp=Timestamp.decode(json_value["timestamp"]))
