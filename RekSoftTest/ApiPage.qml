import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Page{
  id: root
  title: "title"
  property alias buttonText: navButton.text
  property alias setTitle: root.title
  property alias setUrlText: urltxt.text
  property alias setDescriptionText: description.text

  signal buttonClicked();
  onButtonClicked:{stackView.pop()}

  ColumnLayout
  {
      function scroll_to_bottom() {
          flickabe_item.contentY = 
              Math.max(0, webview_item.height - flickabe_item.height);
          return;
      }
      //anchors.top: parent.top
      id: colay
      spacing: 2
      width: parent.width
      anchors.fill: parent
      anchors.bottomMargin: 100

    Text {
        id: description
        font.pointSize: 12
        Layout.margins: 10
        Layout.fillWidth: parent.width
        wrapMode: Text.WordWrap
    }

    Text {
        id: urltxt
        font.bold: true
        font.pointSize: 12
        Layout.margins: 10 
        Layout.fillWidth: parent.width
        wrapMode: Text.WordWrap
    }
        
    /*Text {
        id: replytxt
        font.pointSize: 12
        Layout.margins: 10
        Layout.fillWidth: parent.width 
        wrapMode: Text.WordWrap
        text: "reply JSON:"
    }*/
    
    Rectangle {
        height: parent.height/2
        Layout.fillWidth: parent.width
        Layout.margins: 10
        //anchors.fill: flickable2
        
        Flickable {
            id: flickable2
            anchors.fill: parent
            width: parent.width
            height: Math.min(contentHeight, 300)
            contentWidth: width
            contentHeight: replytxt.implicitHeight
      
            TextArea.flickable: TextArea {
                id: replytxt//textArea
                text: qsTr("Get Request (timeout = 10s)! ")
                wrapMode: Text.WordWrap
            }
            ScrollBar.vertical: ScrollBar {}
        }
    }

    Rectangle {
      //width: 220
      height: 60
      color: "lightgray"
      Layout.fillWidth: parent.width
      Layout.margins: 10
      
      TextEdit {
        id: edittxt 
        anchors.fill: parent
        //Layout.minimumWidth: 20
        font.bold: true
        font.pointSize: 12
        Layout.margins: 10
        Layout.fillWidth: parent.width
        wrapMode: TextEdit.WordWrap
        text: "Enter a comment"
      }
    }
  }

  RowLayout
  {
      id: rolay
      spacing: 10
      //width: parent.width
      anchors.bottom: parent.bottom
      anchors.right: parent.right
      layoutDirection: Qt.RightToLeft

  Button{
    id: getHttp
    text:"Request"//urltxt.text
    Layout.margins: 10
    onClicked: {
        replytxt.text=qsTr(reqestFromQml(urltxt.text))}
  }

  Button{
    id: save
    text:"Save"
    Layout.margins: 10
    onClicked: {clickSaveFromQml(edittxt.text)}
  }

  Button{
    id: navButton
    text:"Load"
    Layout.margins: 10
    onClicked: {replytxt.text=qsTr(clickLoadFromQml(urltxt.text));
                edittxt.text=qsTr(clickLoadCommFromQml(urltxt.text))}
  }
  }
}

    //onClicked: {root.color = Qt.rgba(Math.random(), Math.random(), Math.random());}
    //anchors.centerIn: parent
/*
Text {
    id: description
  //y:50
    width: 50
    font.pointSize: 10
    anchors.right: parent.right
    Layout.alignment
    anchors.margins: 10
    anchors.topMargin: 20
    wrapMode: Text.WordWrap
}


        //Layout.maximumWidth: parent.width-20
*/
