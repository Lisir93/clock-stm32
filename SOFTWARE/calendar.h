#ifndef __CALENDAR_H__
#define __CALENDAR_H__

#include <stdint.h>

/*
	baseSec ��1900��1��1��0ʱ0��0�������ھ�������
	sec �� 0~59
	min �� 0~59
	hour ʱ 0~23
	mday �� 1~31
	mon �� 1~12
	year �� ��1900�������� 1900~2035
	wday ���� 0:�� 1:һ ... 6:�� 0~6
	yday ����ĵڼ��� 1~366
*/
typedef struct{
	uint32_t baseSec;
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t mday;
	uint8_t mon;
	uint16_t year;
	uint8_t wday;
	uint16_t yday;
}NewCalendar;

/*
	baseSec ��1900��1��1��0ʱ0��0�������ھ�������
	sec �� 0~59
	min �� 0~59
	hour ʱ 0~23
	mday �� 1~30
	mon �� 1~12��ʾ�� 13~24��ʾ����
	year �� ����1900��1��31����ʼ��ũ����Ϊ0��
*/
typedef struct{
	uint32_t baseSec;
	uint8_t mday;
	uint8_t mon;
	uint8_t year;
}OldCalendar;

extern const uint32_t OldCalendar_Define[];

void		Newcal_Clr				(NewCalendar*nc);
void		Newcal_Cpy				(NewCalendar*nc,NewCalendar*ncfrom);
void		Newcal_Get				(NewCalendar*nc,uint32_t bsec);
uint8_t		Newcal_Getwday			(uint16_t year,uint16_t yday);
uint16_t	Newcal_Getyday			(uint16_t year,uint8_t mon,uint8_t mday);
uint8_t		Newcal_GetDayNumofMon	(uint16_t year,uint8_t mon);
int			Newcal_Cmp				(NewCalendar*nc1,NewCalendar*nc2);
uint32_t	Newcal_GetBaseSecond	(NewCalendar*nc);
int			Newcal_Judge			(NewCalendar*nc);

void		Oldcal_Clr				(OldCalendar*oc);
void		Oldcal_Cpy				(OldCalendar*oc,OldCalendar*ocfrom);
void		Oldcal_Get				(OldCalendar*oc,uint32_t bsec);

//����
#define ClrNewCalendar Newcal_Clr
#define ClrOldCalendar Oldcal_Clr
#define CpyNewCalendar Newcal_Cpy
#define CpyOldCalendar Oldcal_Cpy
#define GetNewCalendar Newcal_Get
#define GetOldCalendar Oldcal_Get
#define Getwday Newcal_Getwday
#define Getyday Newcal_Getyday
#define GetDayNumofMonNewCalendar Newcal_GetDayNumofMon
#define JudgeNewCalendar Newcal_Judge
#define CmpNewCalendar Newcal_Cmp
#define GetBaseSecond Newcal_GetBaseSecond
/*
void ClrNewCalendar(NewCalendar*nc);
void ClrOldCalendar(OldCalendar*oc);
void CpyNewCalendar(NewCalendar*nc,NewCalendar*ncfrom);
void CpyOldCalendar(OldCalendar*oc,OldCalendar*ocfrom);
void GetNewCalendar(NewCalendar*nc,uint32_t bsec);
void GetOldCalendar(OldCalendar*oc,uint32_t bsec);
uint8_t Getwday(uint16_t year,uint16_t yday);
uint16_t Getyday(uint16_t year,uint8_t mon,uint8_t mday);
uint8_t GetDayNumofMonNewCalendar(uint16_t year,uint8_t mon);
int JudgeNewCalendar(NewCalendar*nc);
int CmpNewCalendar(NewCalendar*nc1,NewCalendar*nc2);
uint32_t GetBaseSecond(NewCalendar*nc);
*/
#endif
