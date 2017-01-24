import pykinecting

import time
recording = pykinecting.KinectService("127.0.0.1:7008")
time.sleep(3)
recording.record(0)
recording.play("Test")
