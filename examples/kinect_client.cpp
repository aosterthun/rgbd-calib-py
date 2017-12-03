#include <KinectDaemon.hpp>

int main(int argc, char** argv){
	
	std::shared_ptr<KinectDaemon> _daemon = std::make_shared<KinectDaemon>("192.168.188.105");
	while(true){
		sleep(1);
		_daemon->play("test_file");
	}	
	return 0;
}
