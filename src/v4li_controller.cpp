#include <linux/videodev2.h>

// going to build this as one device because I don't have ir or audio on an oakd S2. Eventually I'll register a seperate camera for one depth format

// the v4l2 device struct in 1.5 is built on top of video_device struct in section 1.4?
struct video_device vdev = video_device_alloc();
