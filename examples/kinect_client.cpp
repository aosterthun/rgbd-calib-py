#include <KinectDaemon.hpp>

int main(int argc, char** argv){


	std::shared_ptr<KinectDaemon> _capturesystem_charon = std::make_shared<KinectDaemon>("141.54.147.108" /*server socket*/, /* this is temp*/ "141.54.147.106");

	auto pupil_record = _capturesystem_charon->record();
	sleep(5);
	pupil_record->stop();
	sleep(1);
	auto play_pupil  = _capturesystem_charon->play(pupil_record->filename()); //loop on internally negotiated socket
	//auto play_pupil = _capturesystem_charon->play("/home/mejo6715/Hiwi/kinect_recordings/rgbdri_rec_2.stream");
	sleep(5);
	play_pupil->stop();

	while(true)
	{

	}

	return 0;
}
