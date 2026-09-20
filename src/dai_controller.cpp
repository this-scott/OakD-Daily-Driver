#include <memory>
#include <depthai/depthai.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h> //v4l2 format commands

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
  
  // Create the file (descriptor) object
  int fd = open(path, O_RDWR);
  // setting image format
  v4l2_format fmt{};
  fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
  fmt.fmt.pix.width = 1920;
  fmt.fmt.pix.height = 1080;
  fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;
  fmt.fmt.pix.sizeimage = 1920*1080*3/2;
  ioctl(fd, VIDIOC_S_FMT, &fmt);

  while (true) {
    //get image frame
    std::shared_ptr<dai::ImgFrame> videoIn=videoQueue->get<dai::ImgFrame>();
    if (videoIn == nullptr)
      continue;

    //auto is creating a copy of the object
    auto data = videoIn->getData();

    std::cout << "printing frame\n";
    
    //writing buffer to stream
    write(fd, data.data(), 1920*1080*3/2);
  }
  return 0;
}
