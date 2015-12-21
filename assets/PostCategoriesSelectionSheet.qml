import bb.cascades 1.3
import bb.cascades.pickers 1.0
import "UIConstants.js" as UI

CutePressSheet {
    id: iSheet
    property variant caller: 0
    content: Page {
        titleBar: TitleBar {
            title: qsTr("Select categories")
            acceptAction: ActionItem {
                title: qsTr("Ok")
                onTriggered: {
                    caller.getMarkedCategoriesFromModel()
                    iSheet.close()
                }
            } // ActionItem
            dismissAction: ActionItem {
                title: qsTr("Cancel")
                onTriggered: {
                    iSheet.close()
                }
            } // ActionItem
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            layout: DockLayout {}
            
            CutePressListView {
                id: iList
                dataModel: cpUtil.categories              
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                
                listItemComponents: [
                    ListItemComponent {
                        id: listComponent
                        type: "item"
                        Container {
                            id: rootContainer
                            horizontalAlignment: HorizontalAlignment.Fill
                            verticalAlignment: VerticalAlignment.Fill
                            property bool isHighlighted
                            
                            layout: DockLayout {
                            }
                            
                            Container {
                                background: Color.Cyan
                                opacity: 0.8
                                visible: ListItemData.categoryMarked
                                horizontalAlignment: HorizontalAlignment.Fill
                                verticalAlignment: VerticalAlignment.Fill
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                layout: StackLayout {}
                                Container {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    topPadding: ui.sdu(1.5)
                                    bottomPadding: topPadding
                                    leftPadding: ui.sdu(2)
                                    rightPadding: leftPadding
                                    layout: StackLayout {}
                                    Label {
                                        text: ListItemData.categoryName
                                        textStyle.fontWeight: FontWeight.Bold
                                        textFormat: TextFormat.Html
                                        multiline: true
                                    }
                                }
                                Divider {}
                            }
                            
                            // A colored Container is used to highlight the item on selection.
                            Container {
                                id: highlight
                                background: Color.Gray
                                opacity: rootContainer.isHighlighted   ? 0.8: 0.0
                                horizontalAlignment: HorizontalAlignment.Fill
                                verticalAlignment: VerticalAlignment.Fill
                            }
                            
                            // Both the activation and selection of an item has the same visual appearance, we alter the opacity of the item.
                            function setHighlight(highlighted) {
                                rootContainer.isHighlighted = highlighted
                            }
                            
                            // Signal handler for ListItem activation
                            ListItem.onActivationChanged: {
                                setHighlight(ListItem.active);
                            }
                            
                            // Signal handler for ListItem selection
                            ListItem.onSelectionChanged: {
                                setHighlight(ListItem.selected);
                            }
                        }
                    }
                ]
                onTriggered: {
                    var currentItem = dataModel.data(indexPath)
                    console.log("Mark/unmark categories", indexPath, currentItem.categoryMarked)
                    if(!currentItem.categoryMarked)
                        cpUtil.markCategoryInModel(indexPath)
                    else
                        cpUtil.unmarkCategoryInModel(indexPath)
                }
            }
        }
    }    
}