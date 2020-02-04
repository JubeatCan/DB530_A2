
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"
#include <memory>

class MyDB_PageRecordIterator;

void MyDB_PageReaderWriter :: clear () {
    getHeader()->pageType = RegularPage;
    getHeader()->wrote_len = 0;

    _pageHandle->wroteBytes();
}



MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return getHeader()->pageType;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr recordPtr) {
    MyDB_RecordIteratorPtr newIterator = make_shared<MyDB_PageRecordIterator> (make_shared<MyDB_PageReaderWriter>(*this), recordPtr);
	return newIterator;
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType newType) {
    getHeader()->pageType = newType;
    _pageHandle->wroteBytes();
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr recordPtr) {

    if (_pageSize < (getHeaderSize() + getWroteLen() + recordPtr->getBinarySize())) {
        return false;
    }
    getHeader()->wrote_len = (char*)recordPtr->toBinary(getStart() + getWroteLen()) - (char*)getStart();
    _pageHandle -> wroteBytes();
	return true;
}

MyDB_PageReaderWriter::MyDB_PageReaderWriter(size_t pageSize, MyDB_PageHandle pageHandle) {
    _pageSize = pageSize;
    _pageHandle = pageHandle;
}

size_t MyDB_PageReaderWriter::getWroteLen() {
    return getHeader()->wrote_len;
}

PageHeader* MyDB_PageReaderWriter::getHeader() {
    return (PageHeader*) _pageHandle->getBytes();
}

char *MyDB_PageReaderWriter::getStart() {
    return &(getHeader()->start[0]);
}

size_t MyDB_PageReaderWriter::getHeaderSize() {
    return getStart() - (char *)getHeader();
}

#endif
