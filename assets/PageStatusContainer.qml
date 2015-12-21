import bb.cascades 1.3
import "UIConstants.js" as UI

Container {
    property alias indicatorVisible: indicator.visible
    property alias labelVisible: label.visible
    property alias labelText: label.text
    horizontalAlignment: HorizontalAlignment.Fill
    background: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?
                Color.create("#f8f8f8"):
                Color.create("#484848")
    layout: DockLayout {}
    topPadding: ui.sdu(1)
    bottomPadding: ui.sdu(1)
    leftPadding: ui.sdu(1)
    rightPadding: ui.sdu(1)                
    ActivityIndicatorSmall {
        id: indicator
    }
    PageProgressStatusLabelSmall {
        id: label
    }
}
