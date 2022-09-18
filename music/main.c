#include <iom16v.h> 
#include <macros.h>

//notegen.pl �ű�����ļ�
#include "notes.h" 

//ͨ��OCR1B������Ĭ������
#define DEFAULT_VOLUME 100
#define _BV(bit) (1 << (bit))


 void delay_loop(unsigned short int count)
{
  while(-- count);
}

void delay_ms(unsigned int ms)
{
        unsigned int i,j;
	for(i=0;i<ms;i++)
	   {
	   for(j=0;j<1141;j++);
       }
}


void InitMusic()
{
	

	DDRD |= _BV(DDD4); //OC1B ��Ϊ���

	//��ʼ��timer1 OCR1B���PWM
	TCCR1A |= _BV(COM1B1);  // �������ʱ�Ƚ�ƥ�佫���� OC1A/OC1B���������ʱ�Ƚ�ƥ�佫��λ OC1A/OC1B

	
	TCCR1B |= _BV(WGM13) 	// ��λ��Ƶ������PWM (���� ICR1)
		   |_BV(CS11); 		// 8λԤ��Ƶ
}



void PlayMusic( const int* pMusicNotes, /*ָ��ָ�������洢��������*/
				unsigned char tempo /*���Ʋ����ٶ�*/)  
{
	int duration;
	int note;
	int i;
	unsigned short int delay = tempo * 1000;

	while( *pMusicNotes )
	{
		note = *pMusicNotes;
		pMusicNotes++;

		duration = *pMusicNotes;
		pMusicNotes++;

		if( p == note )
		{
			//��ͣ
			OCR1B = 0;
		}
		else
		{
			//��������
			OCR1B = DEFAULT_VOLUME;

			//����Ƶ��
			ICR1H = (note >> 8);
			ICR1L = note;
		}

		//�ȴ�����ʱ��
		for(i=0;i<32-duration;i++)
		{
			delay_loop( delay );
		}

	}
	

	
	OCR1B = 0;
}

const int octave[] = {c4, 8, d4, 8, e4, 8, f4, 8, g4, 8, a4, 8, h4, 8, c5, 8, MUSIC_END};


// Star Wars
const int starwars[] = 
{
	Ais2,8, Ais2,8, P,16, F3,8, F3,8, P,16, Dis3,16, P,16, D3,16, P,16, C3,16, P,16, Ais3,8,
	Ais3,8, P,16, F3,8, P,16, Dis3,16, P,16, D3,16, P,16, C3,16, P,16, Ais3,8, Ais3,8, P,16,
	F3,8, P,16, Dis3,16, P,16, D3,16, P,16, Dis3,16, P,16, C3,8, C3,8, 
	MUSIC_END
};

// Fur Elise
const int furelise[] = 
{
    e4, 8, d4x, 8, e4, 8, d4x, 8, e4, 8, b3, 8, d4, 8, c4, 8, a3,8, p, 8,
    c3, 8, e3, 8, a3, 8,  b3, 4, p, 8, e3, 8, g3x, 8, b3, 8, c4, 4, p, 8, e3, 8,
    e3, 8, d4x, 8, e4, 8, d4x, 8, e4, 8, b3, 8, d4, 8, c4, 8, a3, 8, p, 8, c3, 8,
    e3, 8, a3, 8, b3, 4, p, 8, e3, 8, c4, 8, b3, 8, a3, 4,
    MUSIC_END
};

// Beatles, Hey Jude
const int Jude[] = {
	G2,8, E2,8, P,16, E2,16, E2,16, G2,16, A2,16, D2,8, P,16, D2,16, E2,16, F2,8, 
	C3,8, C3,16, C3,16, H2,16, G2,16, A2,16, G2,16, F2,16, E2,8, P,16, G2,16, 
	A2,16, A2,8, A2,16, D3,16, C3,16, H2,16, H2,16, C3,16, A2,16, G2,8, P,16, 
	C2,16, D2,16, E2,16, A2,16, A2,16, G2,8,
	MUSIC_END
};


void main()
{
	InitMusic();

	while(1)
	{

		PlayMusic( octave, 40 );
		delay_ms(1000);

		PlayMusic( furelise, 20 );
		delay_ms(1000);


		PlayMusic( starwars, 17 );
		delay_ms(1000);

		PlayMusic( Jude, 35 );
		delay_ms(1000);
	}

}
