if __name__ == "__main__":

	if sys.argv[1] == "-h":
		usage_str = "[Usage] " + sys.argv[0] + " \n<kinect_daemon_serverport> play <user_id> <filename> <is_compressed> <serverport> <num_cameras>\n"
		usage_str += "play_frames <user_id> <filename> <startframe> <endframe> <loop> \n"
		usage_str += "record <user_id> <filename> <serverport> <num_cameras> <duration_in_secs> <is_compressed> \n"
		usage_str += "record_play <user_id> <filepath_src> <startframe> <endframe> <filepath_dest> <num_cameras>"

		print(usage_str)
	else:
		kinect_service = pykinecting.KinectService("141.54.147.108","141.54.147.106")
		record_handle = kinect_service.record()
		
		record_handle.stop()
		kinect_service.play(record_handle.filename())


