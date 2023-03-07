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

/*enum NASAapi
{
  APOD = 1,
  Asteroids
}*/

class CoreEngine : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString getReqestFromQml READ getReqestFromQml WRITE setReqest NOTIFY replyJson)
  // Q_PROPERTY
public:
  /*struct pack
  {
    QString description = "";
    QString urltxt = "";
    QString replytxt = "";
  };*/

  explicit CoreEngine(QObject *parent = nullptr);
  Q_INVOKABLE QString reqestFromQml(QString n);
  Q_INVOKABLE int clickSaveFromQml(QString n);
  Q_INVOKABLE QString clickLoadFromQml(QString n);
  Q_INVOKABLE QString clickLoadCommFromQml(QString n);
  QString getReqestFromQml() const;
  void setReqest(QString url);

signals:
  void replyJson();

private:
  QNetworkAccessManager *manager;
  QSqlDatabase sdb;
  QString _url;

public slots:
  void replyFinished(QString json);
};

#endif // COREENGINE_H
