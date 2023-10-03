# Lego-AFM
Programs to run the PSI Lego AFM
Arduino:
Based on serial input, either receives x y position data from Python script and moves the motor to that spot or returns which of the six sensors in the array is the most illuminated.
Python:
tells the AFM to move to specific spots and then queries which detector receives the most light (1-6). The script then plots that value on an xy grid corresponding to the positions
