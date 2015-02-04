import roslib; #roslib.load_manifest('SUPERballUART')
import rospy
import serial
import numpy as np
from std_msgs.msg import Float64, Int32, UInt8

rospy.init_node("SUPERballUART")
pub_sg0 = rospy.Publisher('sg_data_0',Float64)
pub_sg0_1 = rospy.Publisher('sg_data_0_1',UInt8)
pub_sg0_2 = rospy.Publisher('sg_data_0_2',UInt8)
pub_sg0_3 = rospy.Publisher('sg_data_0_3',UInt8)

ser = serial.Serial('/dev/ttyUSB0',baudrate=500000) 
state = 0
while True:
	p = ord(ser.read())
	#print p
	if(state==0):
		if(p==0xFF):
			state = 1
			packet = []
			packet.append(p)
	elif(state==1):
		packet.append(p)
		state = 2
	elif(state==2):
		packet.append(p)
		state = 3
		plen = p
		if(plen==2):
			state=4
	elif(state==3):
		packet.append(p)
		#print len(packet)
		if(len(packet)>plen):
			state = 4
	elif(state==4):
		#check length
		cks = 0
		packet.append(p)
		for i in xrange(1,len(packet)-1):
			cks ^= packet[i]
		if(cks==p):
			if(not packet[1] in [2,] and not packet[3] in [13,14, 15] and not packet[2] in [7]):
				#print "packet: "
				print np.array(packet)
				m = (packet[3]<<16) | (packet[4]<<8) | (packet[5])
				
				f = 1.*m
				x = 3.*f/(16*2**23)-3./16
				#print x
				pub_sg0.publish(m/2.**15)
				pub_sg0_1.publish(packet[3])
				pub_sg0_2.publish(packet[4])
				pub_sg0_3.publish(packet[5])
		else:
			#print "CKS error"
			#print plen
			#print np.array(packet)
			#print cks
			pass
		state = 0


