
#ifndef MYDB_TABLERECORDITERATOR_H
#define MYDB_TABLERECORDITERATOR_H

#include <memory>
#include "MyDB_RecordIterator.h"
#include "MyDB_Record.h"
#include "MyDB_TableReaderWriter.h"

using namespace std;

class MyDB_TableRecordIterator : public MyDB_RecordIterator {
public:
    virtual void getNext() override;
    virtual bool hasNext() override;
    ~MyDB_TableRecordIterator() override ;
    MyDB_TableRecordIterator(MyDB_TableReaderWriterPtr ,MyDB_RecordPtr);

private:
    MyDB_RecordPtr _recordPtr;
    MyDB_TableReaderWriterPtr _tablePtr;
    MyDB_RecordIteratorPtr _recordIter;
    size_t _pageId;
};


#endif //MYDB_TABLERECORDITERATOR_H
