import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Button{
  id: root
  text:"Astronomy Picture of the Day"
  //anchors.centerIn: parent
  /*anchors.right: parent.right
  anchors.left: parent.left
  anchors.margins: 140
  anchors.topMargin:0
  anchors.bottomMargin: 20*/
  Layout.margins: 10
  Layout.alignment: Qt.AlignCenter
  Layout.minimumWidth: parent.width/2
}
