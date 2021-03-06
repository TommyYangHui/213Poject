#include <iostream>
#include <curl/curl.h>
#include "include/main.h"
#include "include/face_detect.h"

using namespace std;  

// libcurl库下载链接：https://curl.haxx.se/download.html
// jsoncpp库下载链接：https://github.com/open-source-parsers/jsoncpp/
const static std::string request_url = "https://aip.baidubce.com/rest/2.0/face/v1/detect";
static std::string detect_result;
/**
 * curl发送http请求调用的回调函数，回调函数中对返回的json格式的body进行了解析，解析结果储存在全局的静态变量当中
 * @param 参数定义见libcurl文档
 * @return 返回值定义见libcurl文档
 */
static size_t callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    // 获取到的body存放在ptr中，先将其转换为string格式
    detect_result = std::string((char *) ptr, size * nmemb);
    return size * nmemb;
}
/**
 * 人脸探测
 * @return 调用成功返回0，发生错误返回其他错误码
 */
int detect(std::string &json_result, const std::string &access_token) {
    std::string url = request_url + "?access_token=" + access_token;
    CURL *curl = NULL;
    CURLcode result_code;
    int is_success = -1 ;
    curl = curl_easy_init();//curl_easy_init用来初始化一个CURL的指针(有些像返回FILE类型的指针一样).
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());//CURLOPT_URL设置访问URL
        curl_easy_setopt(curl, CURLOPT_POST, 1);
		//curl_formadd()函数用于在组建multipart/formdata HTTP POST时添加POST选项。一次添加一个POST选项，直至添加完你所有选项。
        curl_httppost *post = NULL;
        curl_httppost *last = NULL;
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "max_face_num", CURLFORM_COPYCONTENTS, "5", CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "face_fields", CURLFORM_COPYCONTENTS, "age,beauty,expression,faceshape,gender,glasses,landmark,race,qualities", CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "image", CURLFORM_COPYCONTENTS, "【base64_img】", CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
		//函数将在libcurl接收到数据后被调用，因此函数多做数据保存的功能，如处理下载文件。
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		//执行单条请求
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
			//curl_easy_strerror进行出错打印
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result_code));
            is_success = 1;
            return is_success;
        }
        json_result = detect_result;
		//这个调用用来结束一个会话.与curl_easy_init配合着用
        curl_easy_cleanup(curl);
        is_success = 0;
    } else {
        fprintf(stderr, "curl_easy_init() failed.");
        is_success = 1;
    }
    return is_success;
}
