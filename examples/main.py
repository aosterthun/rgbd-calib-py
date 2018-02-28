import sys
import time
import pyrgbdcalib

if __name__ == '__main__':
    daemon = pyrgbdcalib.KinectDaemon("141.54.147.101","141.54.147.108")
    recording = daemon.record("/tmp/test_rec.stream","141.54.147.101:7000",4)
    time.sleep(5)
    recording.stop()

    time.sleep(5)

    play_recording = daemon.play(recording.filename(),"141.54.147.101:7001",4)

    time.sleep(20)

    play_recording.stop()

    time.sleep(1)

