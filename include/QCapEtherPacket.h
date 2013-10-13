#ifndef QCAPETHERPACKET_H_
#define QCAPETHERPACKET_H_

// size_t
#include <stdlib.h>

// uint16_t etc.
#include <stdint.h>
#include <QString>

class QCapEtherPacket
{
public:
	QCapEtherPacket( const unsigned char* packet, size_t size );
	~QCapEtherPacket();

	QString srcHost() const;
	QString dstHost() const;

	uint16_t frameType() const;

	bool isIpPacket() const;

	// TODO
	// QCapIpPacket toIpPacket() const;

private:
	unsigned char* m_packet;
	size_t m_size;
};

#endif
