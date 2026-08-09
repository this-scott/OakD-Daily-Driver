# OakDDaily Driver
Personal project to setup my oakd camera as a daily use webcam instead of using it for it's actual purpose

Feels like a good starter 

Building this out of the [depthai-core-example](https://github.com/luxonis/depthai-core-example)
Build commands are the same so far 
```
cmake -Bbuild -S. -DCMAKE_PREFIX_PATH=/path/to/install/dir //create Build files in ./build, use . as Source, (optional)dependency path
cmake --build build --parallel 4 //build build path, use 4 files at a time
```

Aug 2: The current plan is to create a device which wraps depthai controls and interacts with [v4l2](https://www.kernel.org/doc/html/v4.9/media/kapi/v4l2-dev.html)

Aug 9(decided on the 2nd but never documented): Abandoning the udev/v4l2 kernal approach in favor of a loopback device which I can pump video into
- Kernal userspace video driver needs more documentation

[] Create loopback device as /dev/videoX in [loopback controller](src/v4l2_controller.cpp)
[] Pipe video into it via the [depthai controller](src/dai_controller.cpp)
