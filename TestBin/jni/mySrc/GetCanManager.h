#include "math.h"
//#include "comdef.h"
#include "comdef.h"

class GetCanManager{
public:
	static int getIntByBits(BYTE data, int bit, int len){
		if (bit > 7 || len > 8){
			return 0;
		}
		short bb = ((short)(data&0xFF));
		return ((bb>>bit)&((int)(pow(2, len)) - 1 ));
	}
};
