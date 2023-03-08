#include "CoreEngine.h"
#include <QEventLoop>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QTimer>

QJsonDocument loadJson(QString fileName)
{
  QFile jsonFile(fileName);
  jsonFile.open(QFile::ReadOnly);
  return QJsonDocument().fromJson(jsonFile.readAll());
}

void saveJson(QJsonDocument document, QString fileName)
{
  QFile jsonFile(fileName);
  jsonFile.open(QFile::WriteOnly);
  jsonFile.write(document.toJson());
}

CoreEngine::CoreEngine(QObject *parent) : QObject{parent}
{
  manager = new QNetworkAccessManager(this);
  sdb = QSqlDatabase::addDatabase("QSQLITE");
  currentElementApi = 0;
  QString dbName = "infoApi.sqlite";

  if (!QFile::exists(dbName))
  {

    sdb.setDatabaseName(dbName);
    if (!sdb.open())
    {
      qDebug() << sdb.lastError().text();
      qDebug() << sdb.drivers();
    }

    QSqlQuery query(sdb);
    if (!query.exec("CREATE TABLE Json("
                    "title VARCHAR( 2000 ),"
                    "json_str VARCHAR( 2000 ),"
                    "comment VARCHAR( 2000 )," // NOT NULL
                    "date DATE"
                    ")"))
    {
      qDebug() << sdb.lastError().text();
    }

    query.prepare("INSERT INTO Json(title) "
                  "VALUES( :title)");
    query.bindValue(":title", "APOD: Astronomy Picture of the Day");
    query.exec();
    query.prepare("INSERT INTO Json(title) "
                  "VALUES( :title)");
    query.bindValue(":title", "Asteroids: NeoWs");
    query.exec();
    query.prepare("INSERT INTO Json(title) "
                  "VALUES( :title)");
    query.bindValue(":title", "DONKI: Space Weather Database");
    query.exec();
    query.prepare("INSERT INTO Json(title) "
                  "VALUES( :title)");
    query.bindValue(":title", "Earth: Landsat imagery");
    query.exec();
    query.prepare("INSERT INTO Json(title) "
                  "VALUES( :title)");
    query.bindValue(":title", "EPIC: Earth Polychromatic Imaging Camera");

    if (!query.exec())
      qDebug() << query.lastError().text();
  }
  else
  {
    qDebug() << "Data base already exist....";
    sdb.setDatabaseName(dbName);
    if (!sdb.open())
    {
      qDebug() << sdb.lastError().text();
      qDebug() << sdb.drivers();
    }
  }
}

QString CoreEngine::reqestFromQml(QString n)
{

  QString result("No Data!");
  QUrl url(n);
  QNetworkRequest request(url);
  QTimer timer;
  timer.setSingleShot(true);

  QNetworkReply *reply = manager->get(request);

  QEventLoop loop;
  connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  timer.start(10000);
  loop.exec();

  // выводим содержимое
  if (timer.isActive())
  {
    timer.stop();
    if (reply->error() == QNetworkReply::NoError)
    {
      QByteArray content = reply->readAll();
      QTextCodec *codec = QTextCodec::codecForName("utf8"); // cp-1251

      QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();

      // qDebug() << "read all:" << content;

      // Анализ JSON
      QJsonParseError json_error;
      QJsonDocument doucment = QJsonDocument::fromJson(content, &json_error);
      if (json_error.error == QJsonParseError::NoError)
      {
        if (doucment.isObject())
        {
          const QJsonObject obj = doucment.object();
          qDebug() << obj;
          if (obj.contains("args"))
          {
            QJsonValue value = obj.value("args");
            qDebug() << value;
            // QJsonValue(object, QJsonObject({"ie":"utf-8"}))
          }
        }

        saveJson(doucment, "reply_file.json");
      }
      else
      {
        qDebug() << "json error:" << json_error.errorString();
      }

      result = doucment.toJson().data(); // content.data();
    }
    else
      result = reply->errorString();
  }
  else
  {
    // timeout
    disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    reply->abort();
    result = "Error timeout";
  }

  reply->deleteLater();

  return result;
}

