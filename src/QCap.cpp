#include "QCap.h"
#include "QCapEtherPacket.h"

#include <pcap.h>

QCap::QCap( QObject* parent )
	: QObject( parent )
{
	m_pcapHandle = NULL;
	m_socketNotifier = NULL;
}

QString QCap::lookupDevice()
{
	char* device = pcap_lookupdev( m_errbuff );
	if (!device)
		return QString();

	return QString::fromLocal8Bit( device );
}


bool QCap::open( QString dev, int snaplen, bool promisc )
{
	m_pcapHandle = pcap_open_live( dev.toLocal8Bit().constData(),
					snaplen,
					promisc,
					PCAP_TIMEOUT,
					m_errbuff );

	return isValid();
}

bool QCap::close()
{
	if (!isValid()) return false;
	if (m_socketNotifier)
		stop();

	pcap_close( m_pcapHandle );
	m_pcapHandle = NULL;

	return true;
}

bool QCap::setFilter( QString filter )
{
	int ok = pcap_compile( m_pcapHandle, &m_filter,
					filter.toLocal8Bit().constData(), 0, 0 );

	if (ok != 0) return false;

	ok = pcap_setfilter( m_pcapHandle, &m_filter );
	if (ok != 0) return false;

	return true;
}

void QCap::start()
{
	if (!isValid()) return;

	int fd = pcap_get_selectable_fd( m_pcapHandle );

	m_socketNotifier = new QSocketNotifier( fd, QSocketNotifier::Read, this );

	connect( m_socketNotifier, SIGNAL(activated(int)),
			this, SLOT(pcapDataAvailable(int)) );

	m_socketNotifier->setEnabled( true );
}

void QCap::stop()
{
	if (!isValid()) return;

	pcap_breakloop( m_pcapHandle );

	delete m_socketNotifier;
	m_socketNotifier = NULL;
}

void QCap::pcapDataAvailable(int fd)
{
	/* pcap_dispatch calls a callback function for every
	 * packet available. But since this cannot be a member
	 * function, we will make it static and provide the
	 * this-pointer as an argument. The callback can then
	 * cast it to a QCap-pointer.
	 */
	pcap_dispatch( m_pcapHandle, -1, (pcap_handler) &QCap::packet_callback, (unsigned char*) this );
}

// static packet processing method, the callback
void QCap::packet_callback( unsigned char* selfpointer,
				const struct pcap_pkthdr* header,
				const unsigned char* packet )
{
	QCap* self = reinterpret_cast<QCap*>( selfpointer );

	// after this callback, pcap might get the next
	// packet from its internal buffer, hence making
	// the current *packet invalid / overwriting it.
	//
	// the good news is: we don't need to free *packet
	// 					ourselves.
	//
	// the bad new is: the data is not guaranteed to
	// 					be valid when we simply emit *packet.
	//
	// the solution?
	// We are going to create our own packet-class
	// with the ability to convert it to IP/TCP/UDP-packets
	// and hand out a shared pointer.
	
	QSharedPointer<QCapEtherPacket> data( new QCapEtherPacket( packet, header->caplen ) );

	self->emit packetReady( data );
}

struct pcap_stat QCap::getStats()
{
	struct pcap_stat stat;
	pcap_stats(m_pcapHandle, &stat);

	return stat;
}

bool QCap::isValid()
{
	return (m_pcapHandle != NULL);
}

QCap::~QCap()
{
	close();
}
