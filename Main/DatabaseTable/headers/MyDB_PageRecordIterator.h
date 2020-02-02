
#ifndef MYDB_PAGERECORDITERATOR_H
#define MYDB_PAGERECORDITERATOR_H

#include <memory>
#include "MyDB_RecordIterator.h"
#include "MyDB_BufferManager.h"
#include "MyDB_Record.h"
#include "MyDB_PageReaderWriter.h"

using namespace std;

class MyDB_PageReaderWriter;
typedef shared_ptr<MyDB_PageReaderWriter> MyDB_MyDB_PageReaderWriterPtr;

class MyDB_PageRecordIterator : public MyDB_RecordIterator {
public:
    MyDB_PageRecordIterator(MyDBMyDB_PageReaderWriterPtr, MyDB_RecordPtr);
    virtual void getNext();
    virtual bool hasNext();
    ~MyDB_PageRecordIterator() override ;

private:

    MyDBMyDB_PageReaderWriterPtr _pagePtr;
    MyDB_RecordPtr _recordPtr;

};

#endif //MYDB_PAGERECORDITERATOR_H
