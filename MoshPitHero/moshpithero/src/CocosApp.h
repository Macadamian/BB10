#ifndef _CocosApp_H_
#define _CocosApp_H_

#include "cocos2d.h"
#include <QObject>

class AppDelegate;
USING_NS_CC;

class CocosApp: public QObject {
Q_OBJECT

    AppDelegate* appDel;
    CCApplication* m_CCapp;
    CCEGLView* m_eglView;

public:
	CocosApp();
	~ CocosApp();
    CCEGLView* getEGLView();

public slots:
	void run();

signals:
    void finished();
};

#endif // ifndef _CocosApp_H_
