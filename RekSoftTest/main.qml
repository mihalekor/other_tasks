import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: win
    width: 640
    height: 680
    visible: true
    title: qsTr("Hello RekSoft")

    header: ToolBar{
      height: 50
      ToolButton{
        text: "< Back"
        visible: stackView.depth > 1
        anchors.verticalCenter: parent.verticalCenter
        onClicked: {stackView.pop()}
      }
      Text{
        anchors.centerIn:  parent
        font.pointSize: 16
        text: stackView.currentItem.title
      }
    }

    StackView{
      id: stackView
      anchors.fill: parent
      initialItem: mainPage
    }

    Page {
      id: mainPage
      title: "NASA APIs:"
      signal buttonClicked();
      onButtonClicked:{stackView.push(page2)}

      ColumnLayout
      {
          //anchors.top: parent.top
          id: colay
          spacing: 2
          width: parent.width
          anchors.fill: parent
          anchors.bottomMargin: 500

          ApiButton {
            id: butt1
            set_index:0
            text:"APOD: Astronomy Picture of the Day"
          }

          ApiButton {
            id: butt2
            set_index:1
            text:"Asteroids: NeoWs"
          }

          ApiButton {
            id: butt3
            set_index:2
            text:"DONKI: Space Weather Database"
          }

          ApiButton {
            id: butt4
            set_index:3
            text:"Earth: Landsat imagery"
          }

          ApiButton {
            id: butt5
            set_index:4
            text:"EPIC: Earth Polychromatic Imaging Camera"
          }      
      }
    }

    ApiPage {
      id: page1
      visible: false
    }
}

