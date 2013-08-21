// Default empty project template
import bb.cascades 1.0

TabbedPane {
    Tab {
        id: aroundMeTab
        title: qsTr("Around Me")
        imageSource: "asset:///images/Menu Icons/AroundMe.png"
        AroundMePage {            
            objectName: "aroundMePage"
        }
    }
    Tab {
        imageSource: "asset:///images/Menu Icons/Stages.png"
        title: qsTr("Stages")
    }
    Tab {
        imageSource: "asset:///images/Menu Icons/Music.png"
        title: qsTr("Music")
    }
    Tab {
        imageSource: "asset:///images/Menu Icons/Contacts.png"
        title: qsTr("Friends")
        MapPage {
            id:mapPage
        }
    }
    Tab {
        imageSource: "asset:///images/Menu Icons/Conversations.png"
        title: qsTr("Converstation")
    }
    Tab {
        imageSource: "asset:///images/Menu Icons/ic_info.png"
        title: qsTr("Info")
    }
    /*Tab {        
        title: qsTr("Test")
        Test {}
    }*/
    onActiveTabChanged: {
        if(activeTab.title == "Around Me") _lightHouse.showCocos();
        else _lightHouse.hideCocos();
        if (activeTab.title == "Friends") mapPage.nextPin();
    }
    
    onSidebarVisualStateChanged: {
        if(sidebarVisualState == SidebarVisualState.AnimatingToVisibleFull)
        {
            _lightHouse.hideCocos();
        }
        else if (sidebarVisualState == SidebarVisualState.AnimatingToHidden) {
            if (activeTab.title == "Around Me") _lightHouse.showCocos();
        }
    }   
}
