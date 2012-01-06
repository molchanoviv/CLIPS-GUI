#ifndef CLIPSCLASS_H
#define CLIPSCLASS_H

#include <clips/clips.h>
#include <QtCore>

typedef QPair<bool, QString> slotsPair;

class CLIPSClass : public QObject
{
	Q_OBJECT
public:
	explicit CLIPSClass(QObject *parent = 0);

public slots:
	void assertStringSlot(QString, bool);
	void assertSlot(QString, QList<slotsPair>, bool);
	QStringList factsSlot(bool);
	QStringList factsListSlot(bool);
	QStringList templatesSlot(bool);
	void retractSlot(int, bool);
	void saveFactsSlot(QString);
	void loadFactsSlot(QString);
	void saveSlot(QString);
	void loadSlot(QString);
	void clearSlot();
	void setFactDuplicationSlot(bool, bool);
	void deftemplateSlot(QString, QList<slotsPair>);
	void deffactsSlot(QString, QStringList);
	void unDeftemplateSlot(QString, bool);
	void unDeffactsSlot(QString, bool);
	QList<slotsPair> getTemplateInformation(QString);

signals:
	void outputSignal(QString);
	void factsChangedSignal(QStringList);
	void deffactsChangedSignal(QStringList);
	void templatesChangedSignal(QStringList);
	void clearSignal();

protected:

};

#endif // CLIPSCLASS_H
