#ifndef MYDB_PAGERECORDITERATOR_C
#define MYDB_PAGERECORDITERATOR_C

#include "MyDB_PageRecordIterator.h"

using namespace std;

class MyDB_PageRecordIterator;

void MyDB_PageRecordIterator::getNext() {
    if (hasNext()) {
        _pointTo = (char *)(_recordPtr -> fromBinary(_pointTo + (char *)_pagePtr -> getHeader())) - (char*)_pagePtr -> getHeader();
    }
}

bool MyDB_PageRecordIterator::hasNext() {
    return _pointTo + _recordPtr->getBinarySize() <= _pagePtr->getPageSize();
}

MyDB_PageRecordIterator::~MyDB_PageRecordIterator() {

}

MyDB_PageRecordIterator::MyDB_PageRecordIterator(MyDB_PageReaderWriterPtr pagePtr, MyDB_RecordPtr recordPtr) {
    _pagePtr = pagePtr;
    _recordPtr = recordPtr;
    _pointTo = 0;
}

#endif
