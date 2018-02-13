#include<iostream>  
#include<cstring>  
#include<cctype>  
#include <curl/curl.h>
#include <json/json.h>
//#include "access_token.h"
#include "face.h"
#include "include/main.h"
#include "include/access_token.h"
#include "include/face_detect.h"

// libcurl库下载链接：https://curl.haxx.se/download.html
// jsoncpp库下载链接：https://github.com/open-source-parsers/jsoncpp/
// 获取access_token所需要的url
using namespace std;  
 
std::string app_id = "10823071";
std::string api_key = "3qehLyYm8cZmiXG39w84gCUa";
std::string secret_key = "FadlKkhl6fcEL9YRdRKi4IP2IxcFtuoo"; 


// 回调函数获取到的access_token存放变量
static std::string access_token_result;
int main()  
{  
	int ret = -1;
    string str("some string");  
    // range for 语句  
    for(auto &c : str)  
    {  
        c = toupper(c);  
    }  
    cout << str << endl;  
	//face client bulid
	aip::Face client(app_id, api_key, secret_key);
	ret = get_access_token( access_token_result, api_key, secret_key);
	cout << ret << endl;  
    return 0;  
}  


