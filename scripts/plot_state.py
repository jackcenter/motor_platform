import argparse
import json
import logging

import matplotlib.pyplot as plt


def main():
    args = setup()
    logging.info("Starting...")

    with open(args.log_file, 'r') as file_in:
        data = json.load(file_in)

    print(data)

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
