/*
 * Test.cpp
 *
 *  Created on: 2017-11-8
 *      Author: YC2
 */
#include "comdef.h"
#include "cJSON.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include <dlfcn.h>

typedef int (*pFullSetCanData)(int moduleId, unsigned char* buffer, int length);
typedef int (*pSetCanData)(int moduleId, int index, int length, int what);
typedef int (*pGetFullCanData)(int moduleId, unsigned char* buffer, int length);
//测试动态加载SenCan
int testSendCan(){

	void* lib = dlopen("/system/lib/libSendCan.so", RTLD_LAZY);
	if (lib == NULL){
		LOGI("load lib err");
		return 0;
	}

	pFullSetCanData FullSetCanData = (pFullSetCanData)dlsym(lib, "FullSetCanData");
	pSetCanData SetCanData = (pSetCanData)dlsym(lib, "SetCanData");
	pGetFullCanData GetFullCanData = (pGetFullCanData)dlsym(lib, "GetFullCanData");

	BYTE buffer[11]  = {0x01, 0x02, 0x03, 0x04, 0x05};

	FullSetCanData(0x2F9, buffer, 8);
	SetCanData(0x2F8, 12, 12, 0xff);
	SetCanData(0x2F8, 20, 2, 0xff);

	GetFullCanData(0x2F8, buffer, 11);
	char ch1[256] = {0};
				sprintf(ch1, "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,",
						buffer[0], buffer[1],buffer[2],buffer[3],buffer[4],
						buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],
						buffer[10]);
		TestLog("buffer is:%s", ch1);

	GetFullCanData(0x2F9, buffer, 11);

	char ch[256] = {0};
			sprintf(ch, "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,",
					buffer[0], buffer[1],buffer[2],buffer[3],buffer[4],
					buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],
					buffer[10]);
	TestLog("buffer is:%s", ch);

	dlclose(lib);
	return 0;
}

//测试cjson
/**
 * 1、对象用“{}”包含
 * 2、对象内容为key/val形式（可多个，每个之前通过“，”隔开）
 * 3、val值可以为对象、数组、基本类型（Number、String）
 * 4、数组以“[]”表示，其值为val(可多个，每个之前通过“，”隔开)
 */
int testJson(){

	//创建一个根对象
	cJSON* root = cJSON_CreateObject();
	//添加key/val对
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("yc"));
	cJSON_AddItemToObject(root, "age", cJSON_CreateNumber(27));

	cJSON* scoreArray;
	cJSON_AddItemToObject(root, "score", scoreArray = cJSON_CreateArray());
	cJSON* scoreObj;
	cJSON_AddItemToArray(scoreArray, scoreObj = cJSON_CreateObject());
	cJSON_AddItemToObject(scoreObj, "math", cJSON_CreateNumber(97));
	cJSON_AddItemToObject(scoreObj, "english", cJSON_CreateNumber(87));
	cJSON_AddItemToObject(scoreObj, "chinese", cJSON_CreateNumber(90));

	cJSON* familyObj;
	cJSON_AddItemToArray(scoreArray, familyObj = cJSON_CreateObject());
	cJSON_AddItemToObject(familyObj, "father", cJSON_CreateString("ri"));
	cJSON_AddItemToObject(familyObj, "mather", cJSON_CreateString("chun"));
	cJSON_AddItemToObject(familyObj, "brother", cJSON_CreateString("bin"));

	cJSON_AddItemToArray(scoreArray, cJSON_CreateString("erzhong"));
	cJSON_AddItemToArray(scoreArray, cJSON_CreateNumber(2010));


	char* json_data = NULL;
	LOGI("create json data:%s\n",json_data = cJSON_Print(root));

	cJSON* json = cJSON_Parse(json_data);
	cJSON* parserObj = NULL;
	parserObj = cJSON_GetObjectItem(json, "name");
	if (parserObj != NULL){
		LOGI("has name Object");
	}
	else{
		LOGI("no has name Object");
	}
	if (1 == cJSON_HasObjectItem(json, "age")){
		LOGI("has age Object");
	}
	else{
		LOGI("no has age Object");
	}
	parserObj = cJSON_GetObjectItem(json, "score");
	if (parserObj != NULL){
		LOGI("has score Object");
		if (parserObj->type == cJSON_Array){
			int size = cJSON_GetArraySize(parserObj);
			LOGI("has score Object, is Array,Array size = %d", size);
			cJSON* scoreObj = NULL;
			//for循环
			for (int i = 0; i < size; i++){
				scoreObj = cJSON_GetArrayItem(parserObj, i);
				if (cJSON_IsString(scoreObj)){
					LOGI("for arrayItem is String, item value = %s", scoreObj->valuestring);
				}
				else if (cJSON_IsNumber(scoreObj)){
					LOGI("for arrayItem is Number, item value = %d", scoreObj->valueint);
				}
				else if (cJSON_IsObject(scoreObj)){
					LOGI("for arrayItem is Object");
					//遍历Objces
					cJSON* item = scoreObj->child;
					while(item != NULL){
						char* key = item->string;
						if (key != NULL){
							cJSON* val = cJSON_GetObjectItem(scoreObj, key);
							if (val != NULL){
								if (cJSON_IsString(val)){
									LOGI("for arrayItem key = %s, val = %s", (key != NULL) ? key: "null", val->string);
								}
								else if (cJSON_IsNumber(val)){
									LOGI("for arrayItem key = %s, val = %d", (key != NULL) ? key: "null", val->valueint);
								}
								else{
									LOGI("for arrayItem key = %s, val = other", (key != NULL) ? key: "null");
								}
							}
						}
						item = item->next;
					}
				}
			}
			//ForEach循环
			cJSON_ArrayForEach(scoreObj, parserObj){
				if (cJSON_IsString(scoreObj)){
					LOGI("ArrayForEach is String, item value = %s", scoreObj->valuestring);
				}
				else if (cJSON_IsNumber(scoreObj)){
					LOGI("ArrayForEach is Number, item value = %d", scoreObj->valueint);
				}
				else if (cJSON_IsObject(scoreObj)){
					LOGI("ArrayForEach is Object");
					//遍历Objces
					cJSON* item = scoreObj->child;
					while(item != NULL){
						char* key = item->string;
						if (key != NULL){
							cJSON* val = cJSON_GetObjectItem(scoreObj, key);
							if (val != NULL){
								if (cJSON_IsString(val)){
									LOGI("for arrayItem key = %s, val = %s", (key != NULL) ? key: "null", val->string);
								}
								else if (cJSON_IsNumber(val)){
									LOGI("for arrayItem key = %s, val = %d", (key != NULL) ? key: "null", val->valueint);
								}
								else{
									LOGI("for arrayItem key = %s, val = other", (key != NULL) ? key: "null");
								}
							}
						}
						item = item->next;
					}
				}
			}
		}
	}
	else{
		LOGI("no has score Object");
	}
	cJSON_Delete(json);
	//cJSON_Print()生成的字符串要free掉
	free(json_data);

	//删除根据对象
	cJSON_Delete(root);
	return 0;
}

#ifdef __cplusplus
}
#endif

