#include <linux/types.h>
#include <linux/v4l2loopback.h>

// going to build this as one device because I don't have ir or audio on an oakd S2. Eventually I'll register a seperate camera for one depth format

// Create loopback device. Return filepath?
int create_device() {
	v4l2_loopback_config config;

	return 0;
}
