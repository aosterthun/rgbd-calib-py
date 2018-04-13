import sys
import time
import pyrgbdcalib

if __name__ == '__main__':
    rgbd = pyrgbdcalib.RGBDRIClient("127.0.0.1","127.0.0.1")
    live = pyrgbdcalib.Play(rgbd,"/opt/kinect-resources/rgbd-framework/rgbd-daemon/kinect_recordings/user_andre.stream", "127.0.0.1:9000")
    live.start()

    while True:
        pass
    # while(True):
    #     record = pyrgbdcalib.Record(rgbd,"/tmp/record.stream", live.stream_endpoint)
    #     record.start()
    #     time.sleep(10)
    #     record.stop()
    #
    #     play = pyrgbdcalib.Play(rgbd,record.filename, "127.0.0.1:9002")
    #     play.start()
    #     time.sleep(10)
    #     play.pause()
    #     time.sleep(10)
    #     play.resume()
    #     time.sleep(10)
    #     play.stop()
