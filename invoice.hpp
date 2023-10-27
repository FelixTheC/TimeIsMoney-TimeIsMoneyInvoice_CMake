#ifndef INVOICE_HPP
#define INVOICE_HPP

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextDocumentWriter>
#include <QPrinter>
#include <QPainter>
#include <QPaintDevice>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QPageSize>
#include <QSharedPointer>


namespace Ui {
class Invoice;
}

class Invoice : public QMainWindow
{
    Q_OBJECT

public:
    explicit Invoice(QSharedPointer<QSqlDatabase> &database, QWidget *parent = nullptr);
    ~Invoice();

private slots:
    void on_calendarStart_clicked(const QDate &date);
    void on_calendarEnd_clicked(const QDate &date);
    void on_btnGenerate_clicked();

    void on_btnSaveSettings_clicked();

private:
    Ui::Invoice *ui;
    QSharedPointer<QSqlDatabase> database;

    void initDateWidgets();
    void initComboBoxItems();
    void save_invoice_settings();
    void update_invoice_settings();
    void initInvoiceView();

    [[nodiscard]] double getTax();
    [[nodiscard]] double getExchangeRate();

    [[nodiscard]] bool invoiceSettingsExist();
    QWidget *QMainWindow;
};

#endif // INVOICE_HPP
