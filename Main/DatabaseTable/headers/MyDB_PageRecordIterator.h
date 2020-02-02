
#ifndef MYDB_PAGERECORDITERATOR_H
#define MYDB_PAGERECORDITERATOR_H

#include <memory>
#include "MyDB_RecordIterator.h"

using namespace std;

class MyDB_PageRecordIterator : public MyDB_RecordIterator {
public:
    virtual void getNext();
    virtual bool hasNext();
    ~MyDB_PageRecordIterator() override ;
};

#endif //MYDB_PAGERECORDITERATOR_H
