/********************************************************************************************************
 * @file    tlPrintf.c
 *
 * @brief   This is the source file for tlPrintf
 *
 * @author  Driver & Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/

#if (__PRINTF_FLOAT)
	/* stdlib.h doesn't play well with the ZigBee SDK headers
	**	conflicting types for 'size_t'		telink_zigbee_sdk/tl_zigbee_sdk/proj/common/../drivers/../common/types.h:173
	**	conflicting types for 'rand'		telink_zigbee_sdk/tl_zigbee_sdk/platform/chip_8258/random.h:41
#	include <stdlib.h>
	**	without including stdlib.h the code won't use the library functions */
#	include <math.h>
#endif

#include "../drivers/drv_putchar.h"
#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
	#include <stdarg.h>
#else
	typedef char *va_list;

	#define _INTSIZEOF(n)   	( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

	#define va_start(ap,v)  	( ap = (va_list)&v + _INTSIZEOF(v) )
	#define va_arg(ap,t)    	( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
	#define va_end(ap)      	( ap = (va_list)0 )

	#define	DECIMAL_OUTPUT		10
	#define	OCTAL_OUTPUT		8
	#define	HEX_OUTPUT			16
#endif



#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
__attribute__((used)) int _write(int fd, const unsigned char *buf, int size){
	(void)fd;
    int i;
    for(i = 0; i < size; i++){
    	drv_putchar(buf[i]);
    }
    return i;
}
#else
static void put_s(char *s){
	while((*s != '\0')){
		drv_putchar(*s++);
	}
}

static void puti(unsigned int num, int base){
	char re[]="0123456789ABCDEF";

	char buf[50];

	char *addr = &buf[49];

	*addr = '\0';

	do{
		*--addr = re[num%base];
		num/=base;
	}while(num!=0);

	put_s(addr);
}

#if (__PRINTF_FLOAT)
static void putf(double num)
{
#	ifdef _STDLIB_H_
	int dec, sign;
	s = fcvt (num, 5, &dec, &sign);
	if (sign) {
		drv_putchar('-');
	}
	while((*s != '\0')){
		if (dec-- == 0) {
			drv_putchar('.');
		}
		drv_putchar(*s++);
	}
#	else
	double f_integ,f_fract;
	// convert to split decimal
	f_fract = modf (num, &f_integ);	// f_fract gets the fractional part, f_integ gets the integral part
	m = (long)f_integ;				// cast to integer
	if(m<0){
		drv_putchar('-');
		m = -m;
	}
	puti(m,DECIMAL_OUTPUT);
	drv_putchar('.');
	f_fract *= 100000.0;			// this should give 5 decimal digits
	m = (long)f_fract;				// cast to integer
	if (m < 10000) {
		drv_putchar('0');			// output leading zeroes
	}
	if (m < 1000) {
		drv_putchar('0');			// output leading zeroes
	}
	if (m < 100) {
		drv_putchar('0');			// output leading zeroes
	}
	if (m < 10) {
		drv_putchar('0');			// output leading zeroes
	}
	puti(m,DECIMAL_OUTPUT);
#	endif
}
#endif

int tl_printf(const char *format, ...){
	char span;
	unsigned long j;
	char *s;
	long m;
#if (__PRINTF_FLOAT)
	double f;
#endif

	va_list arg_ptr;
	va_start(arg_ptr, format);

#if (UART_PRINTF_DISABLE_IRQ)
	u32 r = drv_disable_irq();// enable this may disturb time sequence, but if disable unrecognizable code will show
#endif

	while((span = *(format++))){
		if(span != '%'){
			drv_putchar(span);
		}else{
			span = *(format++);
			if(span == 'c'){
				j = va_arg(arg_ptr,int);//get value of char
				drv_putchar(j);
			}else if(span == 'd'){
				m = va_arg(arg_ptr,int);//get value of char
				if(m<0){
					drv_putchar('-');
					m = -m;
				}
				puti(m,DECIMAL_OUTPUT);
			}else if(span == 's'){
				s = va_arg(arg_ptr,char *);//get string value
				put_s(s);
			}else if(span == 'o'){
				j = va_arg(arg_ptr,unsigned int);//get octal value
				puti(j,OCTAL_OUTPUT);
			}else if(span == 'x'){
					j = va_arg(arg_ptr,unsigned int);//get hex value
					puti(j,HEX_OUTPUT);
#if (__PRINTF_FLOAT)
			}else if(span == 'f'){
				f = va_arg(arg_ptr,double);//get floating point value
				putf(f);
#endif
			}else if(span == 0){
				break;
			}else{
				drv_putchar(span);
			}
		}
	}
	va_end(arg_ptr);

#if (UART_PRINTF_DISABLE_IRQ)
	drv_restore_irq(r);
#endif

	return 0;
}
#endif

