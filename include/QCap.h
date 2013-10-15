#ifndef QCAP_H_
#define QCAP_H_

#include <QObject>
#include <QString>
#include <QSocketNotifier>
#include <QSharedPointer>
#include <QByteArray>

#include <pcap.h>

#define PCAP_TIMEOUT 10000

#include "QCapEtherPacket.h"

class QCap : public QObject
{
	Q_OBJECT

public:
	QCap( QObject* parent = NULL );
	~QCap();

	QString lookupDevice();

	bool open( QString dev, int snaplen = 65536, bool promisc = true );
	bool close();

	bool setFilter( QString filter );

	void start();
	void stop();

	struct pcap_stat getStats();

	bool isValid();

private:
	// internal packet callback for pre-processing and emitting
	// the signal(s)
	static void packet_callback(unsigned char*, const pcap_pkthdr*, const unsigned char*);

private:
	// buffer for pcap-error-messages
	char 			m_errbuff[PCAP_ERRBUF_SIZE];

	// the actual pcap handle
	pcap_t* 		m_pcapHandle;

	// a notifier to avoid polling
	QSocketNotifier* m_socketNotifier;

	// the used filter
	bpf_program 	m_filter;

private slots:
	// process captured packets
	// TODO: create IP/TCP/UDP packets and emit them
	void pcapDataAvailable(int fd);


signals:
	void packetReady( QSharedPointer<QCapEtherPacket> );
};

#endif
