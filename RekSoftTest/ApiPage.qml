import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15


Page{
  id: root
  property alias buttonText: navButton.text
  property alias urlText: urltxt.text

  signal buttonClicked();
  onButtonClicked:{stackView.pop()}

  Text {
      id: urltxt
      y:10
      width: 50
      anchors.right: parent.right
      anchors.left: parent.left
      anchors.margins: 10
  }

  Button{
    id: getHttp
    text:"Reqest JSON"//urltxt.text
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.margins: 10
    onClicked: {}
  }

  Button{
    id: save
    text:"Save"
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.margins: 10
    anchors.leftMargin: 120
    onClicked: {}
  }

  Button{
    id: navButton
    text:"Back"
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.margins: 10
    onClicked: {root.buttonClicked();}
  }
}

    //onClicked: {root.color = Qt.rgba(Math.random(), Math.random(), Math.random());}
    //anchors.centerIn: parent
