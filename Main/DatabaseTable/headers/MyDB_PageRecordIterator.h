
#ifndef MYDB_PAGERECORDITERATOR_H
#define MYDB_PAGERECORDITERATOR_H

#include <memory>
#include "MyDB_RecordIterator.h"

using namespace std;

class MyDB_PageRecordIterator : public MyDB_RecordIterator {
public:
    MyDB_PageRecordIterator();
    virtual void getNext();
    virtual bool hasNext();
    ~MyDB_PageRecordIterator() override ;

private:

};

#endif //MYDB_PAGERECORDITERATOR_H
