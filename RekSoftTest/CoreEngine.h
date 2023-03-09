#ifndef COREENGINE_H
#define COREENGINE_H

//#include <QNetworkAccessManager>
#include <QObject>
#include <QTextCodec>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtSql>
#include <vector>

class CoreEngine : public QObject
{

  Q_OBJECT
public:
  explicit CoreEngine(QObject *parent = nullptr);
  Q_INVOKABLE QString clickRequest(QString n);
  Q_INVOKABLE int clickSaveFromQml(QString jsonSave, QString comment);
  Q_INVOKABLE QStringList clickLoadFromQml();
  Q_INVOKABLE QStringList getApiInfo(int n);

private:
  QNetworkAccessManager manager;
  QSqlDatabase sdb;
  int currentElementApi;

  enum NASAapi
  {
    APOD = 1,
    Asteroids,
    DONKI,
    Earth,
    EPIC
  };

  struct apiInfo
  {
    QString description;
    QString url;
  };

  QString apiKey = "DEMO_KEY"; // DEMO_KEY  //wKXJIhhJo58U4QeF9RrU00qsJhHfd6iWk3pjyBaa
  const std::vector<apiInfo> vecApiInfos = {

      {// APOD: Astronomy Picture of the Day
       //  description
       "Cтруктурирует изображения APOD и связанные с ними метаданные, чтобы их можно было "
       "использовать для других приложений. Кроме того, если concept_tagsдля параметра установлено значениеTrue, то "
       "возвращаются ключевые слова, полученные из пояснения к изображению. Эти ключевые слова можно использовать в "
       "качестве автоматически сгенерированных хэштегов для каналов Twitter или Instagram; но в целом они помогают "
       "обнаруживать соответствующие изображения.",
       // url
       "https://api.nasa.gov/planetary/apod?api_key=" + apiKey},

      {// Asteroids: NeoWs
       //  description
       "NeoWs (Near Earth Object Web Service) - это веб-сервис RESTful для получения информации об астероидах, "
       "сближающихся с Землей. С помощью NeoWs пользователь может: искать астероиды на основе даты их ближайшего "
       "сближения с Землей, искать конкретный астероид с его идентификатором малого тела NASA JPL, а также "
       "просматривать общий набор данных.",
       // url
       "https://api.nasa.gov/neo/rest/v1/feed?start_date=2015-09-07&end_date=2015-09-08&api_key=" + apiKey},

      {// DONKI: Space Weather Database
       //  description
       "База данных уведомлений, знаний и информации о космической погоде (DONKI) это комплексный онлайновый "
       "инструмент для прогнозистов космической погоды, ученых и всего научного сообщества в области космонавтики. "
       "DONKI ведет хронику ежедневных интерпретаций наблюдений за космической погодой, анализа, моделей, прогнозов и "
       "уведомлений, предоставляемых Центром исследований космической погоды (SWRC).\nГеомагнитная буря (GST):",
       // url
       "https://api.nasa.gov/DONKI/GST?startDate=2016-01-01&endDate=2016-01-30&api_key=" + apiKey},

      {// Earth: Landsat imagery
       //  description
       "Снимки Landsat предоставляются общественности в рамках совместного проекта НАСА и Геологической службы США. "
       "Недавняя отрасль Сообщить по данным спутниковых снимков landsat, общая годовая стоимость для экономики "
       "составляет 2,19 миллиарда долларов, что намного превышает многолетние общие затраты на создание, запуск и "
       "управление спутниками и датчиками Landsat. ",
       // url
       "https://api.nasa.gov/planetary/earth/imagery?lon=-95.33&lat=29.78&date=2018-01-01&dim=0.15&api_key=" + apiKey},

      {// EPIC: Earth Polychromatic Imaging Camera
       //  description
       "API EPIC предоставляет информацию о ежедневных снимках, собираемых прибором DSCOVR Earth Polychromatic Imaging "
       "Camera (EPIC). Уникально расположенный в точке Лагранжа Земля-Солнце, EPIC обеспечивает полное изображение "
       "диска Земли и захватывает уникальные перспективы определенных астрономических событий",
       // url
       "https://api.nasa.gov/neo/rest/v1/feed?start_date=2015-09-07&end_date=2015-09-08&api_key=" + apiKey}};
};

#endif // COREENGINE_H
