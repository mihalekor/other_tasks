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
  property int index: 0
  property alias set_index: root.index
  
  onClicked:{
    page1.setReplyText = "Push \"Request\" (timeout = 7s)"
    page1.setCommentText = "Enter a comment"
    page1.setTitle = text
    stackView.push(page1);
    var ApiInfo = getApiInfo(index)
    page1.setDescriptionText = ApiInfo[0]  // description
    page1.setUrlText = ApiInfo[1]                       // url
  }
}
