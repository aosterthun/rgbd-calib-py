import pyrgbdcalib

import time
recording = pyrgbdcalib.RemoteRecorder("127.0.0.1:7008", "stream01.stream")
time.sleep(3)
recording.record(0)
recording.play("Test")
