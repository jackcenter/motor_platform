from typing import NamedTuple

from motor_platform.types.header import Header

class Input(NamedTuple):
    header: Header
    voltage: float

    @staticmethod
    def decode(json_value):
        return Input(
            header=Header.decode(json_value["header"]),
            voltage=json_value["voltage"]
        )