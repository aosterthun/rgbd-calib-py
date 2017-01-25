import pykinecting

import time
kinect_service = pykinecting.KinectService("127.0.0.1:7008")
#time.sleep(3)
#kinect_service.play("1A","opt/lel")
kinect_service.record("A1", "/mnt/project_avatars/daemon-record-test/test.stream", "141.54.147.33:7000", "4", "10", True)
