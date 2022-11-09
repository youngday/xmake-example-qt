#include "main.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

using namespace std;

extern int folderTest();
extern int tcp_client();
extern int tcp_client_coro();
extern int sqlite_orm_app();
extern int xtensor_test();
extern int cppzmq_app();

int main(int argc, char *argv[])
{
    auto time_str = mylocal_time();
  filesystem::path folder_path = "./log/";
  filesystem::create_directory(folder_path) ? LOG_S(INFO) << "mkdir sucess." << folder_path << endl : LOG_S(INFO) << "dir exist." << folder_path << endl;

  string logfilename = "log/everything-" + time_str + ".log";
  loguru::init(argc, argv);
  loguru::add_file(logfilename.c_str(), loguru::Append,
                   loguru::Verbosity_MAX); // Verbosity_INFO  Verbosity_MAX
  // Only log INFO, WARNING, ERROR and FATAL to "latest_readable.log":
  logfilename = "log/latest_readable-" + time_str + ".log";
  loguru::add_file(logfilename.c_str(), loguru::Truncate,
                   loguru::Verbosity_INFO);
  LOG_S(INFO) << fmt::format("Starting at {}!\n", time_str);


  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  // QThread *my_thread = new QThread;
  // Test *test_2 = new Test(); // should not (this) , QObject::moveToThread:
  //                            // Cannot move objects with a parent
  // //  Test_Concurent* test_concurent = Q_NULLPTR;

  // engine.addImportPath(TaoQuickImportPath);
  // engine.rootContext()->setContextProperty("taoQuickImagePath",
  //                                          TaoQuickImagePath);
  // engine.rootContext()->setContextProperty("buttonsClicked", test_2);

  // test_2->moveToThread(my_thread);
  // QObject::connect(test_2, &Test::sigResultReady, test_2, &Test::onTest);
  // QObject::connect(my_thread, &QThread::finished, test_2, &Test::deleteLater);
  // my_thread->start();
  // // test_concurent = new Test_Concurent();
  // // test_concurent->hide();

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);
 if (engine.rootObjects().isEmpty())
        return -1;

  //   QList<QString> strList;
  //   for (int i = 0; i < 20; i++)
  //     strList.append(QString::number(i + 1) + " ok");
  //   string text;
  //   for (int i = 0; i < strList.size(); ++i)
  //     text += strList.at(i).toStdString() + "  ";
  // LOG_S(INFO)<<text;

  //   QList<QString> strNew =
  //       QtConcurrent::blockingMapped(strList, stringInversion);
  //   text.clear();
  //   for (int i = 0; i < strNew.size(); ++i)
  //     text += strNew.at(i).toStdString() + "  ";
  // LOG_S(INFO)<<text;

  // QSharedPointer<QMediaPlayer> player(new QMediaPlayer);
  // // https://www.luyinzhushou.com/text2voice/
  // player->setMedia(QUrl::fromLocalFile("test2.mp3")); // should local file
  // path
  // // player->setMedia(QUrl("qrc:/test1.mp3"));
  // player->setVolume(50); // 0~100音量范围,默认是100
  // player->play();


    return app.exec();
}
