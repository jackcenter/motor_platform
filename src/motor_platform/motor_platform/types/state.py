from typing import NamedTuple

from motor_platform.types.header import Header


class State(NamedTuple):
    header: Header
    joint_1_position_rad: float
    joint_1_velocity_rps: float
    joint_2_position_rad: float
    joint_2_velocity_rps: float

    @staticmethod
    def decode(json_value):
        return State(
            header=Header.decode(json_value["header"]),
            joint_1_position_rad=json_value["joint_1_position_rad"],
            joint_1_velocity_rps=json_value["joint_1_velocity_rps"],
            joint_2_position_rad=json_value["joint_2_position_rad"],
            joint_2_velocity_rps=json_value["joint_2_velocity_rps"],
        )
