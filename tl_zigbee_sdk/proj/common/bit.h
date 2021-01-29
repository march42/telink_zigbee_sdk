/********************************************************************************************************
 * @file	bit.h
 *
 * @brief	This is the header file for bit
 *
 * @author	Driver & Zigbee Group
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions
 *              in binary form must reproduce the above copyright notice, this list of
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *
 *              3. Neither the name of TELINK, nor the names of its contributors may be
 *              used to endorse or promote products derived from this software without
 *              specific prior written permission.
 *
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or
 *              relating to such deletion(s), modification(s) or alteration(s).
 *
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************************************/
#pragma once

// http://www.coranac.com/documents/working-with-bits-and-bitfields/#sec-intro

#include "macro_trick.h"

#define BIT(n)                  		( 1<<(n) )

// BITSx  are internal used macro, please use BITS instead
#define BITS1(a)                 		BIT(a)
#define BITS2(a, b)              		(BIT(a) | BIT(b))
#define BITS3(a, b, c)          		(BIT(a) | BIT(b) | BIT(c))
#define BITS4(a, b, c, d)        		(BIT(a) | BIT(b) | BIT(c) | BIT(d))
#define BITS5(a, b, c, d, e)     		(BIT(a) | BIT(b) | BIT(c) | BIT(d) | BIT(e))
#define BITS6(a, b, c, d, e, f)  		(BIT(a) | BIT(b) | BIT(c) | BIT(d) | BIT(e) | BIT(f))
#define BITS7(a, b, c, d, e, f, g)  	(BIT(a) | BIT(b) | BIT(c) | BIT(d) | BIT(e) | BIT(f) | BIT(g))
#define BITS8(a, b, c, d, e, f, g, h)  	(BIT(a) | BIT(b) | BIT(c) | BIT(d) | BIT(e) | BIT(f) | BIT(g) | BIT(h))

#define BITS(...) 						VARARG(BITS, __VA_ARGS__) 


// bits range: BITS_RNG(4, 5)  0b000111110000,  start from 4, length = 5
#define BIT_RNG(s, e)  					(BIT_MASK_LEN((e)-(s)+1) << (s))

#define BM_MASK_V(x, mask)        		( (x) | (mask) )
#define BM_CLR_MASK_V(x, mask)    		( (x) & ~(mask) )

#define BM_SET(x, mask)         		( (x) |= (mask) )
#define BM_CLR(x, mask)       			( (x) &= ~(mask) )
#define BM_IS_SET(x, mask)   			( (x) & (mask) )
#define BM_IS_CLR(x, mask)   			( (~x) & (mask) )
#define BM_FLIP(x, mask)      			( (x) ^=  (mask) )

// !!!!   v is already a masked value,  no need to shift
#define BM_MASK_VAL(x, mask, v)  		( ((x) & ~(mask)) | (v))
#define BM_SET_MASK_VAL(x, mask, v)  	( (x) = BM_MASK_VAL(x, mask, v) )

//-------------------SET_BIT---------------------
#define SETB(v,n)						(*(volatile unsigned char  *)v |= n)
#define CLRB(v,n)						(*(volatile unsigned char  *)v &= ~n)
#define TEST(v,n)						(((*(volatile unsigned char  *)v) & n) ? 1:0)
#define BIT_SET(x, n)         			((x) |=  BIT(n))
#define BIT_CLR(x, n)       			((x) &= ~ BIT(n))
#define BIT_IS_SET(x, n)   				((x) & BIT(n))
#define BIT_FLIP(x, n)   				((x) ^= BIT(n))
#define BIT_SET_HIGH(x) 				((x) |=  BIT((sizeof((x))*8-1)))				// set the highest bit
#define BIT_CLR_HIGH(x) 				((x) &= ~ BIT((sizeof((x))*8-1)))				// clr the highest bit
#define BIT_IS_SET_HIGH(x) 				((x) & BIT((sizeof((x))*8-1)))					// check the highest bit

#define BIT_MASK_LEN(len)       		(BIT(len)-1)
#define BIT_MASK(start, len)    		(BIT_MASK_LEN(len) << (start) )

//! Prepare a bitmask for insertion or combining.
#define BIT_PREP(x, start, len) 		((x) & BIT_MASK(start, len))

//! Extract a bitfield of length \a len starting at bit \a start from \a y.
#define BIT_GET(x, start, len)  		(((x) >> (start)) & BIT_MASK_LEN(len))
#define BIT_GET_LOW(x, len)   			((x) & BIT_MASK_LEN(len))

