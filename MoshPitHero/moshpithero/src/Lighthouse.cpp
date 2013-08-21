// Default empty project template
#include "Lighthouse.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/platform/Notification>
#include <bb/platform/NotificationDialog>
#include <bb/platform/NotificationError>
#include <bb/platform/NotificationResult>

#include "CocosApp.h"
#include "InvocationWrapper.hpp"
#include "Calendar.hpp"
#include "CocosEventHandler.h"

using namespace bb::cascades;
using namespace bb::platform;

Lighthouse::Lighthouse(bb::cascades::Application *app)
: QObject(app)
{
    qmlRegisterType<InvocationWrapper>("lighthouse.app", 1, 0, "InvocationWrapper");
    qmlRegisterType<Calendar>("lighthouse.app", 1, 0, "Calendar");
    qmlRegisterType<bb::platform::Notification>("lighthouse.app", 1, 0, "Notification");
    qmlRegisterType<bb::platform::NotificationDialog>("lighthouse.app", 1, 0, "NotificationDialog");
    qmlRegisterUncreatableType<bb::platform::NotificationError>("lighthouse.app", 1, 0, "NotificationError", "");
    qmlRegisterUncreatableType<bb::platform::NotificationResult>("lighthouse.app", 1, 0, "NotificationResult", "");
    qmlRegisterType<QTimer>("lighthouse.app", 1, 0, "QTimer");

    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_lightHouse", this);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

	// set created root object as a scene
	app->setScene(root);

	mCocosThread = new QThread;
	m_CCApp = new CocosApp();
	m_CCApp->moveToThread(mCocosThread);
    m_CCApp->setParent(this);
	connect(mCocosThread, SIGNAL(started()), m_CCApp, SLOT(run()));
	connect(m_CCApp, SIGNAL(finished()), mCocosThread, SLOT(quit()));
	connect(m_CCApp, SIGNAL(finished()), m_CCApp, SLOT(deleteLater()));
	connect(mCocosThread, SIGNAL(finished()), mCocosThread, SLOT(deleteLater()));
	mCocosThread->start();

	CocosEventHandler* CCEH= CocosEventHandler::getInstance();
	CCEH->moveToThread(mCocosThread);
	connect(CCEH, SIGNAL(tweet(QString, QString)), this, SIGNAL(tweet(QString, QString)), Qt::QueuedConnection);
	connect(CCEH, SIGNAL(buddy(QString)), this, SIGNAL(buddy(QString)), Qt::QueuedConnection);
	connect(CCEH, SIGNAL(star(QString)), this, SIGNAL(star(QString)), Qt::QueuedConnection);
	connect(CCEH, SIGNAL(stage(QString, QString)), this, SIGNAL(stage(QString, QString)), Qt::QueuedConnection);
	connect(CCEH, SIGNAL(reset()), this, SIGNAL(reset()), Qt::QueuedConnection);

    mInvokeManager = new InvokeManager(this);
    connect(mInvokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)),
            SLOT(onInvoked(const bb::system::InvokeRequest&)));
}

void Lighthouse::onInvoked(const InvokeRequest& req)
{
    qDebug("onInvoked");
}

void Lighthouse::showCocos()
{
    m_CCApp->getEGLView()->setZOrder(5);
}

void Lighthouse::hideCocos()
{
    m_CCApp->getEGLView()->setZOrder(-5);
}
