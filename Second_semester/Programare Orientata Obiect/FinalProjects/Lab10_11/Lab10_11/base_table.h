#ifndef BASE_TABLE_H
#define BASE_TABLE_H

#include <QWidget>

class base_table : public QWidget
{
private:
    QWidget* parent;

public:
    explicit base_table(QWidget *par = nullptr);

};

#endif // BASE_TABLE_H
