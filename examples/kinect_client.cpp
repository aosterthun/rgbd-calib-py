#include <KinectDaemon.hpp>

int main(int argc, char** argv){
	
	std::shared_ptr<KinectDaemon> _capturesystem_charon = std::make_shared<KinectDaemon>("141.54.147.108","141.54.147.106");

	auto teacher_play = _capturesystem_charon->play("/mnt/pitoti/recording_session1/teacher.ks"); //loop
	sleep(3);
	teacher_play->send_on_backchannel(102);
	//user input for start record
	/*
	auto pupil_record = _capturesystem_charon->record();
	sleep(5);
	//user input for end record
	pupil_record->stop();
	sleep(5);
	auto pupil_record2 = _capturesystem_charon->record("pupil_record2.ks","10"); //abs or rel ?
	while(!pupil_record2->is_finished())
	{
		std::cout << "Dance!!!" << std::endl;
	}
	teacher_stream->stop();

	system("/opt/kinect-resources/rgbd-framework/rgbd-recon/install/bin/kinect_client " + pupil_record->filename() + "&");
	system("/opt/kinect-resources/rgbd-framework/rgbd-recon/install/bin/kinect_client " + pupil_record2->filename() + "&");

	sleep(10);

	_capturesystem_charon->play(pupil_record->filename()); //loop
	_capturesystem_charon->play(pupil_record2->filename(), false); //no loop


	while(true)
	{

	}*/
	


	return 0;
}
