
#ifndef MYDB_PAGERECORDITERATOR_H
#define MYDB_PAGERECORDITERATOR_H

#include <memory>
#include "MyDB_RecordIterator.h"
#include "MyDB_BufferManager.h"
#include "MyDB_Record.h"
#include "MyDB_PageReaderWriter.h"

using namespace std;

class MyDB_PageReaderWriter;
typedef shared_ptr<MyDB_PageReaderWriter> MyDB_PageReaderWriterPtr;

class MyDB_PageRecordIterator : public MyDB_RecordIterator {
public:
    MyDB_PageRecordIterator(MyDB_PageReaderWriterPtr, MyDB_RecordPtr);
    virtual void getNext() override;
    virtual bool hasNext() override;
    ~MyDB_PageRecordIterator() override ;

private:

    MyDB_PageReaderWriterPtr _pagePtr;
    MyDB_RecordPtr _recordPtr;
    size_t _pointTo;
};

#endif //MYDB_PAGERECORDITERATOR_H
