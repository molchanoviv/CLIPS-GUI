#ifndef CLIPSCLASS_H
#define CLIPSCLASS_H

#include <clips/clips.h>
#include <QtCore>

class CLIPSClass : public QObject
{
	Q_OBJECT
public:
	explicit CLIPSClass(QObject *parent = 0);

public slots:
	void assertStringSlot(QString, bool);
	QString factsSlot(bool);
	void retractSlot(int, bool);
	void saveFactsSlot(QString);
	void loadFactsSlot(QString);
	void saveSlot(QString);
	void loadSlot(QString);
	void clearSlot();
	void setFactDuplicationSlot(bool, bool);

signals:
	void outputSignal(QString);
	void factsChangedSignal(QString);

protected:
	char* toChar(QString);

};

#endif // CLIPSCLASS_H
