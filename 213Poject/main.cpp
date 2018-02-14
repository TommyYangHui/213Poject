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
	Json::Value result;

	std::string image;
	aip::get_file_content("photo/hansum.JPG", &image);
	// 如果有可选参数
	std::map<std::string, std::string> options;
	options["max_face_num"] = "2";
	options["face_fields"] = "age,beauty,expression,faceshape,gender,glasses,race,qualities";

	// 带参数调用人脸检测
	result = client.detect(image, options);
	
/* 	std::cout <<"error_msg = " <<result["error_msg"].asString()<< endl;  
	std::cout <<"error_code = "<< result["error_code"].asInt()<< endl;
	std::cout <<"result_num = "<< result["result_num"].asInt()<< endl; */
	
	
	Json::Reader reader;
	Json::FastWriter fwriter;
	Json::StyledWriter swriter;
//need add a condition :promise the result isn't null
/*	std::string _str = fwriter(result);
	std::ofstream ofs("example_fast_writer.json");
	ofs << _str;
	ofs.close();

	_str = swriter(result);
	ofs.open("example_styled_writer.json");
	ofs << _str;
	ofs.close();
	
*/
	std::cout << swriter.write(result) << std::endl;	
	
	
	
	
	
	//----------------------------------------
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


