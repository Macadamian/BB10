// Default empty project template
#ifndef Lighthouse_HPP_
#define Lighthouse_HPP_

#include <QObject>
#include <QThread>
#include <bb/cascades/Application>
#include <bb/system/InvokeManager>

class CocosApp;
using namespace bb::cascades;
using namespace bb::system;

namespace bb {
namespace cascades {
class Application;
class Page;
}
}

class Lighthouse: public QObject {
Q_OBJECT
public:

    Lighthouse(bb::cascades::Application *app);
    virtual ~Lighthouse(){}

public Q_SLOTS:
    void onInvoked(const bb::system::InvokeRequest& req);
    void showCocos();
    void hideCocos();

signals:
    void tweet(QString, QString);
    void buddy(QString);
    void star(QString);
    void stage(QString, QString);
    void reset();

private:
    InvokeManager* mInvokeManager;
    QThread* mCocosThread;
    CocosApp* m_CCApp;
};

#endif /* Lighthouse_HPP_ */
