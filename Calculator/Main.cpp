#include <iostream>
#include "ParseBuffer.h"	/* �Խ�������Ķ��� */
#include "FormularUnit.h"	/* �Է��̵�Ԫ��Ķ��� */
using namespace std;

int main(int argc, char** argv)
{
	char ss[1000];
	FormularUnit* u;

	// ������ʽ
	cout << "> ";
	while( cin >> ss )
	{
		// ���ɽ�����
		ParseBuffer buffer(ss);

		try
		{
			// �ӽ������н�����ʽ, ���ɷ��̵�Ԫ��
			u = FormularUnit::Parse(&buffer,0);

			// ������������Ƿ���ʣ��
			if( !buffer.IsEOF() ) cout << "[unfull Parse]";

			// ������
			cout << u->GetUnitValue() << endl;

			// �ͷŷ��̵�Ԫ��
			FormularUnit::Release( u );
		}
		catch( WrongFormatException &e )
		{
			/* ��ʽ�����쳣 */
			cout << e.what() << endl;
		}
		cout << "> ";
	}
	return 0;
}