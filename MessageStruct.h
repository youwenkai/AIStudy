#ifndef _MessageStruct_H_
#define _MessageStruct_H_



struct Telegram
{
	//�������telegram��ʵ��
	int		Sender;
	//�������telegram��ʵ��
	int		Receiver;
	//��Ϣ�������ڵ�ö��ֵ�����ļ���"MessageTypes.h"
	int		Msg;
	//���Ա��������ͻ����ӳ�һ��ָ��������ʱ����͵���Ϣ
	//���һ���ӳ��Ǳ��룬��������ʱ�������ϢӦ���ڴ˺�ʱ��󱻷���
	double	DispatchTime;
	//�κ�Ӧ�ð�����Ϣ�Ķ�����Ϣ
	void*	ExtraInfo;
};




#endif