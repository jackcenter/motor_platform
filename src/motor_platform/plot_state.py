import argparse
import json
import logging

import matplotlib.pyplot as plt

import motor_platform.plots as plots
from motor_platform.types.input import Input
from motor_platform.types.measurement import Measurement
from motor_platform.types.state import State


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

    for message in messages:
        for key, val in message.items():
            if key == "input":
                input_list.append(Input.create_from_json(val))

            if key == "measurement":
                measurement_list.append(Measurement.create_from_json(val))

            if key == "state":
                state_list.append(State.create_from_json(val))

    reference_errors = [
        datum.joint_2_position_rad - datum.joint_1_position_rad for datum in state_list
    ]
    state_times = [datum.header.timestamp.microseconds for datum in state_list]

    _, axes = plt.subplots(3, 2, figsize=(8.5, 6))

    plots.scatter_attribute(state_list, "joint_1_position_rad", axes[0][0])
    plots.scatter_attribute(state_list, "joint_2_position_rad", axes[0][0])
    __set_axis_settings("Position [rad]", axes[0][0])

    axes[1][0].scatter(state_times, reference_errors, label="position_error_rad")
    __set_axis_settings("Error [rad]", axes[1][0])

    plots.scatter_attribute(input_list, "voltage", axes[2][0])
    __set_axis_settings("Input [volts]", axes[2][0])

    plots.scatter_attribute(measurement_list, "encoder_1_pos", axes[0][1])
    plots.scatter_attribute(measurement_list, "encoder_2_pos", axes[0][1])
    __set_axis_settings("Position [counts]", axes[0][1])

    plots.scatter_attribute(state_list, "joint_1_velocity_rps", axes[1][1])
    plots.scatter_attribute(state_list, "joint_2_velocity_rps", axes[1][1])
    __set_axis_settings("Velocity [rad / sec]", axes[1][1])

    axes[-1][0].set_xlabel("Time [sec]")
    axes[-1][1].set_xlabel("Time [sec]")

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


def __set_axis_settings(y_label: str, ax):
    ax.set_ylabel(y_label)
    ax.legend()
    ax.grid(visible=True, which="both")


if __name__ == "__main__":
    main()
