
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
 * curl����http������õĻص��������ص������жԷ��ص�json��ʽ��body�����˽������������������result��
 * @param ���������libcurl���ĵ�
 * @return ����ֵ�����libcurl���ĵ�
 */
static size_t callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    // ��ȡ����body�����ptr�У��Ƚ���ת��Ϊstring��ʽ
    std::string s((char *) ptr, size * nmemb);
    // ��ʼ��ȡjson�е�access token��Ŀ
    Json::Reader reader;
    Json::Value root;
    // ʹ��boost�����json
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
 * ���Ի�ȡaccess_token�ĺ�����ʹ��ʱ��Ҫ���ڰٶ��ƿ���̨������Ӧ���ܵ�Ӧ�ã���ö�Ӧ��API Key��Secret Key
 * @param access_token ��ȡ�õ���access token�����ú���ʱ�贫��ò���
 * @param AK Ӧ�õ�API key
 * @param SK Ӧ�õ�Secret key
 * @return ����0�����ȡaccess token�ɹ�����������ֵ�����ȡʧ��
 */
int get_access_token(std::string &access_token, const std::string &AK, const std::string &SK) {
    CURL *curl;
    CURLcode result_code;
    int error_code = -1;
    curl = curl_easy_init();//curl_easy_init������ʼ��һ��CURL��ָ��(��Щ�񷵻�FILE���͵�ָ��һ��).
    if (curl) {
        std::string url = access_token_url + "&client_id=" + AK + "&client_secret=" + SK;
		//������curl��.��������ε���Ϊ
        curl_easy_setopt(curl, CURLOPT_URL, url.data());//CURLOPT_URL���÷���URL
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        std::string access_token_result;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &access_token_result);//��������libcurl���յ����ݺ󱻵��ã���˺����������ݱ���Ĺ��ܣ��紦�������ļ���
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);//CURLOPT_WRITEDATA ���ڱ���CURLOPT_WRITEFUNCTION�����е�streamָ�����Դ��
        result_code = curl_easy_perform(curl);//���������õ�option ��������
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