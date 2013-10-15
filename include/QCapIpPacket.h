#ifndef QCAPIPPACKET_H_
#define QCAPIPPACKET_H_

#include "QCapEtherPacket.h"

class QCapIpPacket
{
public:
	QCapIpPacket( const QCapEtherPacket* );
	~QCapIpPacket();

	// TODO
	//
	// QString srcIpStr();
 	// QSTring dstIpStr();
	//
	// uint32_t srcIp();
	// uint32_t dstIp();
	//
	// const unsigned char* payload();
	// size_t payloadSize();
	//
	// bool isUdpPacket()
	// bool isTcpPacket()
	//
	// QCapTcpPacket* toTcpPacket()
	// QCapUdpPacket* toUdpPacket()

private:
	unsigned char* m_packet;
	size_t m_size;
};


#endif
