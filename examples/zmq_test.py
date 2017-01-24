import pykinecting

import time
kinect_service = pykinecting.KinectService("127.0.0.1:7008")
time.sleep(3)
kinect_service.play("1A","../../../recordings/steppo_standing/steppo_standing.stream")
