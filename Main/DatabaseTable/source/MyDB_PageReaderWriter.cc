
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"
#include <memory>

class MyDB_PageRecordIterator;

void MyDB_PageReaderWriter :: clear () {
    _wroteLen = 0;
    _type = RegularPage;
    _pageHandle->wroteBytes();
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return _type;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr recordPtr) {
    MyDB_RecordIteratorPtr newIterator = make_shared<MyDB_PageRecordIterator> (make_shared<MyDB_PageReaderWriter>(*this), recordPtr);
	return newIterator;
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType newType) {
    _type = newType;
    _pageHandle->wroteBytes();
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr recordPtr) {
    if (_pageSize < _wroteLen + recordPtr->getBinarySize()) {
        return false;
    }

    _wroteLen = (char*)recordPtr->toBinary(getHeader() + _wroteLen) - (char*)getHeader();
    _pageHandle -> wroteBytes();
	return true;
}

MyDB_PageReaderWriter::MyDB_PageReaderWriter(size_t pageSize, MyDB_PageHandle pageHandle) {
    _pageSize = pageSize;
    _pageHandle = pageHandle;
    _wroteLen = 0;
    _type = RegularPage;
}

#endif
