import numpy as np
import sys
import matplotlib.pyplot as plt

# Define points along x and y axes
x_data = [0.0, 1.0, 1.9, 3.0, 3.9,  5.0]
y_data = [1.0, 3.2, 5.0, 7.2, 9.3, 11.1]

# Set up A array and b array
A = np.array([[0.0, 1], [1.0, 1], [1.9, 1], [3.0, 1], [3.9, 1], [5.0, 1]])
b = np.array([[1.0], [3.2], [5.0], [7.2], [9.3], [11.1]])

## q = inv(ATA)*ATb
# Calculate inverse of ATA
AT = np.array(A.transpose())
ATA = AT.dot(A)
ATAi = np.linalg.inv(ATA)

# Calculate AT*b
ATb = AT.dot(b)

# Calculate ATAi*ATb
q = ATAi.dot(ATb)
print(q)

## q = [[m] [c]]     q contains slope and intercept
m = q[0][0]
c = q[1][0]
print("m:", m)
print("c:", c)

## y = mx + c
x = np.linspace(x_data[0], x_data[5], 100)
y = m*x + c

# Plot points with line of best fit
plt.plot(x, y, 'r', label='y=mx+c')
plt.scatter(x_data, y_data, c='black', marker='d')
plt.legend(loc='upper left')
plt.grid()
plt.show()
