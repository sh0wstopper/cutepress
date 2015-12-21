import bb.cascades 1.3
import "UIConstants.js" as UI

Tab {
    id: iTab
    property alias initialContent: initialPage.content
    property alias initialActions: initialPage.actions
    function push(iPage) {
        navigationPane.push(iPage)
    }
    function pop(iPage) {
        navigationPane.pop(iPage)
    }
    function count() {
        return navigationPane.count()
    }
    function top() {
        return navigationPane.top
    }
    function navigateToFirst() {
        navigationPane.navigateTo(navigationPane.at(0))
    }
    onTriggered: {
        if(mainWindow.activeTab==pagesTab )
            iList.scrollToTop();
        else {
//            if(oauth.isAuthorized) {
//                if(cpUtil.pagesState==UI.ProgressState.None || cpUtil.pagesState==UI.ProgressState.Error) {
//                    cpUtil.fetchPosts()
//                }
//            }
        } 
    }
    NavigationPane { 
        id: navigationPane
        onTopChanged: {
//            if (count() == 1 && oauth.state == OAuth.UserAuthorizes) oauth.unauthorize();
        }
        onPopTransitionEnded: { page.destroy(); }
        Page {
            id: initialPage
            
            actions: [
                ActionItem {
                    title: qsTr("Refresh")
                    imageSource: "asset:///images/refresh.png"
//                    enabled: oauth.state==OAuth.Authorized
                    onTriggered: {
                        cpUtil.fetchPages()
                    }
                    ActionBar.placement: ActionBarPlacement.InOverflow
                }
            ]
            titleBar: ButtonTitleBar {
                titleText: qsTr("Pages")//qsTr("%1::Posts").arg(cpUtil.name==""?oauth.blogId:cpUtil.name)
                defaultImgSource: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?"asset:///images/toolbarcompose-black.png":"asset:///images/toolbarcompose.png"
                pressedImgSource: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?"asset:///images/toolbarcompose-black.png":"asset:///images/toolbarcompose.png"
                buttonEnabled: cpUtil.blogs.size()>0
                onButtonClicked: {
                    mainWindow.openNewPageEditor()
                }
            }
            content: Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                layout: StackLayout {}
                
                PageStatusContainer {
                    visible: cpUtil.pagesState==UI.ProgressState.Processing || (cpUtil.pagesState == UI.ProgressState.Success && cpUtil.pages.size() == 0)
                    indicatorVisible: cpUtil.pagesState==UI.ProgressState.Processing
                    labelVisible: cpUtil.pagesState==UI.ProgressState.Error || (cpUtil.pagesState == UI.ProgressState.Success && cpUtil.pages.size() == 0)
                    labelText: cpUtil.pagesStatus
                }
                
                PagePagesListView {
                    id: iList
                    dataModel: cpUtil.pages
                    onFlickedAtEnd: {
                    }
                }
//                ActivityIndicatorLarge {
//                    visible: cpUtil.pages.size() == 0 && cpUtil.pagesState==UI.ProgressState.Processing
//                }
//                PageProgressStatusLabel {
//                    visible: cpUtil.pagesState == UI.ProgressState.Error || (cpUtil.pagesState == UI.ProgressState.Success && cpUtil.pages.size() == 0)
//                    text: (cpUtil.pagesState == UI.ProgressState.Success && cpUtil.pages.size() == 0) ? qsTr("No pages") : cpUtil.pagesStatus
//                }
            } 
            shortcuts: [
                SystemShortcut {
                    type: SystemShortcuts.CreateNew
                    enabled: cpUtil.blogs.size()>0
                    onTriggered: {               
                        mainWindow.openNewPageEditor()
                    }
                }
            ] 
            onCreationCompleted: {
                //                if(oauth.isAuthorized) {
                //                    if(cpUtil.pagesState==UI.ProgressState.None || cpUtil.pagesState==UI.ProgressState.Error) {
                //                        cpUtil.fetchPosts()
                //                    }
                //                }
            }                  
        }
    }
}
