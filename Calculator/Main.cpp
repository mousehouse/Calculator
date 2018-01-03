#include <iostream>
#include "ParseBuffer.h"	/* 对解析流类的定义 */
#include "FormularUnit.h"	/* 对方程单元类的定义 */
using namespace std;

int main(int argc, char** argv)
{
	char ss[1000];
	FormularUnit* u;

	// 输入算式
	cout << "> ";
	while( cin >> ss )
	{
		// 生成解析流
		ParseBuffer buffer(ss);

		try
		{
			// 从解析流中解析算式, 生成方程单元树
			u = FormularUnit::Parse(&buffer,0);

			// 检验解析流中是否有剩余
			if( !buffer.IsEOF() ) cout << "[unfull Parse]";

			// 输出结果
			cout << u->GetUnitValue() << endl;

			// 释放方程单元树
			FormularUnit::Release( u );
		}
		catch( WrongFormatException &e )
		{
			/* 格式错误异常 */
			cout << e.what() << endl;
		}
		cout << "> ";
	}
	return 0;
}