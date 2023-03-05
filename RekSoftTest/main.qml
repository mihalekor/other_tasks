import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: win
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello RekSoft")

    StackView{
      id: stackView
      anchors.fill: parent
      initialItem: mainPage
    }

    Page {
      id: mainPage
      signal buttonClicked();

      onButtonClicked:{stackView.push(page2)}

      Text {
          id: caption
          y:10
          width: 50
          anchors.right: parent.right
          anchors.left: parent.left
          anchors.margins: 140
          text: qsTr("NASA APIs:")
      }

      ApiButton {
          id: butt1
          y: 50
          text:"Astronomy Picture of the Day"
          //onClicked: {root.buttonClicked();}
      }

      ApiButton {
          id: butt2
          y: 100
          text:"Astronomy Picture of the Day2"
          //onClicked: {root.buttonClicked();}
      }

    }

    ApiPage {
      id: page1
      visible: false
    }

    ApiPage {
      id: page2
      visible: false
    }

    /*Item {
      id: root
      x: 100
      y: 200
      property int size: 100
      property color color: "lightgrey"
      }
      */

    //onClicked: {win.color = Qt.rgba(Math.random(), Math.random(), Math.random());}
}