//! Insert a new bitfield value \a x into \a y.
#define BIT_MERGE(y, x, start, len)    \
    ( y = ((y) &~ BIT_MASK(start, len)) | BIT_PREP(x, start, len) )

#define BIT_IS_EVEN(x)     				(((x)&1)==0)
#define BIT_IS_ODD(x)      				(!BIT_IS_EVEN((x)))

#define BIT_IS_POW2(x)     				(!((x) & ((x)-1)))

/* turn off right-most 1-bit in x */
#define BIT_TURNOFF_1(x)   				((x) &= ((x)-1))
/* isolate right-most 1-bit in x */
#define BIT_ISOLATE_1(x)   				((x) &= (-(x)))
/* right-propagate right-most 1-bit in x */
#define BIT_PROPAGATE_1(x) 				((x) |= ((x)-1))
/* isolate right-most 0-bit in x */
#define BIT_ISOLATE_0(x)   				((x) = ~(x) & ((x)+1))
/* turn on right-most 0-bit in x */
#define BIT_TURNON_0(x)    				((x) |= ((x)+1))

#define CLAMP_TO_ONE(x) 				(!!(x))				// compiler defined, not stardard.    0 --> 0,   1 --> 0xffffffff

#define ONES(x)							BIT_MASK_LEN(x)
#define ONES_32							0xffffffff
#define ALL_SET							0xffffffff

#if 0
//! Massage \a x for use in bitfield \a name.
#define BFN_PREP(x, name)    			( ((x)<<name##_SHIFT) & name##_MASK )

//! Get the value of bitfield \a name from \a y. Equivalent to (var=) y.name
#define BFN_GET(y, name)     			( ((y) & name##_MASK)>>name##_SHIFT )

//! Set bitfield \a name from \a y to \a x: y.name= x.
#define BFN_SET(y, x, name)  			(y = ((y)&~name##_MASK) | BFN_PREP(x,name) )

// Usage: prio get/set like before:
prio = BFN_GET(attr2, ATTR2_PRIO);
BFN_SET(attr2, x, ATTR2_PRIO);
#endif

/* 
** bithacks.h - bit hacks macros. v1.0
**
** Peteris Krumins (peter@catonmat.net)
** http://www.catonmat.net  --  good coders code, great reuse
**
** This file is explained in the following article:
** http://www.catonmat.net/blog/bit-hacks-header-file
**
** Released under the MIT license.
*/

// Return the bit index of the lowest 1 in y.   ex:  0b00110111000  --> 3
#define BIT_LOW_BIT(y)  (((y) & BIT(0))?0:(((y) & BIT(1))?1:(((y) & BIT(2))?2:(((y) & BIT(3))?3:			\
						(((y) & BIT(4))?4:(((y) & BIT(5))?5:(((y) & BIT(6))?6:(((y) & BIT(7))?7:				\
						(((y) & BIT(8))?8:(((y) & BIT(9))?9:(((y) & BIT(10))?10:(((y) & BIT(11))?11:			\
						(((y) & BIT(12))?12:(((y) & BIT(13))?13:(((y) & BIT(14))?14:(((y) & BIT(15))?15:		\
						(((y) & BIT(16))?16:(((y) & BIT(17))?17:(((y) & BIT(18))?18:(((y) & BIT(19))?19:		\
						(((y) & BIT(20))?20:(((y) & BIT(21))?21:(((y) & BIT(22))?22:(((y) & BIT(23))?23:		\
						(((y) & BIT(24))?24:(((y) & BIT(25))?25:(((y) & BIT(26))?26:(((y) & BIT(27))?27:		\
						(((y) & BIT(28))?28:(((y) & BIT(29))?29:(((y) & BIT(30))?30:(((y) & BIT(31))?31:32		\
						))))))))))))))))))))))))))))))))

// Return the bit index of the highest 1 in (y).   ex:  0b00110111000  --> 8
#define BIT_HIGH_BIT(y)  (((y) & BIT(31))?31:(((y) & BIT(30))?30:(((y) & BIT(29))?29:(((y) & BIT(28))?28:	\
						(((y) & BIT(27))?27:(((y) & BIT(26))?26:(((y) & BIT(25))?25:(((y) & BIT(24))?24:		\
						(((y) & BIT(23))?23:(((y) & BIT(22))?22:(((y) & BIT(21))?21:(((y) & BIT(20))?20:		\
						(((y) & BIT(19))?19:(((y) & BIT(18))?18:(((y) & BIT(17))?17:(((y) & BIT(16))?16:		\
						(((y) & BIT(15))?15:(((y) & BIT(14))?14:(((y) & BIT(13))?13:(((y) & BIT(12))?12:		\
						(((y) & BIT(11))?11:(((y) & BIT(10))?10:(((y) & BIT(9))?9:(((y) & BIT(8))?8:			\
						(((y) & BIT(7))?7:(((y) & BIT(6))?6:(((y) & BIT(5))?5:(((y) & BIT(4))?4:				\
						(((y) & BIT(3))?3:(((y) & BIT(2))?2:(((y) & BIT(1))?1:(((y) & BIT(0))?0:32				\
						))))))))))))))))))))))))))))))))

