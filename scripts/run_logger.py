from datetime import datetime
from pathlib import Path
import serial

def main():
    ser = serial.Serial('/dev/ttyACM0', 9600)

    log_filename = 'log_' + datetime.utcnow().strftime('%Y-%m-%d_%H:%M:%S')
    log_file = Path(__file__).parents[1] / 'log' / log_filename

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            with open(log_file, 'a') as fout:
                fout.write(line)

if __name__ == '__main__':
    main()
