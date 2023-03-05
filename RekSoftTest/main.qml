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
          onClicked: {
              page1.urlText=qsTr("NASA APIs: GET https://api.nasa.gov/planetary/apod");
              stackView.push(page1);}
      }

      ApiButton {
          id: butt2
          y: 100
          text:"Asteroids - NeoWs"
          onClicked: {
              page1.urlText=qsTr("NASA APIs: https://api.nasa.gov/neo/rest/v1/feed?start_date=2015-09-07&end_date=2015-09-08&api_key=DEMO_KEY");
              stackView.push(page1);}
      }

    }

    ApiPage {
      id: page1
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

