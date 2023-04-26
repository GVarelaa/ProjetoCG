from math import sin, cos, pi

step = (2*pi)/15
a = 9
b = 12

for i in range(0,15):
    x = a * cos(i*step)
    y = b * sin(i*step)
    print('<point x="' + str(x) + '" y="0" z="' + str(y) + '"/>')