#include "play.hpp"

Play::Play(RGBDRIClient &client, std::string const& filename, std::string const& stream_endpoint):
client{client},
filename{filename},
loop{false},
number_rgbd_sensors{4},
compressed{true},
stream_endpoint{stream_endpoint},
ctx{},
skt{},
req_inited{false},
m_logger{spdlog::get("console")},
is_running{false},
backchannel_endpoint{}
{
  ctx = std::make_shared<zmq::context_t>(4);
  m_logger->debug("Stream endpoint {0:s}", this->stream_endpoint);
  if(this->stream_endpoint != "self"){
    auto endpoint = split(this->stream_endpoint,':');
    m_logger->debug(endpoint[1]);
    auto port = std::stoi(endpoint[1]);
    auto new_port = port + 1;
    this->backchannel_endpoint = endpoint[0] + ":" + std::to_string(new_port);
    m_logger->debug(this->backchannel_endpoint);
  }
};

Play::Play(RGBDRIClient &client, std::string const& filename, std::string const& stream_endpoint, std::string const& backchannel_endpoint):
client{client},
filename{filename},
loop{false},
number_rgbd_sensors{4},
compressed{true},
stream_endpoint{stream_endpoint},
ctx{},
skt{},
req_inited{false},
m_logger{spdlog::get("console")},
is_running{false},
backchannel_endpoint{backchannel_endpoint}
{
  ctx = std::make_shared<zmq::context_t>(4);
  m_logger->debug("Stream endpoint {0:s}", stream_endpoint);
  if(stream_endpoint != "self"){
    auto endpoint = split(stream_endpoint,':');
    m_logger->debug(endpoint[1]);
    auto port = std::stoi(endpoint[1]);
    auto new_port = port + 1;
    this->backchannel_endpoint = endpoint[0] + ":" + std::to_string(new_port);
    m_logger->debug(backchannel_endpoint);
  }
};

Play::Play(std::string const& filename, std::string const& stream_endpoint):
client{},
filename{filename},
loop{false},
number_rgbd_sensors{4},
compressed{true},
stream_endpoint{stream_endpoint},
ctx{},
skt{},
req_inited{false},
m_logger{spdlog::get("console")},
is_running{false},
backchannel_endpoint{}
{
  ctx = std::make_shared<zmq::context_t>(4);
  m_logger->debug(stream_endpoint);
  if(stream_endpoint != "self"){
    auto endpoint = split(stream_endpoint,':');
    m_logger->debug(endpoint[1]);
    auto port = std::stoi(endpoint[1]);
    auto new_port = port + 1;
    backchannel_endpoint = endpoint[0] + ":" + std::to_string(new_port);
    m_logger->debug(backchannel_endpoint);
  }
};

Play::Play(std::string const& filename,
            bool loop,
            int number_rgbd_sensors,
            int max_fps,
            bool compressed,
            int start_frame,
            int end_frame,
            std::string const& stream_endpoint):
            client{},
            filename{filename},
            loop{loop},
            number_rgbd_sensors{number_rgbd_sensors},
            max_fps{max_fps},
            compressed{compressed},
            start_frame{start_frame},
            end_frame{end_frame},
            stream_endpoint{stream_endpoint},
            ctx{},
            skt{},
            req_inited{false},
            m_logger{spdlog::get("console")},
            is_running{false},
            backchannel_endpoint{}{
              ctx = std::make_shared<zmq::context_t>(4);
              m_logger->debug(stream_endpoint);
              if(stream_endpoint != "self"){
                auto endpoint = split(stream_endpoint,':');
                m_logger->debug(endpoint[1]);
                auto port = std::stoi(endpoint[1]);
                auto new_port = port + 1;
                backchannel_endpoint = endpoint[0] + ":" + std::to_string(new_port);
                m_logger->debug(backchannel_endpoint);
              }

};

Play::Play(std::string const& filename,
            bool loop,
            int number_rgbd_sensors,
            int max_fps,
            bool compressed,
            int start_frame,
            int end_frame,
            std::string const& backchannel_endpoint,
            std::string const& stream_endpoint):
            client{},
            filename{filename},
            loop{loop},
            number_rgbd_sensors{number_rgbd_sensors},
            max_fps{max_fps},
            compressed{compressed},
            start_frame{start_frame},
            end_frame{end_frame},
            stream_endpoint{stream_endpoint},
            ctx{},
            skt{},
            req_inited{false},
            m_logger{spdlog::get("console")},
            is_running{false},
            backchannel_endpoint{backchannel_endpoint}{
              ctx = std::make_shared<zmq::context_t>(4);
};

