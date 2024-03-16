from typing import NamedTuple

from motor_platform.types.header import Header


class Measurement(NamedTuple):
    header: Header
    encoder_1_pos: int
    encoder_2_pos: int

    @staticmethod
    def decode(json_value):
        return Measurement(
            header=Header.decode(json_value["header"]),
            encoder_1_pos=json_value["encoder_1_pos"],
            encoder_2_pos=json_value["encoder_2_pos"],
        )
