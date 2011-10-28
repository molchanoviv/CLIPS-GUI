#ifndef CLIPSMMCLASS_H
#define CLIPSMMCLASS_H

#include <clipsmm.h>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QVector>

class CLIPSMMClass : public QObject
{
	Q_OBJECT
public:
	explicit CLIPSMMClass(QObject *parent = 0);

signals:

public slots:
	void addFact(QString);
	QString getAllFacts();
private:
	CLIPS::Environment env;
	CLIPS::Fact::pointer fact;

};

#endif // CLIPSMMCLASS_H
