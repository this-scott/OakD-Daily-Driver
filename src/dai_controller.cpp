#include <memory>
// #include <opencv2/opencv.hpp> ~ included from example
#include <fstream>
#include <depthai/depthai.hpp>

//keeping this extremely simple. Get the camera image, pump it to the stream.
int dai_run(const char *path) {
  // Create camera device
  // Shared ptr automatically destroys itself when it has no more references. In this case when the function ends
  std::shared_ptr<dai::Device> device = std::make_shared<dai::Device>();

  // Create Pipeline
  dai::Pipeline pipeline(device);

  //Create camera node
  auto cam = pipeline.create<dai::node::Camera>() -> build(dai::CameraBoardSocket::CAM_A);
  
  // Creating the camera stream. DAI auto-outputs to 420p
  std::shared_ptr<dai::MessageQueue> videoQueue = cam->requestOutput({1920,1080}, dai::ImgFrame::Type::YUV420p, dai::ImgResizeMode::STRETCH,30)->createOutputQueue(8,false);

  pipeline.start();
  
  // Create the output stream object
  std::ofstream outfile(path, std::ios::binary);

  while (true) {
    //get image frame
    std::shared_ptr<dai::ImgFrame> videoIn=videoQueue->get<dai::ImgFrame>();
    if (videoIn == nullptr)
      continue;

    //auto is creating a copy of the object
    auto data = videoIn->getData();

    std::cout << "printing frame\n";

    //reinterpret cast converts data into a char* for the yuv420p stream
    outfile.write(reinterpret_cast<const char*>(data.data()), data.size());
    // commenting these to say what existed. TODO: Safe exit function
//    cv::imshow("vid", videoIn->getCvFrame());

//    if (cv::waitKey(1)=='q'){
//      break;
//    }
  }
  return 0;
}
