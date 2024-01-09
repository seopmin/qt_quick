#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString names READ names WRITE setNames NOTIFY namesChanged FINAL)
    Q_PROPERTY(QString favoriteColor READ favoriteColor WRITE setFavoriteColor NOTIFY favoriteColorChanged FINAL)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged FINAL)

public:
    explicit Person(QObject *parent = nullptr);
    Person(const QString &names, const QString &favoritecolor, const int &age, QObject *parent = nullptr);


    QString names() const;
    void setNames(const QString &newNames);

    QString favoriteColor() const;
    void setFavoriteColor(const QString &newFavoriteColor);

    int age() const;
    void setAge(int newAge);

signals:

    void namesChanged();
    void favoriteColorChanged();

    void ageChanged();

private:
    QString m_names;
    QString m_favoriteColor;
    int m_age;
};

#endif // PERSON_H
