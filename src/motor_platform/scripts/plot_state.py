import argparse
import json
import logging

import matplotlib.pyplot as plt

from motor_platform.types.input import Input
from motor_platform.types.measurement import Measurement
from motor_platform.types.state import State
from motor_platform.visualization import plots


# TODO: Set up tests, set up formatting 
def main():
    args = setup()
    logging.info("Starting...")

    messages = []
    with open(args.log_file, "r") as file_in:
        messages = json.load(file_in)

    input_list = []
    measurement_list = []
    state_list = []

    # TODO: It might be a good idea to have a single message type get published from the hardware
    for message in messages:
        for key, val in message.items():
            if key == "input":
                input_list.append(Input.decode(val))

            if key == "measurement":
                measurement_list.append(Measurement.decode(val))

            if key == "state":
                state_list.append(State.decode(val))

    reference_errors = [
        datum.joint_2_position_rad - datum.joint_1_position_rad for datum in state_list
    ]
    state_times = [datum.header.timestamp.microseconds for datum in state_list]

    _, axes = plt.subplots(4, 1)

    plots.scatter_attribute(state_list, "joint_1_position_rad", axes[0])
    plots.scatter_attribute(state_list, "joint_2_position_rad", axes[0])
    axes[1].scatter(state_times, reference_errors)
    plots.scatter_attribute(input_list, "voltage", axes[2])
    plots.scatter_attribute(measurement_list, "encoder_1_pos", axes[3])

    if args.visualize:
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
    parser.add_argument("--visualize", action="store_true", dest="visualize")

    args = parser.parse_args()

    numeric_level = getattr(logging, args.loglevel.upper(), None)
    if not isinstance(numeric_level, int):
        raise ValueError("Invalid log level: {level}".format(level=args.loglevel))
    logging.basicConfig(level=numeric_level)

    return args


if __name__ == "__main__":
    main()
