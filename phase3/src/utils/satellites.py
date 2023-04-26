from math import sin, cos, pi

step = (2*pi)/15
a = 24.23
b = 4/3 * a
c = b
beta = pi/3

for i in range(0,15):
    x = a * cos(i * step) * cos(beta)
    y = b * cos(i * step) * sin(beta)
    z = c * sin(i * step)
    print('<point x="' + str(x) + '" y="' + str(y) +  '" z="' + str(z) + '"/>')