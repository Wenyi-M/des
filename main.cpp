#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "des.h"

using namespace std ;

const int num = 88 ;

void help(const string & str)
{
	string header("DES Manual      MaWenyi") ;
	string command("Command : des option srcfile tarfile keyword") ;
	string options("Options :") ;
	string e("-e : encryption the srcfile with keyword , the result is stored in tarfile") ;
	string d("-d : decryption the srcfile with keyword , the result is stored in tarfile") ;
	string help("-h : show this manual") ;

	for(size_t i = 0 ; i < num - 1 ; ++i)
		cout << '*' ;
	cout << endl ;

	for(size_t i = 0 ; i < num ; ++i)
	{
		if(i == 0 || i == num - 1)
			cout << '*' ;
		else if(i == num / 2 - 3)
		{
			cout << header ;
			i += header.size() ;
		}
		else cout << ' ' ;
	}
	cout << endl ;
	for(size_t i = 0 ; i < num ; ++i)
	{
		if(i == 0 || i == num - 1)
			cout << '*' ;
		else if(i == 3)
		{
			cout << command ;
			i += command.size() ;
		}
		else cout << ' ' ;
	}
	cout << endl ;
	for(size_t i = 0 ; i < num ; ++i)
	{
		if(i == 0 || i == num - 1)
			cout << '*' ;
		else if(i == 3)
		{
			cout << options ;
			i += options.size() ;
		}
		else cout << ' ' ;
	}
	cout << endl ;

	for(size_t i = 0 ; i < num ; ++i)
	{
		if(i == 0 || i == num - 1)
			cout << '*' ;
		else if(i == 3)
		{
			cout << e ;
			i += e.size() ;
		}
		else cout << ' ' ;
	}
	cout << endl ;

	for(size_t i = 0 ; i < num ; ++i)
	{
		if(i == 0 || i == num - 1)
			cout << '*' ;
		else if(i == 3)
		{
			cout << d ;
			i += d.size() ;
		}
		else cout << ' ' ;
	}
	cout << endl ;

	for(size_t i = 0 ; i < num ; ++i)
	{
		if(i == 0 || i == num - 1)
			cout << '*' ;
		else if(i == 3)
		{
			cout << help ;
			i += help.size() ;
		}
		else cout << ' ' ;
	}
	cout << endl ;
	
	for(size_t i = 0 ; i < num - 1 ; ++i)
		cout << '*' ;
	cout << endl ;
	
	cout << str << endl ;

	exit(-1) ;//退出
}

void StrFromBlock(char * str , const Block & block)
{
	memset(str , 0 , 8) ;//将8个字节全部置0
	for(size_t i = 0 ; i < block.size() ; ++i)
	{
		if(true == block[i])//第i位为1
			*((unsigned char *)(str) + i / 8) |= (1 << (7 - i % 8)) ;
	}
}

void BlockFromStr(Block & block , const char * str)
{
	for(size_t i = 0 ; i < block.size() ; ++i)
	{
		if(0 != (*((unsigned char *)(str) + i / 8) & (1 << (7 - i % 8))))
			block[i] = true ;
		else 	block[i] = false ;
	}	
}

int main(int argc , char * argv[])
{
	if(argc < 2 || argv[1][0] != '-')
		help("Command Args Error") ;//输入参数错误，打印帮助文件然后退出
	
	Method method ;//记录运算方式（加密/解密）
	switch(argv[1][1])
	{
		case 'e'://加密
			method = e ;
			break ;
		case 'd'://加密
			method = d ;
			break ;
		case 'h'://打印帮助文件
			help("") ;
			break ;
		default:
			help("Command Args Error") ;
			break ;
	}
	if(argc < 5 || strlen(argv[4]) < 8)
		help("Command Args Error") ;//输入参数错误，打印帮助文件然后退出

	ifstream srcFile(argv[2]) ;//输入文件
	ofstream tarFile(argv[3]) ;//输出文件
	if(!srcFile || !tarFile) help("File Open Error") ;//文件打开失败
	
	Block block , bkey ;//数据块和密钥
	BlockFromStr(bkey , argv[4]) ;//获取密钥
	char buffer[8] ;
	while(1)
	{
		memset(buffer , 0 , 8) ;//将8个字节置0
		srcFile.read(buffer , 8) ;//从源中读取数据
		if(srcFile.eof()) break ;
		BlockFromStr(block , buffer) ;//构建数据块
		des(block , bkey , method) ;
		StrFromBlock(buffer , block) ;//获取运算后的数据
		tarFile.write(buffer , 8) ;//写入目标文件
	}
	srcFile.close() ;
	tarFile.close() ;
	
	return 0 ;
}
