#
#
# Quick script to send serial commands with sweeping in steer
#
# 1 April 2016
# Michel Fathallah
# 


import serial, time

ser = serial.Serial('/dev/cu.usbmodem1421', 115200)  # open first serial port
print ser.portstr       # check which port was really used

# Definie value limits
maxSteer = 174
minSteer = 78
normSteer = 127

# maxThrust = 169
# minThrust = 70

stepSize = 1

# Set initial
steer = minSteer
direction = 1 # 1 is increasing, 0 is decreasing

while (1):

	# increasing
	if (direction == 1):
		steer = steer + stepSize
		if (steer >= maxSteer): 	# change direction to down if reached max
			direction = 0

	# decreasing
	elif (direction == 0):
		steer = steer - stepSize
		if (steer <= minSteer): 	# change direction to up if reached min
			direction = 1

	steerStr = str(steer)

	# if less than 100, then add 1 zero - if less than 10, then add another zero
	if (steer < 100):
		steerStr = '0' + steerStr
		if (steer < 10):
			steerStr = '0' + steerStr

	print steerStr + '0' + str(minSteer) + '\0'

	# ser.write( '0' + str(minSteer) + steerStr + '\0' )
	ser.write( steerStr + '0' + str(minThrust) + '\0' )

	time.sleep(0.01) # 10ms