Play::~Play(){
  m_logger->debug("destructor {0:s}", filename);
  m_logger->debug("destructor {0:b}", is_running);
  if(is_running){
    stop();
  }
}

void Play::init_req(){
  if(!req_inited){
    skt = std::make_shared<zmq::socket_t>(*ctx.get(), ZMQ_REQ);
    req_inited = true;
  }
}

void Play::init_rep(){
  m_logger->debug("[START] void Play::init_rep()");
  skt = std::make_shared<zmq::socket_t>(*ctx.get(), ZMQ_REP);
  m_logger->debug("backchannel_endpoint:{0:s}", backchannel_endpoint);
  skt->bind("tcp://" + backchannel_endpoint);

  while(is_running){
    m_logger->debug("backchannel_endpoint:{0:s}", backchannel_endpoint);
    zmq::message_t message;
    auto request = srecv(*skt.get());

    if(request[0] == "STOP"){
      m_logger->debug("STOP");
      ssend(*skt.get(), "STOPED");
      is_running = false;
    }
    if(request[0] == "PAUSE"){
      m_logger->debug("PAUSE");
      ssend(*skt.get(), "PAUSED");
      is_paused = true;
    }
    if(request[0] == "RESUME"){
      m_logger->debug("RESUME");
      ssend(*skt.get(), "RESUMED");
      is_paused = false;
    }
  }

  m_logger->debug("backchannel_endpoint:{0:s}", backchannel_endpoint);

  skt->unbind("tcp://" + backchannel_endpoint);
  m_logger->debug("[END] void Play::init_rep()");
}

void Play::execute(){
  m_logger->debug("[START] void Play::execute()");
  is_running = true;
  auto rep_thread = std::thread(&Play::init_rep,this);
  rep_thread.detach();

  const unsigned colorsize = compressed ? 691200 : 1280 * 1080 * 3;
  const unsigned depthsize = 512 * 424 * sizeof(float);
  const unsigned framesize = (colorsize + depthsize) * number_rgbd_sensors;
  double frametime = 0;
  double last_frame_time = 0;
  FileBuffer* fb = nullptr;
  size_t framecounter = 0;
  size_t num_frames = 0;

  zmq::socket_t  socket(*ctx.get(), ZMQ_PUB);
  uint32_t hwm = 1;
  socket.setsockopt(ZMQ_SNDHWM,&hwm, sizeof(hwm));
  std::string endpoint("tcp://" + stream_endpoint);
  socket.bind(endpoint.c_str());

  if(fb != nullptr){
    fb->close();
    delete fb;
    fb = nullptr;
  }

  fb = new FileBuffer(filename.c_str());
  if(!fb->open("r", 0)){
    m_logger->critical("error opening {0:s} exiting...",filename);
    exit(0);
  }
  fb->setLooping(loop);

  framecounter = 0;

  num_frames = fb->getFileSizeBytes()/framesize;

  while (is_running) {
    if(!is_paused){
      zmq::message_t zmqm(framesize);
      fb->read((unsigned char*) zmqm.data(), framesize);
      memcpy((char*) &frametime, (const char*) zmqm.data(), sizeof(double));

      const double elapsed_frame_time = frametime - last_frame_time;
      last_frame_time = frametime;
      const unsigned sleep_time = std::min(100u, std::max(0u, (unsigned)((elapsed_frame_time) * 1000u)));
      if(framecounter > 1){
          std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }

      socket.send(zmqm);
      ++framecounter;
      if(framecounter >= num_frames){
        if(loop){
          m_logger->debug("loop: restart stream");
          framecounter = 0;
        }
        else{
          m_logger->debug("stop play since end reached");
          is_running = false;
        }
      }
    }
  }

  m_logger->debug("[END] void Play::execute()");
};

