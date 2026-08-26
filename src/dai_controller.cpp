#include <memory>
#include <opencv2/opencv.hpp>

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
  auto videoQueue = cam->requestOutput({1920,1080}, dai::ImgFrame::Type::BGR888p, dai::ImgResizeMode::STRETCH,30)->createOutputQueue();

  pipeline.start();

  while (true) {
    auto videoIn=videoQueue->get<dai::ImgFrame>();
    if (videoIn == nullptr)
      continue;

    cv::imshow("vid", videoIn->getCvFrame());

    if (cv::waitKey(1)=='q'){
      break;
    }
  }
  return 0;
}
