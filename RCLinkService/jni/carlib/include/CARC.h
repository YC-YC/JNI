#include <string.h>
#include <stdlib.h>

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

/*=========内部接口函数==================*/
void CARC_Init(void);
void CARC_5msTask(void);
void CARC_10msTask(void);
/*=========内部接口函数 完==================*/


/*ty 2016 04 19 新结构体定义*/

typedef union
{
	u16 CARC_BtInfo[4];
	struct
	{
		u16 CARC_BT_INIT_STATUS	 :1;
		u16 CARC_BT_AUDIO_STATUS :2;
		u16 CARC_BT_CALL_STATUS	 :2;
		u16 CARC_BT_SPP_STATUS	 :2;
		u16 CARC_BT_BLE_STATUS 	 :2;
		u16 					 :7;
		u16 CARC_BT_MAC_ADDRESS1 :16;
		u16 CARC_BT_MAC_ADDRESS2 :16;
		u16 CARC_BT_MAC_ADDRESS3 :16;

	}s;
}CARC_BtInfo_Typedef;

typedef enum
{
	CARC_RADIO_OFF = (u8)0x0,
	CARC_RADIO_FM_MODE = (u8)0x1,
	CARC_RADIO_AM_MODE = (u8)0x2,
	CARC_RADIO_BUSY = (u8)0x3
}CARC_RadioStatus_Typedef;


typedef union
{
	u16 CARC_RadioInfo;
	struct
		{
			u16 CARC_RADIO_BAND	:1;
			u16 CARC_RADIO_FREQ :15;
		}s;
}CARC_RadioInfo_Typedef;

typedef union 
{
	u8 CARC_KEYVALUE;
	struct
	{
		u8 CARC_KEY_MODE 		:1;
		u8 CARC_KEY_SEEKUP 		:1;
		u8 CARC_KEY_SEEKDOWN 	:1;
		u8 CARC_KEY_CALLUP 		:1;
		u8 CARC_KEY_HANGUP		:1;
		u8  					:1;
		u8  					:1;
		u8 						:1;
	}s;
}CARC_KEY_Typedef;

typedef struct
{
	CARC_KEY_Typedef		i_KeyValue;
	CARC_BtInfo_Typedef		i_BtStatus;
	CARC_RadioStatus_Typedef  i_RadioStatus;
	CARC_RadioInfo_Typedef  i_RadioCurrenFreq;
	u8 						i_AppModeCtrl;
	u8						i_VoiceSourceChange;
}CARC_InputMsg_Typedef;



typedef struct
{
	u16	Id;
	u8	Dlc;
	u8	Data[8];
}CARC_Can_StdMsg_Typedef;

typedef struct
{
	u8 o_RadioCtrl;
	u8 o_Rc_ConnectStatus;
	CARC_RadioInfo_Typedef o_RadioCtrlFreq;
	u8 o_AudioCtrl;
	u8 o_Sleeped;
	u8 o_AppModeCtrl;
}CARC_OutPutMsg_Typedef;
/*ty 2016 04 19 新结构体定义 完*/

extern CARC_OutPutMsg_Typedef CARC_Out;
extern CARC_InputMsg_Typedef CARC_In;

/*=========外部接口函数==================*/
//extern u8 CARC_GetRadioList(u8 MaxDlc,CARC_RadioInfo_Typedef *pList);//获取收音机搜索列表
//extern u16 CARC_GetBtMsg(u8 *pData); //获取一包数据
//extern bool CARC_PutBtMsg(u8 *pData,u16 pLength);//发送一包数据
//extern u8 CARC_GetCanMsg(CARC_Can_StdMsg_Typedef *pMsg);//获取can信息
/*=========外部接口函数 完==================*/

