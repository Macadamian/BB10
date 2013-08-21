#include "CocosApp.h"
#include "AppDelegate.h"
#include <bb/cascades/Application>
#include <bb/cascades/Window>

using namespace bb::cascades;

CocosApp::CocosApp() {
}

CocosApp::~CocosApp() {
    delete appDel;
}

void CocosApp::run() {
    // create the application instance
    appDel = new AppDelegate();
    QString s = Application::instance()->mainWindow()->groupId();
    m_eglView = CCEGLView::sharedOpenGLView(s.toAscii().constData());
    m_eglView->setFrameSize(768, 1138);
    m_CCapp = CCApplication::sharedApplication();
    m_eglView->setZOrder(5);
    m_CCapp->run();
    emit finished();
}

CCEGLView* CocosApp::getEGLView() {
    return m_eglView;
}
