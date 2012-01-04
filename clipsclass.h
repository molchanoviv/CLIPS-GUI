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
	QStringList factsSlot(bool);
	QStringList templatesSlot(bool);
	void retractSlot(int, bool);
	void saveFactsSlot(QString);
	void loadFactsSlot(QString);
	void saveSlot(QString);
	void loadSlot(QString);
	void clearSlot();
	void setFactDuplicationSlot(bool, bool);
	void deftemplateSlot(QString, QList<slotsPair>);
	void unDeftemplateSlot(QString, bool);

signals:
	void outputSignal(QString);
	void factsChangedSignal(QStringList);
	void templatesChangedSignal(QStringList);
	void clearSignal();

protected:

};

#endif // CLIPSCLASS_H
