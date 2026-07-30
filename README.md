# OakDDaily Driver
Personal project to setup my oakd camera as a daily use webcam instead of using it for it's actual purpose

Feels like a good starter 

Building this out of the [depthai-core-example](https://github.com/luxonis/depthai-core-example)
Build commands are the same so far 
```
cmake -Bbuild -S. -DCMAKE_PREFIX_PATH=/path/to/install/dir //create Build files in ./build, use . as Source, (optional)dependency path
cmake --build build --parallel 4 //build build path, use 4 files at a time
```
need to learn how to communicate with udev
