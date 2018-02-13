
#include<iostream>  
#include<cstring>  
#include<cctype>  
#include <curl/curl.h>
#include <json/json.h>
//#include "access_token.h"
#include "include/main.h"
#include "include/access_token.h"

using namespace std;  
const std::string access_token_url = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials";
/**
 * curl发送http请求调用的回调函数，回调函数中对返回的json格式的body进行了解析，解析结果储存在result中
 * @param 参数定义见libcurl库文档
 * @return 返回值定义见libcurl库文档
 */
static size_t callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    // 获取到的body存放在ptr中，先将其转换为string格式
    std::string s((char *) ptr, size * nmemb);
    // 开始获取json中的access token项目
    Json::Reader reader;
    Json::Value root;
    // 使用boost库解析json
    if( !reader.parse(s,root) ){
		std::cout << "parse fail"<< endl;  
	}else{
		std::cout <<"refresh_token = " <<root["refresh_token"].asString()<< endl;  
		std::cout <<"expires_in = "<< root["expires_in"].asInt()<< endl;
		std::cout <<"scope = "<< root["scope"].asString()<< endl;		
		std::cout <<"session_key = "<< root["session_key"].asString()<< endl;
		std::cout <<"access_token = "<< root["access_token"].asString()<< endl;  
		std::cout <<"session_secret = "<< root["session_secret"].asString()<< endl;  
		
		std::cout <<"error = "<< root["error"].asString()<< endl;  
		std::cout <<"error_description = "<< root["error_description"].asString()<< endl;  
	}
    std::string* access_token_result = static_cast<std::string*>(stream);
    *access_token_result = root["access_token"].asString();
    return size * nmemb;
}

/**
 * 用以获取access_token的函数，使用时需要先在百度云控制台申请相应功能的应用，获得对应的API Key和Secret Key
 * @param access_token 获取得到的access token，调用函数时需传入该参数
 * @param AK 应用的API key
 * @param SK 应用的Secret key
 * @return 返回0代表获取access token成功，其他返回值代表获取失败
 */
int get_access_token(std::string &access_token, const std::string &AK, const std::string &SK) {
    CURL *curl;
    CURLcode result_code;
    int error_code = -1;
    curl = curl_easy_init();//curl_easy_init用来初始化一个CURL的指针(有些像返回FILE类型的指针一样).
    if (curl) {
        std::string url = access_token_url + "&client_id=" + AK + "&client_secret=" + SK;
		//它告诉curl库.程序将有如何的行为
        curl_easy_setopt(curl, CURLOPT_URL, url.data());//CURLOPT_URL设置访问URL
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        std::string access_token_result;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &access_token_result);//函数将在libcurl接收到数据后被调用，因此函数多做数据保存的功能，如处理下载文件。
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);//CURLOPT_WRITEDATA 用于表明CURLOPT_WRITEFUNCTION函数中的stream指针的来源。
        result_code = curl_easy_perform(curl);//让我们设置的option 运作起来
        if (result_code != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result_code));
            return 1;
        }
        access_token = access_token_result;
        curl_easy_cleanup(curl);
		fprintf(stderr, "curl_easy_init() sus.");
        error_code = 0;
    } else {
        fprintf(stderr, "curl_easy_init() failed.");
        error_code = 1;
    }
    return error_code;
}