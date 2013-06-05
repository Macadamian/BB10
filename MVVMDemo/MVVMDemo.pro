APP_NAME = MVVMDemo

CONFIG += qt warn_on cascades10 network

LIBS += -lbbmultimedia
LIBS += -lcrypto
LIBS += -lpps
LIBS += -lcurl
LIBS += -lcsm
LIBS += -lbbdevice
LIBS += -lbbsystem
LIBS += -lbbdata
LIBS += -lbb
LIBS += -lbbplatform
LIBS += -lbbpim
LIBS += -lbbcascadesmaps 
LIBS += -lQtLocationSubset 
LIBS += -lGLESv1_CM
LIBS += -lbbutility

QT += network core gui xml


include(config.pri)

device {
    CONFIG(debug, debug|release) {
        # Device-Debug custom configuration
    }

    CONFIG(release, debug|release) {
        # Device-Release custom configuration
    }
}

simulator {
    CONFIG(debug, debug|release) {
        # Simulator-Debug custom configuration
    }
}
