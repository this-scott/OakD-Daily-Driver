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

Aug 9(decided on the 2nd but never documented): Abandoning the v4l2 kernal/userspace approach in favor of a loopback device which I can pump video into
- Kernal userspace video driver needs more documentation

[v4l2loopback](https://github.com/v4l2loopback/v4l2loopback) device creation components

[] ~Create loopback device as /dev/videoX in [loopback controller](src/v4l2_controller.cpp)~ (Replaced by modprobe startup config)
[x] Pipe video into it via the [depthai controller](src/dai_controller.cpp)
[x] Create a build script for 1 time setup

Test run command
modprobe v4l2loopback video_nr=<N> card_label="Oak-D Camera" width=1920 height=1080

Currently using ofstream to stream bytes but that can't set the file type. Abandoning ofstream in favor of `open(path, O_RDWR)` so I can set the stream data type and figure out how to send a stream through this
