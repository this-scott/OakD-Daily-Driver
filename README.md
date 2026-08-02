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

need to learn how to communicate with udev

udev appending rules:
[] Find consistent flag to trigger process with
