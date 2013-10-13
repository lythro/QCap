#ifndef MYETHER_H_
#define MYETHER_H_

#include <stdio.h>

/*
 **	IEEE 802.3 Ethernet magic constants.  The frame sizes omit the preamble
 **	and FCS/CRC (frame check sequence).
 **/

#define ETH_ALEN	6		/* Octets in one ethernet addr	 */
#define ETH_HLEN	14		/* Total octets in header.	 */
#define ETH_ZLEN	60		/* Min. octets in frame sans FCS */
#define ETH_DATA_LEN	1500	/* Max. octets in payload	 */
#define ETH_FRAME_LEN	1514	/* Max. octets in frame sans FCS */
#define ETH_FCS_LEN		4	/* Octets in the FCS		 */

#define	ETHERTYPE_IP		0x0800		/* IP */

/* 10Mb/s ethernet header */
struct ether_header
{
	uint8_t  ether_dhost[ETH_ALEN];	/* destination eth addr	*/
	uint8_t  ether_shost[ETH_ALEN];	/* source ether addr	*/
	uint16_t ether_type;		    /* packet type ID field	*/
} __attribute__ ((__packed__));


/* This is a name for the 48 bit ethernet address available on many
 * systems.  */
struct ether_addr
{
	u_int8_t ether_addr_octet[ETH_ALEN];
} __attribute__ ((__packed__));


char * ether_ntoa_r(const struct ether_addr *addr, char *buf)
{
	sprintf (buf, "%x:%x:%x:%x:%x:%x",
			addr->ether_addr_octet[0], 	addr->ether_addr_octet[1],
			addr->ether_addr_octet[2], 	addr->ether_addr_octet[3],
			addr->ether_addr_octet[4], 	addr->ether_addr_octet[5]	);
	return buf;
}

char * ether_ntoa(const struct ether_addr *addr)
{
	static char temp_buf [18];
	return ether_ntoa_r(addr,temp_buf);
}

#endif
