#ifndef PACKETINFOPRINTER_H_
#define PACKETINFOPRINTER_H_

#include "QCap.h"
#include "QCapEtherPacket.h"

#include <QSharedPointer>
#include <QObject>

class PacketInfoPrinter : public QObject
{
	Q_OBJECT

public slots:
	void printInfo( QSharedPointer<QCapEtherPacket> packet );
};

#endif
