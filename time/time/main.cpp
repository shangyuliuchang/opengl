#include <stdio.h>
#include<Windows.h>
#include <time.h>
int main()
{
	time_t t;
	tm * lt;
	while (true) {
		time(&t);//��ȡUnixʱ�����
		lt = localtime(&t);//תΪʱ��ṹ��
		printf("%d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);//������
		Sleep(1000);
	}
	return 0;
}