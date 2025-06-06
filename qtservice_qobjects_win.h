
#ifndef QTSERVICE_QOBJECTS_WIN_H
#define QTSERVICE_QOBJECTS_WIN_H

#include <QObject>

class QtServiceControllerHandler : public QObject
{
	Q_OBJECT
public:
	QtServiceControllerHandler(QtServiceSysPrivate *sys);

protected:
	void customEvent(QEvent *e);

private:
	QtServiceSysPrivate *d_sys;
};


#endif