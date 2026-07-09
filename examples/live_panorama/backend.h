#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QQmlParserStatus>

#include <downloader.h>
#include <imagetiles.h>
#include <panomax/panoramaupdater.h>

// owns the PanoramaUpdater and exposes only the resulting image tiles to
// qml; mirrors the pattern the real app will use
class Backend : public QObject, public QQmlParserStatus
{
  Q_OBJECT
  QML_ELEMENT
  Q_INTERFACES(QQmlParserStatus)
  Q_PROPERTY(int camId READ camId WRITE setCamId NOTIFY camIdChanged FINAL)
  Q_PROPERTY(QString resolution READ resolution WRITE setResolution NOTIFY
                 resolutionChanged FINAL)
  Q_PROPERTY(QString fallbackResolution READ fallbackResolution WRITE
                 setFallbackResolution NOTIFY fallbackResolutionChanged FINAL)
  Q_PROPERTY(wsgui::core::ImageTiles imageTiles READ imageTiles NOTIFY
                 imageTilesChanged FINAL)

public:
  explicit Backend(QObject* parent = nullptr);

  int camId() const;
  void setCamId(int camId);

  const QString& resolution() const;
  void setResolution(const QString& resolution);

  const QString& fallbackResolution() const;
  void setFallbackResolution(const QString& fallbackResolution);

  const wsgui::core::ImageTiles& imageTiles() const;

  void classBegin() override;
  void componentComplete() override;

signals:
  void camIdChanged();
  void resolutionChanged();
  void fallbackResolutionChanged();
  void imageTilesChanged();

private:
  wsgui::core::Downloader m_downloader;
  wsgui::core::panomax::PanoramaUpdater m_updater;
};
