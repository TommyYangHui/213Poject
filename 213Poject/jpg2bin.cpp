//#include "stdafx.h"  
#include <iostream>  
#include <fstream>  
//#include <io.h>  
  
using namespace std;  
  
int jpg2bin( void )  
{  
	char * buffer;  
	const char * filename = "photo/jpgbin.bin"; 
	long size;  
	ifstream in (filename, ios::in|ios::binary|ios::ate);  
	size = in.tellg();  
	in.seekg (0, ios::beg);  
	buffer = new char [size];  
	in.read (buffer, size);  
	in.close();  
	  
	cout << "the complete file is in a buffer="<<endl;
	cout <<buffer<<endl; 
	delete[] buffer;  
	return 0;  


	/* const char * filename = "a.txt"; 
	long l,m;  
	ifstream in(filename, ios::in|ios::binary);  
	l = in.tellg();  
	in.seekg (0, ios::end);  
	m = in.tellg();  
	in.close();  
	cout << "size of " << filename;  
	cout << " is " << (m-l) << " bytes.\n"<<endl;  
	return 0;   */

	

    /* string strpath = "H:\\windows_share_y\\face_213Poject\\213Poject\\photo\\jpgbin.bin";  
    //string strR1 = "D:\\Dtest5\\Readjpg\\10.jpg";  
  
    std::ifstream fin(strpath.c_str(), std::ios::binary);  
    fin.seekg(0, ios::end);  
    int iSize = fin.tellg();  //tellg()代表当前get 流指针的位置 (用tellg)
    char* szBuf = new (std::nothrow) char[iSize];  
  
    fin.seekg(0, ios::beg);  
    fin.read(szBuf, sizeof(char) * iSize);  
    fin.close();  
	
	cout << "iSize="<< iSize <<endl; 
	//cout << "szBuf[0]="<< szBuf[0] <<endl; 
	cout << "hello"<< endl;  */
   /*  std::ofstream fout(strR1.c_str(), std::ios::binary);  
    fout.write(szBuf, sizeof(char) * iSize);  
    fout.close();  */ 
  
    return 0;  
}  