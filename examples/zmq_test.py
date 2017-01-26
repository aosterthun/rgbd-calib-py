import pykinecting
import sys
import time


if __name__ == "__main__":

	if sys.argv[1] == "-h":
		usage_str = "[Usage] " + sys.argv[0] + " \n<kinect_daemon_serverport> play <user_id> <filename>\n"
		usage_str += "play_frames <user_id> <filename> <startframe> <endframe> <loop> \n"
		usage_str += "record <user_id> <filename> <serverport> <num_cameras> <duration_in_secs> <is_compressed> \n"
		usage_str += "record_play <user_id> <filepath_src> <startframe> <endframe> <filepath_dest> <num_cameras>"

		print(usage_str)
	else:
		kinect_service = pykinecting.KinectService(sys.argv[1])

		if sys.argv[2] == "play":
			kinect_service.play(sys.argv[3],sys.argv[4])
		elif sys.argv[2] == "play_frames": 
			kinect_service.play_frames(sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7])
		elif sys.argv[2] == "record":
			kinect_service.record(sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7])
		elif sys.argv[2] == "record_play":
			kinect_service.record_play(sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7])