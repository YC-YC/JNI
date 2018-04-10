/*
 * TestSpyFile.cpp
 *
 *  Created on: 2018-4-9
 *      Author: YC2
 */
#include <sys/poll.h>
#include <fcntl.h>
#include <linux/input.h>
#include "comdef.h"
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * poll监听字符设备
 */
void testPollFile(){
	LOGI("testPollFile");
	LOGI("appversion = 2018041001");
	const char *device_path = "/dev/input/event0";
//	const char *device_path = "/dev/input/test_file";
	struct pollfd *ufds;
	int nfds = 1;
	int fd = open(device_path, O_RDONLY);
	if (fd > 0){
		ufds = (pollfd*)calloc(nfds, sizeof(ufds[0]));
		ufds[0].fd = fd;
		ufds[0].events = POLLIN;
		struct input_event event;
		for (;;){
			int ret = poll(ufds, nfds, 5*1000);
			if (ret > 0){
//				LOGI("had event:%d\n", ufds[0].revents);
				if (ufds[0].revents & POLLIN){
//					char data = 0;
//					ret = read(ufds[0].fd, &data, sizeof(char));
//					if (ret > 0){
//						LOGI("poll read data: %d\n", data);
////						ftruncate(ufds[0].fd, 0);
//					}
					ret = read(ufds[0].fd, &event, sizeof(input_event));
					if (ret > 0){
						LOGI("poll read data [%8ld.%06ld]: %x %x %x\n", event.time.tv_sec, event.time.tv_usec, event.type, event.code, event.value);
					}
					else{
						LOGI("no data\n");
					}

				}
			}
			else{
				LOGI("no data,timeout\n");
			}
		}
		close(fd);
	}
}

#ifdef __cplusplus
}
#endif
