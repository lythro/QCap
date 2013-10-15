#include "PacketInfoPrinter.h"

#include <QByteArray>

#include <iostream>
using std::cout;
using std::endl;
using std::flush;

void PacketInfoPrinter::printInfo( QSharedPointer<QCapEtherPacket> packet )
{
	static int no = 0;

	cout << endl;
	cout << "---------------------" << endl;
	cout << " Packet:        " << no++ << endl;
	cout << "  isIpPacket:   " << packet->isIpPacket() << endl;
	cout << "  srcHost:      " << packet->srcHost().toStdString() << endl;
	cout << "  dstHost:      " << packet->dstHost().toStdString() << endl;

	// some info about the data
	cout << "  payload size: " << packet->payloadSize() << endl;

	if (packet->payloadSize() <= 0)	return;

	const unsigned char* data = packet->payload();
	QByteArray tmp( (const char*) data, 1 );
	QByteArray hex = tmp.toHex();

	cout << "   first byte:  0x" << hex[0] << hex[1]  << endl;
	
}
