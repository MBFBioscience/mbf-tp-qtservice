
#ifndef QTSERVICE_QOBJECTS_H
#define QTSERVICE_QOBJECTS_H

#include <QtCore/QObject>
#include "qtservice_p.h"

class QtServiceStarter : public QObject
{
	Q_OBJECT
public:
	QtServiceStarter(QtServiceBasePrivate *service)
		: QObject(), d_ptr(service) {}
	public slots :
		void slotStart()
	{
		d_ptr->startService();
	}
private:
	QtServiceBasePrivate *d_ptr;
};

#endif