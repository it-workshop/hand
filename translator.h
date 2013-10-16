#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QList>

class FileActionPerformer;
class GloveInterface;
class HandInterface;
class User;

enum ConnectionType {
	noConnection = 0,
	gloveToHand = 1,
	actionToHand = 2
};

class Translator :  public QObject
{
	Q_OBJECT
public:
	Translator();
	~Translator();

	bool connectGlove();
	bool connectHand();

	void startConnection();
	void stopConnection();

	QList<int> *sensorData() { return &mSensorDatas; }
	QList<int> *convertedData() { return &mConvertedDatas; }

	void setConnectionType(ConnectionType const& type) { mConnectionType = type; }
	ConnectionType connectionType() const { return mConnectionType; }

	void startLoadAction(const QString &fileName);
	void stopLoadAction();

	void startSaveAction(const QString &fileName, const int &freq);
	void stopSaveAction();

protected slots:
	void convertData();

signals:
	void loadingStoped();

protected:
	void saveConvertedData(QList<int> const& data);
	void saveSensorsData(QList<int> const& data);

	int map(int const& value
			, int const& firstMin, int const& firstMax
			, int const& secondMin, int const& secondMax);

	int map(int const& value
			, int const& min, int const& max);

	void sendDataToHand();

private:
	ConnectionType mConnectionType;

	QList<int> mConvertedDatas;
	QList<int> mSensorDatas;

	User *mUser;

	FileActionPerformer *mFileActionPerformer;

	GloveInterface *mGloveInterface;
	HandInterface *mHandInterface;
};

#endif // TRANSLATOR_H
