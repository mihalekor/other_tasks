import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15


Page{
  id: root
  property alias buttonText: navButton.text
  signal buttonClicked();
  onButtonClicked:{stackView.pop()}

  Button{
    id: navButton
    text:"navButton"
    //anchors.centerIn: parent
    y: 50
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.margins: 10
    onClicked: {root.buttonClicked();}
  }
}