#define BM_MASK_FLD(x, mask)    		(((x) & (mask)) >> BIT_LOW_BIT(mask))
#define BM_SET_MASK_FLD(x, mask, v)    	( (x) = BM_MASK_VAL(x,mask,v) )

//////////////////////
#define MV(m, v)											(((v) << BIT_LOW_BIT(m)) & (m))

// warning MASK_VALn  are internal used macro, please use MASK_VAL instead
#define MASK_VAL2(m, v)    									(MV(m,v))
#define MASK_VAL4(m1,v1,m2,v2)    							(MV(m1,v1)|MV(m2,v2))
#define MASK_VAL6(m1,v1,m2,v2,m3,v3)    					(MV(m1,v1)|MV(m2,v2)|MV(m3,v3))
#define MASK_VAL8(m1,v1,m2,v2,m3,v3,m4,v4)    				(MV(m1,v1)|MV(m2,v2)|MV(m3,v3)|MV(m4,v4))
#define MASK_VAL10(m1,v1,m2,v2,m3,v3,m4,v4,m5,v5)    		(MV(m1,v1)|MV(m2,v2)|MV(m3,v3)|MV(m4,v4)|MV(m5,v5))
#define MASK_VAL12(m1,v1,m2,v2,m3,v3,m4,v4,m5,v5,m6,v6)    	(MV(m1,v1)|MV(m2,v2)|MV(m3,v3)|MV(m4,v4)|MV(m5,v5)|MV(m6,v6))
#define MASK_VAL14(m1,v1,m2,v2,m3,v3,m4,v4,m5,v5,m6,v6,m7,v7) (MV(m1,v1)|MV(m2,v2)|MV(m3,v3)|MV(m4,v4)|MV(m5,v5)|MV(m6,v6)|MV(m7,v7))
#define MASK_VAL16(m1,v1,m2,v2,m3,v3,m4,v4,m5,v5,m6,v6,m7,v7,m8,v8) (MV(m1,v1)|MV(m2,v2)|MV(m3,v3)|MV(m4,v4)|MV(m5,v5)|MV(m6,v6)|MV(m7,v7)|MV(m8,v8))

#define MASK_VAL(...) 					VARARG(MASK_VAL, __VA_ARGS__) 

#define FLD_MASK_VAL(x, mask, v)    	BM_MASK_VAL(x, mask, MV(mask,v))

#define SET_FLD(x, mask)    			BM_SET(x, mask)
#define CLR_FLD(x, mask)    			BM_CLR(x, mask)
#define FLIP_FLD(x, mask)    			BM_FLIP(x, mask)

#define GET_FLD(x, mask)    			BM_MASK_FLD(x, mask)

#ifndef WIN32
// warning SET_FLD_Vn  are internal used macro, please use SET_FLD_V instead
#define SET_FLD_V3(x, m, v)    															\
    BM_SET_MASK_FLD(x,m,MV(m,v))
    
#define SET_FLD_V5(x, m1, v1, m2, v2)    												\
    BM_SET_MASK_FLD(x, m1|m2, MV(m1,v1)| MV(m2,v2))

#define SET_FLD_V7(x, m1, v1, m2, v2, m3, v3)    										\
    BM_SET_MASK_FLD(x, m1|m2|m3, MV(m1,v1)| MV(m2,v2)| MV(m3,v3))

#define SET_FLD_V9(x, m1, v1, m2, v2, m3, v3, m4, v4)    								\
    BM_SET_MASK_FLD(x, m1|m2|m3|m4, MV(m1,v1)| MV(m2,v2)| MV(m3,v3)| MV(m4,v4))

#define SET_FLD_V11(x, m1, v1, m2, v2, m3, v3, m4, v4, m5, v5)    						\
    BM_SET_MASK_FLD(x, m1|m2|m3|m4|m5, MV(m1,v1)| MV(m2,v2)| MV(m3,v3)| MV(m4,v4)| MV(m5,v5))

