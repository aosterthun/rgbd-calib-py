#include <KinectDaemon.hpp>

int main(int argc, char** argv){
	
	std::shared_ptr<KinectDaemon> _daemon = std::make_shared<KinectDaemon>("141.54.147.32");

	return 0;
}
