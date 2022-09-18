
#ifndef __tiaosu_H__
#define __tiaosu_H__

#define uchar unsigned char 
#define uint unsigned int

/**********************¶Ë¿Ú³õÊ¹»¯*******************************/
extern void port_init(void);
extern void forward(void);
extern void toleft(void);
extern void left(void);
extern void toright(void);
extern void right(void);
extern void stop(void);
extern void back(void);
extern void init_devices(void);
extern void delay_tiaosu_ms(uint k);
extern void tiaosu(uint time);

#endif