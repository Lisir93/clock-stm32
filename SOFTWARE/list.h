#ifndef __LIST_H__
#define __LIST_H__

#include <stdint.h>
#include "controls.h"

typedef enum
{
	List_Status_Invalid,
	List_Status_Ready,
	List_Status_Selected,
	List_Status_Hide,
}List_Status;

/*
	x ���ϽǺ�����(����)
	y ���Ͻ�������(����)
	sizex ˮƽ���(����)
	unity ÿ����Ŀ�ĸ߶�(����)
	quan ��Ŀ����(��)
	selected ����ʾ��������Ŀ��ѡ�еĵڼ�����Ŀ(��)
	string �ַ�������
	firstStr ����Ŀ�е�һ����ʾ���ַ������±�
	strQuan �ַ�������
*/
#define LIST_STRING_TOTAL 16
typedef struct
{
	uint8_t x;
	uint8_t y;
	uint8_t sizex;
	uint8_t unity;
	uint8_t quan;
	uint8_t selected;
	const char*string[LIST_STRING_TOTAL];
	uint8_t firstStr;
	uint8_t strQuan;
	List_Status status;
}List;

void List_Init(List*list);
void List_SetPosition(List*list,uint8_t x,uint8_t y);
void List_SetSize(List*list,uint8_t sizex,uint8_t unity);
void List_SetString(List*list,uint8_t n,const char*str);
void List_SetSelected(List*list,uint8_t sel);
void List_SetFirst(List*list,uint8_t fstr);
void List_SetQuan(List*list,uint8_t quan);
void List_SetStrQuan(List*list,uint8_t strquan);
void List_SetStatus(List*list,List_Status status);
void List_Show(List*list);
void List_Close(List*list,uint8_t refresh);
void List_MovSelected(List*list,uint8_t dir);
uint8_t List_GetNum(List*list);

#endif
