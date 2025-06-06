#ifndef QTSERVICE_SYS_PRIV
#define QTSERVICE_SYS_PRIV

#include "qtunixserversocket.h"

class QtServiceSysPrivate : public QtUnixServerSocket
{
    Q_OBJECT
public:
    QtServiceSysPrivate();
    ~QtServiceSysPrivate();

    char *ident;

    QtServiceBase::ServiceFlags serviceFlags;

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void slotReady();
    void slotClosed();

private:
    QString getCommand(const QTcpSocket *socket);
    QMap<const QTcpSocket *, QString> cache;
};

#endif

