import pykinecting

import time
serv = pykinecting.KinectService("127.0.0.1:7008")
time.sleep(3)
serv.play("/opt/kinect-resources/rgbd-framework/recordings/actors/actors_localhost.ks")
