import pykinecting
import sys
import time

kinect_service = pykinecting.KinectService("127.0.0.1:8000")
user_id = sys.argv[1]

#kinect_service.play("1A","/tmp/macarena.stream")
#kinect_service.record("A1", "/mnt/project_avatars/daemon-record-test/instructor.stream", "141.54.147.33:7000", "4", "10", True)
kinect_service.record_play(user_id, "/tmp/macarena.stream", "40", "140",
    "/tmp/test" + user_id + ".stream", "4")
