from math import sin, cos, pi

step = (2*pi)/15
yRotation = pi/4
xRotation = pi/4
a = 9
b = 12
centerx = 0
centerz = 0

for i in range(0,15):
    x = centerx + a * cos(yRotation) * cos(i*step) - b * sin(yRotation) * sin(i*step) * cos(xRotation)
    y = b * sin(i*step) * sin(xRotation)
    z = centerz + a * sin(yRotation) * cos(i*step) + b * cos(yRotation) * sin(i*step) * cos(xRotation)
    print('<point x="' + str(x) + '" y="' + str(y) + '" z="' + str(z) + '"/>')
