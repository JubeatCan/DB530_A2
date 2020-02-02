
#ifndef MYDB_TABLERECORDITERATOR_H
#define MYDB_TABLERECORDITERATOR_H

#include <memory>
#include "MyDB_RecordIterator.h"

using namespace std;

class MyDB_TableRecordIterator : public MyDB_RecordIterator {
public:
    virtual void getNext();
    virtual bool hasNext();
    ~MyDB_TableRecordIterator() override ;
    MyDB_TableRecordIterator();

private:
};


#endif //MYDB_TABLERECORDITERATOR_H
