#include <KinectDaemon.hpp>

int main(int argc, char** argv){
	
	std::shared_ptr<KinectDaemon> _daemon = std::make_shared<KinectDaemon>("127.0.0.1:8000");

	return 0;
}
