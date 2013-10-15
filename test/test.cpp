#include <iostream>
#include <QByteArray>
#include <QString>
#include <QCoreApplication>
#include <QTimer>
#include <QSharedPointer>

#include "QCap.h"
#include "QCapEtherPacket.h"

#include "PacketInfoPrinter.h"

#include <iostream>
using std::endl;
using std::cout;
using std::flush;


int main(int argc, char** args)
{
	QCoreApplication app( argc, args );


	cout << "-- creating QCap object..." << endl;
	QCap cap;

	cout << "-- lookup default device... " << flush;
	QString dev = cap.lookupDevice();
	if (dev.isEmpty())
	{
		cout << "not found." << endl;
		return 1;
	}
	cout << dev.toStdString() << endl;

	cout << "-- open device... " << flush;
	if (!cap.open( dev ))
	{
		cout << "failed." << endl;
		return 1;
	}
	cout << "ok." << endl;


	/*
	cout << "-- setting filter \"ip\"... " << flush;
	if (!cap.setFilter( "ip" ))
	{
		cout << "failed." << endl;
		return 1;
	}
	cout << "ok." << endl;
	*/
	
	PacketInfoPrinter printer;
	QObject::connect( &cap, SIGNAL(packetReady( QSharedPointer<QCapEtherPacket> ) ),
					&printer, SLOT(printInfo( QSharedPointer<QCapEtherPacket> ) ) );

	cout << "-- start capture..." << endl;
	cap.start();
	cout << "-- capture for 5 seconds..." << endl;


	// start the eventloop, but quit it after
	// a few seconds!
	QTimer timer;
	timer.setSingleShot( true );
	
	QObject::connect( &timer, SIGNAL(timeout()),
					&app, SLOT(quit()) );

	timer.start( 5000 );
	app.exec();

	cout << "-- stop capture..." << endl;
	cap.stop();

	// get some stats
	struct pcap_stat stat = cap.getStats();

	cout << "-- packets received: " << stat.ps_recv << endl;
	cout << "-- packets dropped by me: " << stat.ps_drop << endl;
	cout << "-- packets dropped by if: " << stat.ps_ifdrop << endl;

	cout << "-- close device... " << flush;
	if (!cap.close())
	{
		cout << "failed." << endl;
	}
	cout << "ok." << endl;

	return 0;
}