void Play::start(){
  //Wrap command as GenericMessage
  auto msg = GenericMessage();
  msg.type = 0; //TODO: think about type handling
  m_logger->debug("start");
  msg.payload = to_string();
  m_logger->debug(msg.payload);
  //Send command to server
  client.send(msg.to_string());

  m_logger->debug("Send request");

  auto reply = client.recv();
  m_logger->debug("Received reply");
  auto reply_msg = GenericMessage::from_string(reply.back());
  switch (reply_msg.type) {
    case 15:{
      m_logger->debug(reply_msg.payload);
      Play::from_string(*this, reply_msg.payload);
      // stream_endpoint = cmd.stream_endpoint;
      // backchannel_endpoint = cmd.backchannel_endpoint;
      // is_running = cmd.is_running;
      // is_paused = cmd.is_paused;
      // m_logger->debug("Play on endpoint: {0:s}", cmd.stream_endpoint);
      break;
    }
    case 1:{
      m_logger->warn("Received non valid command");
      break;
    }
  }
};
bool Play::is_playing(){
  init_req();
  skt->connect("tcp://" + backchannel_endpoint);
  m_logger->debug(backchannel_endpoint);
  ssend(*skt.get(),"IS_RUNNING");
  auto rep = srecv(*skt.get());

  skt->disconnect("tcp://" + backchannel_endpoint);

  return to_bool(rep.front());
};
void Play::play_as_loop(){
  loop = true;
  start();
  loop = false;
};

void Play::stop(){
  init_req();
  m_logger->debug("[START] void Play::stop()");
  skt->connect("tcp://" + backchannel_endpoint);
  m_logger->debug("Connected");
  ssend(*skt.get(),"STOP");
  m_logger->debug("Send");
  srecv(*skt.get());
  m_logger->debug("Recv");

  skt->disconnect("tcp://" + backchannel_endpoint);
  m_logger->debug("[END] void Play::stop()");
};

void Play::pause(){
  init_req();
  m_logger->debug("[START] void Play::pause()");
  skt->connect("tcp://" + backchannel_endpoint);


  ssend(*skt.get(),"PAUSE");
  srecv(*skt.get());

  skt->disconnect("tcp://" + backchannel_endpoint);
  m_logger->debug("[END] void Play::pause()");
};

void Play::resume(){
  init_req();
  m_logger->debug("[START] void Play::resume()");
  skt->connect("tcp://" + backchannel_endpoint);

  ssend(*skt.get(),"RESUME");
  srecv(*skt.get());

  skt->disconnect("tcp://" + backchannel_endpoint);
  m_logger->debug("[END] void Play::resume()");
};

std::string Play::to_string(){
  std::string output;

  output += filename + "$";
  output += std::to_string(loop) + "$";
  output += std::to_string(number_rgbd_sensors) + "$";
  output += std::to_string(max_fps) + "$";
  output += std::to_string(compressed) + "$";
  output += std::to_string(start_frame) + "$";
  output += std::to_string(end_frame) + "$";
  output += std::to_string(is_running) + "$";
  output += std::to_string(is_paused) + "$";
  output += backchannel_endpoint + "$";
  output += stream_endpoint + "$";

  return output;
};

Play Play::from_string(std::string const& play_string){
  std::cout << "from string start" << std::endl;
  std::cout << play_string << std::endl;
  auto parts = split(play_string, '$');
  auto cmd = Play(
    parts[0] + "ich bin fake",
    to_bool(parts[1]),
    std::stoi(parts[2]),
    std::stoi(parts[3]),
    to_bool(parts[4]),
    std::stoi(parts[5]),
    std::stoi(parts[6]),
    parts[9],
    parts[10]
  );
  cmd.is_running = to_bool(parts[7]);
  cmd.is_paused = to_bool(parts[8]);
  std::cout << "from string end" << std::endl;
  return cmd;
};

void Play::from_string(Play &play,std::string const& play_string){
  std::cout << "from string start" << std::endl;
  std::cout << play_string << std::endl;
  auto parts = split(play_string, '$');
  play.filename = parts[0];
  play.loop  = to_bool(parts[1]);
  play.number_rgbd_sensors  = std::stoi(parts[2]);
  play.max_fps  = std::stoi(parts[3]);
  play.compressed  = to_bool(parts[4]);
  play.start_frame  = std::stoi(parts[5]);
  play.end_frame  = std::stoi(parts[6]);
  play.is_running  = to_bool(parts[7]);
  play.is_paused  = to_bool(parts[8]);
  play.backchannel_endpoint  = parts[9];
  play.stream_endpoint  = parts[10];

  std::cout << "from string end" << std::endl;
};
