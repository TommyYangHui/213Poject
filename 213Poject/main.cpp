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

extern int jpg2bin( void ) ;

// 回调函数获取到的access_token存放变量
static std::string access_token_result;
int main()  
{  
	int ret = -1;
	std::string detect_result;
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
	cout << "get_access_token ret =" << ret << endl;  
	
	
	//-------------------------------------
	// 带参数调用人脸检测
	{
	Json::Value result;

	std::string image;
	aip::get_file_content("photo/WZT_227552.JPG", &image);
	// 如果有可选参数
	std::map<std::string, std::string> options;
	options["max_face_num"] = "2";
	options["face_fields"] = "age,beauty,expression,faceshape,gender,glasses,race,qualities";

	
	result = client.detect(image, options);
	Json::StyledWriter swriter;
	//need add a condition :promise the result isn't null
	std::cout << swriter.write(result) << std::endl;	
	}
	//-------end------------------------------
	
	//-------------------------------------
	//face user add:
/* 	{
	Json::Value result_user_add;

	std::string uid = "gakki";

	std::string user_info = "100,200";

	std::string group_id = "group1,group2";

	std::string image_a;
	Json::StyledWriter swriter;
	
	aip::get_file_content("photo/gakki (2).jpg", &image_a);

	// 如果有可选参数
	std::map<std::string, std::string> options_a;
	options_a["action_type"] = "append";

	// 带参数调用人脸注册
	result_user_add = client.user_add(uid, user_info, group_id, image_a, options_a);
	std::cout << swriter.write(result_user_add) << std::endl;	
	} */
	//-------end---------------------------
	
	//--------------------------------------
	/* // 调用用户信息查询
	{
	Json::Value result_b;
	Json::StyledWriter swriter;
	result_b = client.user_get("YangHui", aip::null);
	std::cout << swriter.write(result_b) << std::endl;	
	
	// 调用用户信息查询
	Json::Value result_c;
	result_c = client.user_get("gakki", aip::null);
	std::cout << swriter.write(result_c) << std::endl;	
	} */
	//-------end---------------------------
	
	//--------------------------------------
	// face identify
	{
	Json::Value result;

	std::string group_id = "group1,group2";

	std::string image;
	Json::StyledWriter swriter;
	aip::get_file_content("photo/WZT_227552.JPG", &image);

	//调用人脸识别
	//result = client.identify(group_id, image, aip::null);

	//如果有可选参数
	std::map<std::string, std::string> options;
	options["ext_fields"] = "faceliveness";
	options["user_top_num"] = "3";

	//带参数调用人脸识别
	result = client.identify(group_id, image, options);
	std::cout << "face identify:" << std::endl;
	std::cout << swriter.write(result) << std::endl;	
	 }
	//-------end--------------------------- 
	
	//--------------------------------------
	// user info update:
	/* {	
	Json::Value result;

	std::string uid = "YangHui";

	std::string user_info = "99";

	std::string group_id = "group1,group2";

	std::string image;
	Json::StyledWriter swriter;
	aip::get_file_content("photo/WZT_227551.JPG", &image);


	// 如果有可选参数
	std::map<std::string, std::string> options;
	options["action_type"] = "replace";

	// 带参数调用人脸更新
	result = client.user_update(uid, user_info, group_id, image, options);
	std::cout << "face update:" << std::endl;
	std::cout << swriter.write(result) << std::endl;	
	} */
	//-------end---------------------------
	
	
	
	
	
	
	/* ret = detect( detect_result, access_token_result ); 
	cout << "detect ret =" << ret << endl;  
	
	Json::Reader reader;
    Json::Value root;
    // 使用boost库解析json
    if( !reader.parse(detect_result,root) ){
		std::cout << "parse fail"<< endl;  
	}else{
		std::cout <<"error_msg = " <<root["error_msg"].asString()<< endl;  
		std::cout <<"error_code = "<< root["error_code"].asInt()<< endl;
		std::cout <<"result_num = "<< root["result_num"].asInt()<< endl;		
		//std::cout <<"log_id = "<< root["log_id"].asInt()<< endl;
		
	}
	 */
	//jpg2bin( ) ;
    return 0;  
}  


