#ifndef MYDB_TABLERECORDITERATOR_C
#define MYDB_TABLERECORDITERATOR_C

#include "MyDB_TableRecordIterator.h"
#include "MyDB_PageReaderWriter.h"
class MyDB_PageReaderWriter;


using namespace std;

class MyDB_TableRecordIterator;

void MyDB_TableRecordIterator::getNext() {
    if (hasNext()) {
        return _recordIter->getNext();
    }
}

bool MyDB_TableRecordIterator::hasNext() {
    if (_recordIter->hasNext()) {
        return true;
    }

    if (_pageId == _tablePtr->totalPageNumber() - 1) {
        return false;
    }
    _pageId++;
    _recordIter = _tablePtr->getPage(_pageId).getIterator(_recordPtr);
    return hasNext();
}

MyDB_TableRecordIterator::~MyDB_TableRecordIterator() {

}

MyDB_TableRecordIterator::MyDB_TableRecordIterator(MyDB_TableReaderWriterPtr myDbTableReaderWriterPtr,
        MyDB_RecordPtr myDbRecordPtr) {
    _recordPtr = myDbRecordPtr;
    _tablePtr = myDbTableReaderWriterPtr;
    _pageId = 0;
    _recordIter = _tablePtr->getPage(_pageId).getIterator(_recordPtr);

}

#endif
