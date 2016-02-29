/*
 * TWI_StatCodes.h
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#ifndef CODE_TWI_TWI_STATCODES_H_
#define CODE_TWI_TWI_STATCODES_H_

#define TWI_M_IDLE 			0xF8

#define TWI_M_START			0x08
#define TWI_M_REPSTART		0x10

#define TWI_M_SLAW_ACK		0x18
#define TWI_M_SLAW_NACK		0x20

#define TWI_M_SLAR_ACK 		0x40
#define TWI_M_SLAR_NACK		0x48

#define TWI_M_DATA_ACK		0x28
#define TWI_M_DATA_NACK		0x30

#define TWI_M_REDA_ACK 		0x50
#define TWI_M_REDA_NACK 	0x58

#define TWI_M_MT_ARB_LOST	0x38



#endif /* CODE_TWI_TWI_STATCODES_H_ */
