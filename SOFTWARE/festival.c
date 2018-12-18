#include <stdio.h>
#include "calendar.h"
#include "festival.h"

#define fest_putchar(__cout,__dat) do{*(__cout)++=(__dat);}while(0)
void fest_puts(char**cout,const char*dat){
	while(*dat){
		**cout=*dat++;
		(*cout)++;
	}
}

void Festival_PrintOldCalendar(char*cout,OldCalendar*oc){
	const char*tiangan="���ұ����켺�����ɹ�";
	const char*dizhi= "�ӳ���î������δ�����纥";
	const char*animal="��ţ������������Ｆ����";
	const char*number="��һ�����������߰˾�ʮ";
	uint16_t y=oc->year+36;
	fest_putchar(cout,tiangan[y%10*2+0]);
	fest_putchar(cout,tiangan[y%10*2+1]);
	fest_putchar(cout,dizhi[y%12*2+0]);
	fest_putchar(cout,dizhi[y%12*2+1]);
	fest_putchar(cout,animal[y%12*2+0]);
	fest_putchar(cout,animal[y%12*2+1]);
	fest_puts(&cout,"��");
	if(oc->mon>12){
		fest_puts(&cout,"��");
		oc->mon-=12;
	}
	if(oc->mon==1){
		fest_puts(&cout,"��");
	}else if(oc->mon>=2&&oc->mon<=10){
		fest_putchar(cout,number[oc->mon*2]);
		fest_putchar(cout,number[oc->mon*2+1]);
	}else if(oc->mon==11){
		fest_puts(&cout,"��");
	}else if(oc->mon==12){
		fest_puts(&cout,"��");
	}
	fest_puts(&cout,"��");
	if(oc->mday>=1&&oc->mday<=10){
		fest_puts(&cout,"��");
		fest_putchar(cout,number[oc->mday*2]);
		fest_putchar(cout,number[oc->mday*2+1]);
	}else if(oc->mday>=11&&oc->mday<=19){
		fest_puts(&cout,"ʮ");
		fest_putchar(cout,number[(oc->mday-10)*2]);
		fest_putchar(cout,number[(oc->mday-10)*2+1]);
	}else if(oc->mday==20){
		fest_puts(&cout,"��ʮ");
	}else if(oc->mday>=21&&oc->mday<=29){
		fest_puts(&cout,"إ");
		fest_putchar(cout,number[(oc->mday-20)*2]);
		fest_putchar(cout,number[(oc->mday-20)*2+1]);
	}else if(oc->mday==30){
		fest_puts(&cout,"��ʮ");
	}
	*cout=0;
}

typedef struct{
	const char*name;
	uint8_t mon;
	uint8_t mday;
}NewAnnualFestival;

typedef struct{
	const char*name;
	uint8_t mon;
	uint8_t mday;
}OldAnnualFestival;

typedef struct{
	const char**name;
	int (*judge)(NewCalendar*nc,OldCalendar*oc);
}AttributeFestival;

typedef struct{
	const char*name;
	uint8_t wday;
	uint8_t order;
	uint8_t mon;
}WeekbasedFestival;

typedef struct{
	const char*name;
	int (*judge)(NewCalendar*nc,OldCalendar*oc);
}SpecialFestival;

const NewAnnualFestival nafes[]={
	{"Ԫ��",1,1},
	{"���˽�",2,14},
	{"��Ů��",3,8},
	{"ֲ����",3,12},
	{"������Ȩ����",3,15},
	{"���˽�",4,1},
	{"���������",4,22},
	{"�Ͷ���",5,1},
	{"�����",5,4},
	{"��ʿ��",5,12},
	{"������",5,31},
	{"��ͯ��",6,1},
	{"������",6,26},
	{"������",7,1},
	{"������",8,1},
	{"����ʤ����",8,8},
	{"��ʦ��",9,10},
	{"��һ���±�",9,18},
	{"���ӵ���",9,28},
	{"�����",10,1},
	{"˫ʮһ",11,11},
	{"ƽ��ҹ",12,24},
	{"ʥ����",12,25},
	{0},
};

const OldAnnualFestival oafes[]={
	{"����",1,1},
	{"Ԫ��",1,15},
	{"����",5,5},
	{"��Ϧ",7,7},
	{"��Ԫ",7,15},
	{"����",8,15},
	{"����",9,9},
	{"����",12,8},
	{"ɨ��",12,23},
	{"����",12,24},
	{0},
};

const char*NameWeek[7]={
	"������","����һ","���ڶ�","������","������","������","������"
};

int GetWeek(NewCalendar*nc,OldCalendar*oc){
	return nc->wday;
}

const char*NameConstellation[12]={
	"������","��ţ��","˫����",
	"��з��","ʨ����","��Ů��",
	"�����","��Ы��","������",
	"Ħ����","ˮƿ��","˫����",
};

int GetConstellation(NewCalendar*nc,OldCalendar*oc){
	uint16_t yd;
	yd=nc->yday+((nc->year%(nc->year%100?4:400))?(nc->yday>59):0);
	if(yd>356)return 9;
	if(yd>327)return 8;
	if(yd>297)return 7;
	if(yd>266)return 6;
	if(yd>235)return 5;
	if(yd>204)return 4;
	if(yd>173)return 3;
	if(yd>141)return 2;
	if(yd>110)return 1;
	if(yd>80) return 0;
	if(yd>49) return 11;
	if(yd>19) return 10;
	if(yd>0)  return 9;
	return -1;
}

AttributeFestival atfes[]={
	{NameConstellation,GetConstellation},
	{NameWeek,GetWeek},
	{0},
};

WeekbasedFestival wbfes[]={
  {"ĸ�׽�",0,2,5},
  {"���׽�",0,3,6},
  {"�ж���",1,2,10},
  {0},
};

//��ʵ����ʮ���¼��������ܳ���
int isEve(NewCalendar*nc,OldCalendar*oc){
	if(oc->mon!=24&&oc->mon!=12)return 0;
	if((OldCalendar_Define[oc->year]&0xf)==12){
		if(oc->mon==24&&oc->mday==(((OldCalendar_Define[oc->year]>>16)&1)?30:29))return 1;
		return 0;
	}else{
		if(oc->mon==12&&oc->mday==(((OldCalendar_Define[oc->year]>>4)&1)?30:29))return 1;
		return 0;
	}
}

SpecialFestival spfes[]={
	{"��Ϧ",isEve},
	{0},
};

void Festival_PrintFestival(char*cout,NewCalendar*nc,OldCalendar*oc){
	int i;
	for(i=0;atfes[i].judge;i++){
		fest_puts(&cout,atfes[i].name[atfes[i].judge(nc,oc)]);
	}
	for(i=0;nafes[i].name;i++){
		if(nc->mon==nafes[i].mon&&nc->mday==nafes[i].mday)fest_puts(&cout,nafes[i].name);
	}
	for(i=0;oafes[i].name;i++){
		if(oc->mon==oafes[i].mon&&oc->mday==oafes[i].mday)fest_puts(&cout,oafes[i].name);
	}
	for(i=0;wbfes[i].name;i++){
		if(wbfes[i].mon==nc->mon&&wbfes[i].wday==nc->wday&&wbfes[i].order-1==(nc->mday-1)/7)
			fest_puts(&cout,wbfes[i].name);
	}
	for(i=0;spfes[i].name;i++){
		if(spfes[i].judge(nc,oc))fest_puts(&cout,spfes[i].name);
	}
	*cout=0;
}
