import csv
import os
import fcntl

# path to the file
file = "BSP/Simulator/Hardware/Data/UART.csv"


def write(msg):
    """ Writes the message to UART_2
    Doesn't return anything
    """

    # Creates file if it doesn't exist
    os.makedirs(os.path.dirname(file), exist_ok=True)
    if not os.path.exists(file):
        with open(file, 'w'):
            pass
    
    lines = []
    # Grab the current UART data
    with open(file, "r") as csv:
        fcntl.flock(csv.fileno(), fcntl.LOCK_EX)
        lines = csv.readlines()

    # If the file hasn't been initialzed yet, set the two entries to empty
    length = len(lines)
    if length < 2:
        for i in range(length,2):
            lines.append('\n')
    
    # Write back the UART data, modifying the specified one
    with open(file, "w") as csv:
        for (i, line) in enumerate(lines):
            if i == 1:
                csv.write(msg)
                csv.write('\n')
            else:
                csv.write(line)

        fcntl.flock(csv.fileno(), fcntl.LOCK_UN)