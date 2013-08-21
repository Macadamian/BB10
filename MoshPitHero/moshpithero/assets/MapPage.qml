import bb.cascades 1.0
import lighthouse.app 1.0

Page {
    property int schedule: 0
    
    id: map
    titleBar: TitleBar {
        kind: TitleBarKind.Segmented
        options: [
            Option {
                text: qsTr("Map")
                value: "map"
            }, 
            Option {
                text: qsTr("List")
                value: "list"
            }
        ]
    }
    Container {
        layout: AbsoluteLayout {}
        // The map!
        ImageView {
            imageSource: "asset:///images/map_flattened.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 0.0
                positionY: 0.0
            }
        }
        // the pins
        ImageView {
            id: pin0
            imageSource: "asset:///images/pin0.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 350.0
                positionY: -110.0
            }
        }
        ImageView {
            id: pin1
            imageSource: "asset:///images/pin1.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 180.0
                positionY: -110.0
            }
        }
        ImageView {
            id: pin2
            imageSource: "asset:///images/pin2.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 380.0
                positionY: -110.0
            }
        }
        ImageView {
            id: pin3
            imageSource: "asset:///images/pin3.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 500.0
                positionY: -110.0
            }
        }
        ImageView {
            id: pin4
            imageSource: "asset:///images/pin4.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 430.0
                positionY: -110.0
            }
        }
        ImageView {
            id: pin5
            imageSource: "asset:///images/pin5.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 270.0
                positionY: -110.0
            }
        }
        ImageView {
            id: pin6
            imageSource: "asset:///images/pin6.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 400.0
                positionY: -110.0
            }
        }
        ImageView {
            id: pin7
            imageSource: "asset:///images/pin7.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 520.0
                positionY: -110.0
            }
        }
        ImageView {
            id: pin8
            imageSource: "asset:///images/pin8_Vivek.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 600.0
                positionY: -110.0
            }
        }
    }
    attachedObjects: [
        AnimationPinDrop {
            id: pinDrop
        },
        QTimer {
            id: animationTimeout
            singleShot: true
            interval: 1000
            onTimeout: {
                animationTimeout.interval = animationTimeout.interval - 100;
                nextPin();
            }
        }
    ]
    actions: [
        ActionItem {
            id: onMe
            title: qsTr("Center on me")
            imageSource: "asset:///images/Menu Icons/ShowOnMap.png"
            ActionBar.placement: ActionBarPlacement.OnBar
        }
    ]    
    
    function nextPin() {
        switch (schedule) {
            case 0:
                dropPin(pin0, 600);
                break;
            case 1:
                dropPin(pin1, 800);
                break;
            case 2:
                dropPin(pin2, 900);
                break;
            case 3:
                dropPin(pin3, 120);
                break;
            case 4:
                dropPin(pin4, 220);
                break;
            case 5:
                dropPin(pin5, 500);
                break;
            case 6:
                dropPin(pin6, 400);
                break;
            case 7:
                dropPin(pin7, 440);
                break;
            case 8:
                dropPin(pin8, 540);
                break;
            default:
                break;
        }
    }
    
    function dropPin(target, dropSpot) {
        pinDrop.setTarget(target);
        pinDrop.toY = dropSpot;
        pinDrop.play();
        schedule++;
        pinDrop.factor = pinDrop.factor - 0.1;
        animationTimeout.start();
    }    
}
