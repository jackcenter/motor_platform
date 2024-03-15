import argparse
import json
import logging
from typing import NamedTuple

import matplotlib.pyplot as plt


class Timestamp(NamedTuple):
    microseconds: int 

def decode_timetamp(json_value):
    return Timestamp(microseconds=json_value["microseconds"])


class Header(NamedTuple):
    sequence: int
    timestamp: Timestamp

def decode_header(json_value):
    return Header(sequence=json_value["sequence"], timestamp=decode_timetamp(json_value["timestamp"]))

class State(NamedTuple):
    header: Header
    joint_1_position_rad: float
    joint_1_velocity_rps: float
    joint_2_position_rad: float
    joint_2_velocity_rps: float

def decode_state(json_value):
    return State(
        header=decode_header(json_value["header"]),
        joint_1_position_rad=json_value["joint_1_position_rad"],
        joint_1_velocity_rps=json_value["joint_1_velocity_rps"],
        joint_2_position_rad=json_value["joint_2_position_rad"],
        joint_2_velocity_rps=json_value["joint_2_velocity_rps"]
    )

class Measurement(NamedTuple):
    header: Header
    encoder_1_pos: int
    encoder_2_pos: int

def decode_measurement(json_value):
    return Measurement(
        header=decode_header(json_value["header"]),
        encoder_1_pos=json_value["encoder_1_pos"],
        encoder_2_pos=json_value["encoder_2_pos"]
    )

def main():
    args = setup()
    logging.info("Starting...")

    data = []
    with open(args.log_file, 'r') as file_in:
        data = json.load(file_in)

    input_list = []
    measurement_list = []
    state_list = []

    for datum in data:
        measurement = datum.get("measurement")
        if measurement:
            measurement_list.append(decode_measurement(measurement))

        state = datum.get("state")
        if state:
            state_list.append(decode_state(state))

    encoder_1_posisitions = [datum.encoder_1_pos for datum in measurement_list]
    measurement_times = [datum.header.timestamp.microseconds for datum in measurement_list]
    plt.scatter(measurement_times, encoder_1_posisitions)


    joint_1_positions = [datum.joint_1_position_rad for datum in state_list]
    state_times = [datum.header.timestamp.microseconds for datum in state_list]
    plt.scatter(state_times, joint_1_positions)

    plt.show()
         

def setup():
    parser = argparse.ArgumentParser(
        prog="PlotState",
        description="Plots state data from a log file",
    )
    parser.add_argument("log_file", help="The file with the data to plot.")
    parser.add_argument(
        "--log",
        default="warning",
        choices=["debug", "info", "warning", "error", "critical"],
        dest="loglevel",
    )

    args = parser.parse_args()

    numeric_level = getattr(logging, args.loglevel.upper(), None)
    if not isinstance(numeric_level, int):
        raise ValueError("Invalid log level: {level}".format(level=args.loglevel))
    logging.basicConfig(level=numeric_level)

    return args

if __name__ == "__main__":
    main()
