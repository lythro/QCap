#include "QCapEtherPacket.h"
#include <cstring> // memcpy
#include "MyEther.h"


// ntohs
#ifdef WIN32
	#include <Winsock.h>
#else
	#include <arpa/inet.h>
#endif



QCapEtherPacket::QCapEtherPacket( const unsigned char* packet, size_t size )
{
	// copy the whole packet
	m_packet = new unsigned char[size];
	memcpy( m_packet, packet, size );

	m_size = size;
}

QString QCapEtherPacket::srcHost() const
{
	const ether_header* e = reinterpret_cast<const ether_header*>( m_packet );

	const ether_addr* a = reinterpret_cast<const ether_addr*>( &e->ether_shost );

	return QString::fromLatin1( ether_ntoa( a ) );
}


QString QCapEtherPacket::dstHost() const
{
	const ether_header* e = reinterpret_cast<const ether_header*>( m_packet );

	const ether_addr* a = reinterpret_cast<const ether_addr*>( &e->ether_dhost );

	return QString::fromLatin1( ether_ntoa( a ) );
}


uint16_t QCapEtherPacket::frameType() const
{
	const ether_header* e = reinterpret_cast<const ether_header*>( m_packet );

	return ntohs(e->ether_type);
}

bool QCapEtherPacket::isIpPacket() const
{
	return (frameType() == ETHERTYPE_IP);
}

QCapEtherPacket::~QCapEtherPacket()
{
	delete[] m_packet;
}