#define SET_FLD_V13(x, m1, v1, m2, v2, m3, v3, m4, v4, m5, v5, m6, v6)    				\
    BM_SET_MASK_FLD(x, m1|m2|m3|m4|m5|m6, MV(m1,v1)| MV(m2,v2)| MV(m3,v3)| MV(m4,v4)| MV(m5,v5)| MV(m6,v6))
#else
#define SET_FLD_V3(x, m, v)    															\
	__pragma(warning(push))				\
	__pragma(warning(disable:4244)) 	\
    BM_SET_MASK_FLD(x,m,MV(m,v))		\
	__pragma(warning(pop))
    
#define SET_FLD_V5(x, m1, v1, m2, v2)    												\
	__pragma(warning(push))				\
	__pragma(warning(disable:4244)) 	\
    BM_SET_MASK_FLD(x, m1|m2, MV(m1,v1)| MV(m2,v2))		\
	__pragma(warning(pop))

#define SET_FLD_V7(x, m1, v1, m2, v2, m3, v3)    										\
	__pragma(warning(push))				\
	__pragma(warning(disable:4244)) 	\
    BM_SET_MASK_FLD(x, m1|m2|m3, MV(m1,v1)| MV(m2,v2)| MV(m3,v3))						\
	__pragma(warning(pop))

#define SET_FLD_V9(x, m1, v1, m2, v2, m3, v3, m4, v4)    								\
	__pragma(warning(push))				\
	__pragma(warning(disable:4244)) 	\
    BM_SET_MASK_FLD(x, m1|m2|m3|m4, MV(m1,v1)| MV(m2,v2)| MV(m3,v3)| MV(m4,v4))			\
	__pragma(warning(pop))

#define SET_FLD_V11(x, m1, v1, m2, v2, m3, v3, m4, v4, m5, v5)    						\
	__pragma(warning(push))				\
	__pragma(warning(disable:4244)) 	\
    BM_SET_MASK_FLD(x, m1|m2|m3|m4|m5, MV(m1,v1)| MV(m2,v2)| MV(m3,v3)| MV(m4,v4)| MV(m5,v5))	\
	__pragma(warning(pop))

#define SET_FLD_V13(x, m1, v1, m2, v2, m3, v3, m4, v4, m5, v5, m6, v6)    				\
	__pragma(warning(push))				\
	__pragma(warning(disable:4244)) 	\
    BM_SET_MASK_FLD(x, m1|m2|m3|m4|m5|m6, MV(m1,v1)| MV(m2,v2)| MV(m3,v3)| MV(m4,v4)| MV(m5,v5)| MV(m6,v6))	\
	__pragma(warning(pop))
#endif

#define SET_FLD_V(...) 				VARARG(SET_FLD_V, __VA_ARGS__) 


//This means direct assignment
#define SET_FLD_FULL_V3(x, m, v)											((x) = MASK_VAL2(m,v))
#define SET_FLD_FULL_V5(x, m1, v1, m2, v2)  								((x) = MASK_VAL4(m1,v1,m2,v2))
#define SET_FLD_FULL_V7(x, m1, v1, m2, v2, m3, v3)  						((x) = MASK_VAL6(m1,v1,m2,v2,m3,v3))
#define SET_FLD_FULL_V9(x, m1, v1, m2, v2, m3, v3, m4, v4)    				((x) = MASK_VAL8(m1,v1,m2,v2,m3,v3,m4,v4))
#define SET_FLD_FULL_V11(x, m1, v1, m2, v2, m3, v3, m4, v4, m5, v5)    		((x) = MASK_VAL10(m1,v1,m2,v2,m3,v3,m4,v4,m5,v5))
#define SET_FLD_FULL_V13(x, m1, v1, m2, v2, m3, v3, m4, v4, m5, v5, m6, v6) ((x) = MASK_VAL12(m1,v1,m2,v2,m3,v3,m4,v4,m5,v5,m6,v6))
#define SET_FLD_FULL_V(...) 			VARARG(SET_FLD_FULL_V, __VA_ARGS__) 

////////////////////////////////////////////////////////////////////////
#define HEXIFY(y) 0x##y##LU

#define BIT_8IFY(y) (((y&0x0000000FLU)?1:0)  + \
                  ((y&0x000000F0LU)?2:0)  + \
                  ((y&0x00000F00LU)?4:0)  + \
                  ((y&0x0000F000LU)?8:0)  + \
                  ((y&0x000F0000LU)?16:0) + \
                  ((y&0x00F00000LU)?32:0) + \
                  ((y&0x0F000000LU)?64:0) + \
                  ((y&0xF0000000LU)?128:0))

#define BIT_8(Z) ((unsigned char)BIT_8IFY(HEXIFY(Z)))


