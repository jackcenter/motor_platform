from datetime import datetime
from pathlib import Path
import serial
import signal
import sys

EXIT_FLAG = False

def main():
    signal.signal(signal.SIGINT, signal_handler)

    ser = serial.Serial('/dev/ttyACM0', 9600)

    log_filename = 'log_' + datetime.utcnow().strftime('%Y-%m-%d_%H-%M-%S')
    log_file = Path(__file__).parents[1] / 'log' / log_filename

    prefix = '['
    while not EXIT_FLAG:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            with open(log_file, 'a') as fout:
                fout.write(prefix)
                fout.write(line)
                prefix = ",\n"

    with open(log_file, 'a') as fout:
                fout.write("]\n")


def signal_handler(sig, frame):
    print('\nSystem Exit Requested')
    global EXIT_FLAG
    EXIT_FLAG = True
    

if __name__ == '__main__':
    main()
