import sys
import time
import pyrgbdcalib

if __name__ == '__main__':
    daemon = pyrgbdcalib.KinectDaemon("141.54.147.108","141.54.147.106")

    recording = daemon.record("/home/mejo6715/Hiwi/kinect_recordings/rgbdri_rec_2.stream","141.54.147.108:7000")
    time.sleep(5)
    recording.stop()

    time.sleep(1)

    play = daemon.play(recording.filename(),recording.server())
    time.sleep(5)
    play.stop()
