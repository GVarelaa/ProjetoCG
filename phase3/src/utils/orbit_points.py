from math import sin, cos, pi

step = (2*pi)/15
a = 8.44
b = 6.33
c = 5
beta = 0

for i in range(0,15):
    x = a * cos(i * step) * cos(beta)
    y = c * sin(i * step)
    z = b * cos(i * step) * sin(beta)
    print('<point x="' + str(x) + '" y="' + str(z) +  '" z="' + str(y) + '"/>')