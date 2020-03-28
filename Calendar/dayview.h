#ifndef DAYVIEW_H
#define DAYVIEW_H

#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class DayView : public QDialog
{
    Q_OBJECT
public:
    DayView(QWidget *parent = nullptr);
private:
    QTableWidget *m_eventsTable;

    QStringList m_tableHeader;

    QPushButton *m_addButton;
    QPushButton *m_saveButton;

    QVBoxLayout *m_layout;
    QHBoxLayout *m_buttonLayout;
};

#endif // DAYVIEW_H
