from typing import NamedTuple


class Timestamp(NamedTuple):
    microseconds: int


class Header(NamedTuple):
    sequence: int
    timestamp: Timestamp
    

class Input(NamedTuple):
    header: Header
    voltage: float


class Measurement(NamedTuple):
    header: Header
    encoder_1_pos: int
    encoder_2_pos: int


class State(NamedTuple):
    header: Header
    joint_1_position_rad: float
    joint_1_velocity_rps: float
    joint_2_position_rad: float
    joint_2_velocity_rps: float
