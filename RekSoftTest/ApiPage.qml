import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Page{
  id: root
  title: "title"
  //property alias buttonText: navButton.text
  property alias setTitle: root.title
  property alias setUrlText: urltxt.text
  property alias setDescriptionText: description.text
  property alias setReplyText: replytxt.text
  property alias setCommentText: edittxt.text

  signal buttonClicked();
  onButtonClicked:{stackView.pop()}
  
  Dialog {
    id: dialogOk
    property alias setLabel: dialogLabel.text
    title: "Save Json and comment:"
      
    anchors.centerIn: parent
      
    contentItem:
    Label {
      id: dialogLabel
      text: qsTr("Save ok!")
      font.pointSize: 12
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
      color: "#ffffff"
      font.bold: true
      padding: 10
      background: 
        Rectangle {
          color: "#353535"
        }
    }
    standardButtons: Dialog.Ok
    implicitWidth: parent.width/2
    implicitHeight: parent.height/4
  }

  ColumnLayout
  {
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
                text: qsTr("Push \"Request\" (timeout = 7s) ")
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
        width: parent.width
        //Layout.minimumWidth: 20
        font.bold: true
        font.pointSize: 12
        Layout.margins: 10
        Layout.fillWidth: parent.width
        wrapMode: TextEdit.WordWrap
        text: "Enter a comment"
      }
    }
    
    Rectangle {
        height: 20
        //color: "lightgray"
        Layout.fillWidth: parent.width
        Layout.margins: 10
      Item {
        Timer {
            interval: 500; running: true; repeat: true
            onTriggered: time.text = Date().toString()
        }
    
        Text { id: time }
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
        replytxt.text=qsTr(clickRequest(urltxt.text))}
   }

    Button{
      id: save
      text:"Save"
      Layout.margins: 10
      onClicked: 
      {
        if(!clickSaveFromQml(replytxt.text, edittxt.text))    
          dialogOk.open()
        else
          dialogOk.setLabel = qsTr("Save Error!")
          dialogOk.open()
      }
    }

    Button{
      id: load
      text:"Load"
      Layout.margins: 10
      onClicked: {
        var loadList = clickLoadFromQml()
        replytxt.text = qsTr(loadList[0])       // json_str
        edittxt.text = qsTr(loadList[1])        // comment
      }
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
