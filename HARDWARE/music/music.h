#ifndef __MUSIC_H__
#define __MUSIC_H__

//ռ��TIM3(PWM)��TIM2(��ʱ),���PB5
//��Music Encode����,�ı����䷶��
//2017��12��10��01:38:07 aou

#include <stdint.h>

typedef enum
{
	Music_Test,
	Music_HappyBirthday,
}Music_TuneNamet;

typedef const uint8_t*Music_Tune_t;

typedef struct
{
	Music_Tune_t tune;
	Music_Tune_t progress;
	uint16_t LDiv0;
	uint16_t LDiv4;
	uint16_t delay;
	float NewFreTab[12];
}Music_t;

extern Music_t Music_Playing;

void Music_Init(void);
void Music_Frequency(uint16_t fre);
void Music_Play(Music_Tune_t music,int Signature,int Octachord,int Speed);
void Music_Stop(void);
void Music_Continue(void);

#endif
