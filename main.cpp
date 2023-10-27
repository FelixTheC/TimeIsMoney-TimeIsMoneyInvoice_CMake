#include <QApplication>

#include "../TimeIsMoneyDB_CMake/include/taskdb.hpp"

#include "invoice.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    auto taskDB = TaskDB().getDBPtr();
    
    Invoice w(taskDB, nullptr);
    w.show();
    return a.exec();
}
