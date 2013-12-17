#ifndef __USER_DATA__
#define __USER_DATA__
#include "curl/curl.h"
#include "AniReader.hpp"
class UserData{
public :
	static UserData *current;
	char server[20];
	char username[20];
	char passwd[20];
	int userid;
	int face;
	int rank;
	int coinNum;
	int emotion;
	static int httpAns;
	int item[30];
	bool itemSelect[30];
	int buddylist[40];
	void fetchBasicData();
	void fetchExtraData();
	void regist();
	void login();
	void checkName();
	UserData();
	static size_t writehtml(uint8_t* ptr,size_t size,size_t number,void *stream);
};
UserData *UserData::current=new UserData;
int UserData::httpAns;
UserData::UserData(){
	coinNum=100;
	memset(item, 0, sizeof(item));
	memset(itemSelect, 0, sizeof(itemSelect));
}
void UserData::fetchExtraData(){
	this->coinNum=999;
}
void UserData::fetchBasicData(){
	this->face=2;
	this->rank=19;
	this->emotion=3;
}
void UserData::checkName(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/check.jsp",server);
		CCLog("%s!",url);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s",username);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
	if(res!=0){
		httpAns=-404;
	}
	else
	    userid=httpAns;
    curl_easy_cleanup(curl);
}
void UserData::login(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/login.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s&password=%s",username,passwd);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
    if(httpAns!=-1 and httpAns!=-404){
    	UserData::userid=httpAns;
    	fetchBasicData();
    	fetchExtraData();
    }
}
void UserData::regist(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/regist.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s&password=%s",username,passwd);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
}
size_t UserData::writehtml(uint8_t* ptr,size_t size,size_t number,void *stream){
	char ans[4];
	ans[0]=*(ptr+12);	ans[1]=*(ptr+13);	ans[2]=*(ptr+14);	ans[3]=*(ptr+15);
	sscanf(ans,"%d",&UserData::httpAns);
	return size*number;
}
#endif
