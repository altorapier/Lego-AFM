import serial
import numpy as np
import time
from matplotlib import pyplot as plt
# Serial setup
ser = serial.Serial('COM7', 9600)
time.sleep(2)

# Matrix setup
x_pos = np.arange(0,9,0.25)
y_pos = np.arange(0,6.4,0.25)
rows = len(x_pos)
cols = len(y_pos)
while True:
    matrix = np.zeros((rows, cols))
    plt.pcolormesh(np.flip(matrix,0))
    ##axes.set_aspect('equal')
    plt.show()
    # Iterate over the matrix in a snaking pattern
    for i in range(rows):
        if i % 2 == 0:  # Even rows: left-to-right
            col_range = range(cols)
        else:  # Odd rows: right-to-left
            col_range = np.flip(range(cols))
    
        for j in col_range:
            # Send command to Arduino
            print("x: "+str(i)+" y: "+str(j))
            x = x_pos[i]
            y = y_pos[j]
            print("x: "+str(x)+" y: "+str(y))
            cmd = f"MOVE {x} {y}\n" # divide by 10 to make it a float
            ser.write(cmd.encode())
            while True:
                if ser.in_waiting:
                    data = ser.readline().decode().strip()
                    if data == "READY":
                        break
            time.sleep(0.05)
    
            # Read data from Arduino
            while ser.in_waiting:
                data = ser.readline().decode().strip()
                if data:
                    try:
                        measurement = float(data)
                        matrix[i, j] = measurement
                        plt.pcolormesh(np.flip(matrix,0))
                        plt.gca().set_aspect('equal')
                        plt.clim(0.0,5.0)
                        plt.show()
                    except ValueError:
                        print(f"Received invalid data: {data}")
    
    x = 0.0
    y = 0.0
    print("x: "+str(x)+" y: "+str(y))
    cmd = f"MOVE {x} {y}\n" # divide by 10 to make it a float
    ser.write(cmd.encode())
# Close the serial connection
ser.close()

# Print the filled matrix
print(matrix)
plt.pcolormesh(np.flip(matrix,0))
#plt.figure(figsize = (1,1))
plt.show()