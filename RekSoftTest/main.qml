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
          //y: 50
          text:"Astronomy Picture of the Day"
          onClicked: {
              page1.setTitle = text
              page1.setDescriptionText = "Этот метод структурирует изображения APOD и связанные с ними метаданные, чтобы их можно было использовать для других приложений. Кроме того, если concept_tagsдля параметра установлено значениеTrue, то возвращаются ключевые слова, полученные из пояснения к изображению. Эти ключевые слова можно использовать в качестве автоматически сгенерированных хэштегов для каналов Twitter или Instagram; но в целом они помогают обнаруживать соответствующие изображения."
              page1.setUrlText=qsTr("https://api.nasa.gov/planetary/apod?api_key=wKXJIhhJo58U4QeF9RrU00qsJhHfd6iWk3pjyBaa");
              //page1.setUrlText=qsTr("https://world.openfoodfacts.org/api/v0/product/737628064502.json");
              
              stackView.push(page1);
          }
      }

      ApiButton {
          id: butt2
          //y: 100
          text:"Asteroids - NeoWs"
          onClicked: {
              page1.setTitle = text
              page1.setDescriptionText = "NeoWs (Near Earth Object Web Service) - это веб-сервис RESTful для получения информации об астероидах, сближающихся с Землей. С помощью NeoWs пользователь может: искать астероиды на основе даты их ближайшего сближения с Землей, искать конкретный астероид с его идентификатором малого тела NASA JPL, а также просматривать общий набор данных."
              page1.setUrlText=qsTr("https://api.nasa.gov/neo/rest/v1/feed?start_date=2015-09-07&end_date=2015-09-08&api_key=DEMO_KEY");
              stackView.push(page1);}
      }


      ApiButton {
          id: butt3
          //y: 100
          text:"DONKI"
          onClicked: {
              page1.setTitle = text
              page1.setDescriptionText = ""
              page1.setUrlText=qsTr("https://api.nasa.gov/DONKI/CME?startDate=2017-01-03&endDate=2017-01-03&api_key=DEMO_KEY");
              stackView.push(page1);}
      }
      ApiButton {
          id: butt4
          //y: 100
          text:"Earth"
          onClicked: {
              page1.setTitle = text
              page1.setDescriptionText = ""
              page1.setUrlText=qsTr("https://api.nasa.gov/DONKI/CME?startDate=2017-01-03&endDate=2017-01-03&api_key=DEMO_KEY");
              stackView.push(page1);}
      }

      ApiButton {
          id: butt5
          //y: 100
          text:"EONET"
          onClicked: {
              page1.setTitle = text
              page1.setDescriptionText = ""
              page1.setUrlText=qsTr("https://world.openfoodfacts.org/api/v0/product/737628064502.json");
              stackView.push(page1);}
      }

      
      

      
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

