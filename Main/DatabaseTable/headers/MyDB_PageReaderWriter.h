
#ifndef PAGE_RW_H
#define PAGE_RW_H

#include <memory>
#include "MyDB_PageType.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_PageRecordIterator.h"

using namespace std;

struct PageHeader{
    MyDB_PageType pageType;
    size_t wrote_len;
    char start[0];
};

class MyDB_PageReaderWriter : public enable_shared_from_this<MyDB_PageReaderWriter> {

public:

	// ANY OTHER METHODS YOU WANT HERE

	// empties out the contents of this page, so that it has no records in it
	// the type of the page is set to MyDB_PageType :: RegularPage
	void clear ();	

	// return an itrator over this page... each time returnVal->next () is
	// called, the resulting record will be placed into the record pointed to
	// by iterateIntoMe
	MyDB_RecordIteratorPtr getIterator (MyDB_RecordPtr iterateIntoMe);

	// appends a record to this page... return false is the append fails because
	// there is not enough space on the page; otherwise, return true
	bool append (MyDB_RecordPtr appendMe);

	// gets the type of this page... this is just a value from an ennumeration
	// that is stored within the page
	MyDB_PageType getType ();

	// sets the type of the page
	void setType (MyDB_PageType toMe);

	MyDB_PageReaderWriter(size_t, MyDB_PageHandle);

	PageHeader* getHeader();

	size_t getWroteLen();

	char* getStart();

	size_t getHeaderSize();
	
private:

	// ANYTHING ELSE YOU WANT HERE
	size_t _pageSize;
	MyDB_PageHandle _pageHandle;

};

#endif
