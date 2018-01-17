#include <KinectDaemon.hpp>

int main(int argc, char** argv){
	
	std::shared_ptr<KinectDaemon> _capturesystem_charon = std::make_shared<KinectDaemon>("141.54.147.108" /*server socket*/, /* this is temp*/ "141.54.147.106");


	auto teacher_play = _capturesystem_charon->play("/home/mejo6715/Hiwi/kinect_recordings/user_andre.stream"); //loop on internally negotiated socket

	//system("/opt/kinect-resources/rgbd-framework/rgbd-recon/install/bin/kinect_client " + teacher_play->filename() + " " + teacher_play->socket() + "&");

	sleep(5);
	teacher_play->send_on_backchannel(102);
	sleep(5);
	teacher_play->send_on_backchannel(103);
	//user input for start record
	/*
	auto pupil_record = _capturesystem_charon->record();
	sleep(5);
	//user input for end record
	pupil_record->stop();
	sleep(5);
	auto pupil_record2 = _capturesystem_charon->record("pupil_record2.ks","10" /*seconds); //abs or rel ?
	/*while(!pupil_record2->is_finished())
	{
		std::cout << "Dance!!!" << std::endl;
	}
	teacher_stream->stop();

	auto play_pupil  = _capturesystem_charon->play(pupil_record->filename()); //loop on internally negotiated socket
	auto play_pupil2 = _capturesystem_charon->play(pupil_record2->filename(), false); //no loop on internally negotiated socket


	system("/opt/kinect-resources/rgbd-framework/rgbd-recon/install/bin/kinect_client " + pupil_record->filename() + " " + play_pupil->socket() + "&");
	system("/opt/kinect-resources/rgbd-framework/rgbd-recon/install/bin/kinect_client " + pupil_record2->filename() + " " + play_pupil2->socket() + "&");

	sleep(10);



	while(true)
	{

	}*/
	


	return 0;
}
