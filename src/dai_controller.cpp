#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <exception>

#include <depthai/depthai.hpp>
#include "dai_controller.hpp"
/* 
ironically this is exactly what I need for the core functionality
I just need to make it talk to Linux
*/
dai::Pipeline create_pipe() {

  // Create device
  std::shared_ptr<dai::Device> device = std::make_shared<dai::Device>();

  // Create pipeline
  dai::Pipeline pipeline(device);
  
  return pipeline;
  /*
  // Create nodes
  auto cam = pipeline.create<dai::node::Camera>()->build();:"

  auto videoQueue =
      cam->requestOutput(std::make_pair(1260, 720))->createOutputQueue();

  // Start pipeline
  pipeline.start();
  
  }
  catch (const std::exception& e) {
    std::count << "Exception Occurred: " <<  e.what() << std::endl;
  }
  
  while (true) {
    auto videoIn = videoQueue->get<dai::ImgFrame>();
    if (videoIn == nullptr)
      continue;

    cv::imshow("video", videoIn->getCvFrame());

    if (cv::waitKey(1) == 'q') {
      break;
    }
  }

  // returning video object of what was created
  return videoQueue;
  */
}
