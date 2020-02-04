
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "MyDB_TableRecordIterator.h"
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
	return _pages.back();
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr appendMe) {
    if (!_pages[_pages.size() - 1].append(appendMe)) {
        _tablePtr->setLastPage(_tablePtr->lastPage() + 1);
        MyDB_PageHandle newPageHandle(_bufferManager->getPage(_tablePtr, _tablePtr->lastPage()));
        MyDB_PageReaderWriter newLastPageRW(_pageSize, newPageHandle);
        newLastPageRW.clear();
        _pages.push_back(newLastPageRW);
        _pages[_pages.size() - 1].append(appendMe);
    }
}

void MyDB_TableReaderWriter :: loadFromTextFile (string fileName) {
    for (auto& p : _pages) {
        p.clear();
    }
    _pages.clear();
    _tablePtr->setLastPage(0);
    MyDB_PageHandle newPageHandle = _bufferManager->getPage(_tablePtr, 0);
    MyDB_PageReaderWriter newPageRW(_pageSize, newPageHandle);
    newPageRW.clear();
    _pages.push_back(newPageRW);

    ifstream f(fileName);
    string tempString;
    MyDB_RecordPtr tempRec = getEmptyRecord();
    if (f) {
        while (getline(f, tempString)) {
            tempRec->fromString(tempString);
            append(tempRec);
        }
        f.close();
    }

}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr recordPtr) {
	return make_shared<MyDB_TableRecordIterator>(make_shared<MyDB_TableReaderWriter>(*this), recordPtr);
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string fileName) {
    ofstream f(fileName);
    MyDB_RecordPtr tempRec = getEmptyRecord();
    MyDB_RecordIteratorPtr tempIterator = getIterator(tempRec);
    if (f) {
        while (tempIterator->hasNext()) {
            tempIterator -> getNext();
            f << tempRec << endl;
        }
        f.close();
    }
}

size_t MyDB_TableReaderWriter :: totalPageNumber() {
    return _pages.size();
}

MyDB_PageReaderWriter MyDB_TableReaderWriter :: getPage(size_t pageId) {
    return _pages[pageId];
}

#endif

