#include "QCapIpPacket.h"
#include "QCapEtherPacket.h"

#include <cstring>

QCapIpPacket::QCapIpPacket( const QCapEtherPacket* e )
{
	const unsigned char* edata = e->payload();

	m_size = e->payloadSize();
	m_packet = new unsigned char[m_size];

	memcpy( m_packet, edata, m_size );
}



QCapIpPacket::~QCapIpPacket()
{
	delete[] m_packet;
}
