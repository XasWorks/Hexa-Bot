/*
 * TWI_StatCodes.h
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#ifndef CODE_TWI_TWI_STATCODES_H_
#define CODE_TWI_TWI_STATCODES_H_

#define TWI_IDLE 			0xF8
#define TWI_ERROR			0x00

#define TWI_M_START			0x08
#define TWI_M_REPSTART		0x10

// Master-Transmit related status codes
#define TWI_MT_SLA_ACK		0x18
#define TWI_MT_SLA_NACK		0x20

#define TWI_MT_DATA_ACK		0x28
#define TWI_MT_DATA_NACK	0x30

// Master-Read related status codes
#define TWI_MR_SLA_ACK 		0x40
#define TWI_MR_SLA_NACK		0x48

#define TWI_MR_DATA_ACK 	0x50
#define TWI_MR_DATA_NACK 	0x58

// Slave-Read related status codes
#define TWI_SR_SLA_ACK		0x60
#define TWI_SR_DATA_ACK		0x80
#define TWI_SR_DATA_NACK	0x88

#define TWI_SR_GC_ACK		0x70
#define TWI_SR_GC_DATA_ACK	0x90
#define TWI_SR_GC_DATA_NACK	0x98

#define TWI_SR_STOP			0xA0

// Slave-Transmit related status codes
#define TWI_ST_SLA_ACK		0xA8
#define TWI_ST_DATA_ACK		0xB8
#define TWI_ST_DATA_NACK	0xC0
#define TWI_ST_DATA_LAST	0xC8

// Arbitration related status codes
#define TWI_MT_ARB_LOST		0x38

#define TWI_ARB_LOST_SLAW	0x68	// Arbitration lost and Sla+W received
#define TWI_ARB_LOST_GC		0x78	// Arbitration lost, GC received

#define TWI_ARB_LOST_SLAR	0xB0

#endif /* CODE_TWI_TWI_STATCODES_H_ */