int CoreEngine::clickSaveFromQml(QString jsonSave, QString comment)
{
  qDebug() << "clickSaveFromQml";
  /*if (sdb.open())
  {
    QJsonDocument content = loadJson("reply_file.json");
    qDebug() << "content.toJson" << content.toJson().data();
    QSqlQuery query(sdb);
    query.prepare("INSERT INTO Json( json_str, comment, date ) "
                  "   VALUES( :json_str, :comment, :date )");
    query.bindValue(":json_str", jsonSave);
    query.bindValue(":comment", comment);
    query.bindValue(":date", QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
    if (!query.exec())
    {
      qDebug() << sdb.lastError().text();
    }
  }*/
  if (sdb.open())
  {
    QJsonDocument content = loadJson("reply_file.json");
    qDebug() << "content.toJson" << content.toJson().data();
    QSqlQuery query(sdb);
    query.prepare("UPDATE Json SET json_str=:json_str, comment=:comment, date=:date WHERE rowid =:rowid;");
    query.bindValue(":json_str", jsonSave);
    query.bindValue(":comment", comment);
    query.bindValue(":date", QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
    query.bindValue(":rowid", currentElementApi + 1);
    if (!query.exec())
    {
      qDebug() << query.lastError().text();
    }
  }
  return 0;
}

QStringList CoreEngine::clickLoadFromQml()
{
  QStringList res;
  QSqlQuery query(sdb);
  query.prepare("SELECT json_str, comment FROM Json WHERE rowid =:rowid");
  query.bindValue(":rowid", currentElementApi + 1);
  if (!query.exec())
    qDebug() << "SELECT Error" << query.lastError().text();

  QSqlRecord rec = query.record();
  int iJson_str = rec.indexOf("json_str");
  int iComment = rec.indexOf("comment");
  query.next();
  res.push_back(query.value(iJson_str).toString());
  res.push_back(query.value(iComment).toString());

  qDebug() << res;

  return res;
}

QString CoreEngine::clickLoadCommFromQml()
{
  QSqlQuery query(sdb);
  if (!query.exec("SELECT comment FROM Json ORDER BY rowid DESC LIMIT 1"))
  {
    qDebug() << "Error" << query.lastError().text();
  }

  QSqlRecord rec = query.record();
  int indexOf = rec.indexOf("comment");
  query.next();
  QString res = query.value(indexOf).toString();

  qDebug() << res;

  return res;
}

QStringList CoreEngine::getApiInfo(int n)
{
  currentElementApi = n;
  return {vecApiInfos[currentElementApi].description, vecApiInfos[n].url};
}

QString CoreEngine::getRequestFromQml() const
{
  /*// берем адрес введенный в текстовое поле

  QUrl url(ui->lineEdit->text());

  // создаем объект для запроса

  QNetworkRequest request(url);

  // Выполняем запрос, получаем указатель на объект

  // ответственный за ответ

  QNetworkReply *reply = manager->get(request);

  // Подписываемся на сигнал о готовности загрузки

  connect(reply, SIGNAL(finished()),

          this, SLOT(replyFinished()));*/
  return QString("ret");
}

void CoreEngine::setRequest(QString url_)
{
  // берем адрес введенный в текстовое поле

  QUrl url(url_);

  // создаем объект для запроса

  QNetworkRequest request(url);

  // Выполняем запрос, получаем указатель на объект

  // ответственный за ответ

  QNetworkReply *reply = manager->get(request);

  // Подписываемся на сигнал о готовности загрузки

  connect(reply, SIGNAL(finished()),

          this, SLOT(replyFinished()));
}

void CoreEngine::replyFinished(QString json)
{
  emit replyJson();
}
