
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"
#include <vector>

using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr forMe, MyDB_BufferManagerPtr myBuffer) {
    _tablePtr = forMe;
    _bufferManager = myBuffer;
    _pageSize = myBuffer->getPageSize();
    for (int i = 0; i <= _tablePtr->lastPage(); i++) {
        MyDB_PageHandle newPageHandle = _bufferManager->getPage(_tablePtr, i);
        MyDB_PageReaderWriter newPageRW(_pageSize, newPageHandle);
        _pages.push_back(newPageRW);
    }
}

MyDB_PageReaderWriter MyDB_TableReaderWriter :: operator [] (size_t i) {
    if (i > _tablePtr->lastPage()) {
        cout << "i is greater than the last page " << endl;
    }
	return 	_pages[i];
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
    MyDB_RecordPtr myDbRecordPtr = make_shared<MyDB_Record>(_tablePtr->getSchema());
	return myDbRecordPtr;
}

MyDB_PageReaderWriter MyDB_TableReaderWriter :: last () {
	MyDB_PageReaderWriter lastPageRW = _pages.back();
	return lastPageRW;
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr appendMe) {
    if (!last().append(appendMe)) {
        _tablePtr->setLastPage(_tablePtr->lastPage() + 1);
        MyDB_PageHandle newPageHandle(_bufferManager->getPage(_tablePtr, _tablePtr->lastPage()));
        MyDB_PageReaderWriter newLastPageRW(_pageSize, newPageHandle);
        _pages.push_back(newLastPageRW);
        last().append(appendMe);
    }
}

void MyDB_TableReaderWriter :: loadFromTextFile (string fileName) {

}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr) {
	return nullptr;
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string) {
}

#endif

