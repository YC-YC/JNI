
/*
 * SerialPort.cpp
 *
 *  Created on: 2016-3-17
 *      Author: YC
 */

#include <termios.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <jni.h>

#include <android/log.h>

#define UART_DEBUG			1
#define TESTAP_DBG_USAGE	(1 << 0)
#define TESTAP_DBG_ERR		(1 << 1)
#define TESTAP_DBG_FLOW		(1 << 2)
#define TESTAP_DBG_FRAME	(1 << 3)
#define TESTAP_DBG_BW	    (1 << 4)

#define LOG_TAG "C_JNI"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define TestAp_Printf(flag, msg...)  ((flag)?LOGI(msg):flag)

#define RESULT_SUCCESS 0

static speed_t getBaudrate(jint baudrate) {
    switch (baudrate) {
    case 0:
        return B0;
    case 50:
        return B50;
    case 75:
        return B75;
    case 110:
        return B110;
    case 134:
        return B134;
    case 150:
        return B150;
    case 200:
        return B200;
    case 300:
        return B300;
    case 600:
        return B600;
    case 1200:
        return B1200;
    case 1800:
        return B1800;
    case 2400:
        return B2400;
    case 4800:
        return B4800;
    case 9600:
        return B9600;
    case 19200:
        return B19200;
    case 38400:
        return B38400;
    case 57600:
        return B57600;
    case 115200:
        return B115200;
    case 230400:
        return B230400;
    case 460800:
        return B460800;
    case 500000:
        return B500000;
    case 576000:
        return B576000;
    case 921600:
        return B921600;
    case 1000000:
        return B1000000;
    case 1152000:
        return B1152000;
    case 1500000:
        return B1500000;
    case 2000000:
        return B2000000;
    case 2500000:
        return B2500000;
    case 3000000:
        return B3000000;
    case 3500000:
        return B3500000;
    case 4000000:
        return B4000000;
    default:
        return -1;
    }
}

JNIEXPORT jobject JNICALL uart_open
  (JNIEnv *env, jobject thiz, jstring path, jint baudrate)
{
	int fd;
	speed_t speed;
	jobject mFileDescriptor;

	LOGD("init native Check arguments");
	/* Check arguments */
	{
		speed = getBaudrate(baudrate);
		if (speed == -1)
		{
			LOGD("Invalid baudrate");
			return NULL;
		}
	}

	LOGD("init native Opening device!");
	/* Opening device */
	{
		jboolean iscopy;
		const char *path_utf = env->GetStringUTFChars(path, &iscopy);
		LOGD("Opening serial port %s", path_utf);
		//      fd = open(path_utf, O_RDWR | O_DIRECT | O_SYNC);
		fd = open(path_utf, O_RDWR | O_NOCTTY | O_NONBLOCK | O_NDELAY);
		LOGD("open() fd = %d", fd);
		env->ReleaseStringUTFChars(path, path_utf);
		if (fd == -1)
		{
			LOGD("Cannot open port %d", baudrate);
			return NULL;
		}
	}

	LOGD("init native Configure device!");
	/* Configure device */
	{
		struct termios cfg;
		if (tcgetattr(fd, &cfg))
		{
			LOGD("Configure device tcgetattr() failed 1");
			close(fd);
			return NULL;
		}

		cfmakeraw(&cfg);
		cfsetispeed(&cfg, speed);
		cfsetospeed(&cfg, speed);

		if (tcsetattr(fd, TCSANOW, &cfg))
		{
			LOGD("Configure device tcsetattr() failed 2");
			close(fd);
			return NULL;
		}
	}

	/* Create a corresponding file descriptor */
	{
		jclass cFileDescriptor = env->FindClass("java/io/FileDescriptor");
		jmethodID iFileDescriptor = env->GetMethodID(cFileDescriptor, "<init>","()V");
		jfieldID descriptorID = env->GetFieldID(cFileDescriptor, "descriptor","I");
		mFileDescriptor = env->NewObject(cFileDescriptor, iFileDescriptor);
		env->SetIntField(mFileDescriptor, descriptorID, (jint) fd);
	}
	return mFileDescriptor;
}

JNIEXPORT jint JNICALL uart_close
  (JNIEnv *env, jobject thiz)
{
	jclass SerialPortClass = env->GetObjectClass(thiz);
	jclass FileDescriptorClass = env->FindClass("java/io/FileDescriptor");
	jfieldID mFdID = env->GetFieldID(SerialPortClass, "mFd", "Ljava/io/FileDescriptor;");
	jfieldID descriptorID = env->GetFieldID(FileDescriptorClass, "descriptor", "I");
	jobject mFd = env->GetObjectField(thiz, mFdID);
	jint descriptor = env->GetIntField(mFd, descriptorID);
	LOGD("close(fd = %d)", descriptor);
	close(descriptor);
	return 1;
}

JNIEXPORT jint JNICALL IOCtl
  (JNIEnv *env, jclass clazz, jstring path, jint type, jint val){
	jboolean iscopy;
	const char *path_utf = env->GetStringUTFChars(path, &iscopy);
	int fd = 0;
	if ((fd = open(path_utf, O_RDWR))){
		if (ioctl(fd, type, &val) == RESULT_SUCCESS){
			LOGD("successfully val = %d", val);
		}
		else{
			LOGD("unsuccessfully");
		}
		close(fd);
	}else{
		val = -1;
		LOGD("can't open %s", path_utf);
	}

	env->ReleaseStringUTFChars(path, path_utf);
	return val;
}

/*
 * TODO 方法对应表
 * {Java方法，方法签名(参数+返回值)，本地对应方法}
 */
const JNINativeMethod g_methods[] = {
		{"open", "(Ljava/lang/String;I)Ljava/io/FileDescriptor;", (void*)uart_open},
		{"close", "()I", (void*)uart_close},
		{"IOCtl", "(Ljava/lang/String;II)I", (void*)IOCtl}
};

/*
 * 加载so时回调
 */
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	LOGD("OnLoad Start\r\n");
	JNIEnv * env = NULL;
	jclass cls = NULL;
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK)
	{
		LOGD("OnLoad GetEnv Err\r\n");
		return JNI_ERR;
	}
	cls = env->FindClass("com/yc/javacallc/Connection");
	if (cls == NULL)
	{
		LOGD("FindClass Err\r\n");
		return JNI_ERR;
	}

	//注册JNI方法
	env->RegisterNatives(cls, g_methods, sizeof(g_methods) / sizeof(g_methods[0]));
	LOGD("OnLoad Success\r\n");
	return JNI_VERSION_1_6;
}

//卸载so时回调
JNIEXPORT void JNI_ONUnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv * env = NULL;
	jclass cls = NULL;
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK)
	{
		LOGD("JNI_ONUnLoad GetEnv Err\r\n");
		return;
	}
	cls = env->FindClass("com/yc/javacallc/Connection");
	if (cls == NULL)
	{
		LOGD("FindClass Err\r\n");
		return;
	}
	env->UnregisterNatives(cls);
}
