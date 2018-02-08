//Sean Reddington
//*made arround fall 2016*
//header file to create a queue of cars
//Merged queueType.h and linkedListType.h and removed documentation at some point to save paper when printing... Good luck!

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

struct nodeType {
	int info;
	nodeType *link;
};

class linkedListType {

public:
	linkedListType();
	linkedListType(const linkedListType& otherList);
	~linkedListType();
	const linkedListType& operator= (const linkedListType&);
	void initializeList();
	bool isEmptyList() const;
	void print(ostream& out) const;
	int length() const;
	void destroyList();
	int front() const;
	int back() const;
	void insertFirst(const int& newItem);
	void insertLast(const int& newItem);
	void deleteFront();

protected:
	int count;
	nodeType *first;
	nodeType *last;

private:
	void copyList(const linkedListType& otherList);

};

linkedListType::linkedListType() {

	first = nullptr;
	last = nullptr;
	count = 0;
}

linkedListType::linkedListType(const linkedListType& otherList) {
	first = nullptr;
	copyList(otherList);
}

linkedListType::~linkedListType() {
	destroyList();
}

const linkedListType& linkedListType::operator=(const linkedListType& otherList) {
	if (this != &otherList) {
		copyList(otherList);
	}

	return *this;
}

void linkedListType::initializeList() {
	destroyList();
}

bool linkedListType::isEmptyList() const {
	return (first == nullptr);
}

void linkedListType::print(ostream& out) const {
	nodeType *current;

	current = first;

	while (current != nullptr) {
		out << current->info << " ";
		current = current->link;
	}
}

int linkedListType::length() const {
	return count;
}

void linkedListType::destroyList() {
	nodeType *temp;
	while (first != nullptr) {
		temp = first;
		first = first->link;
		delete temp;
	}

	last = nullptr;
	count = 0;
}

int linkedListType::front() const {
	assert(first != nullptr);

	return first->info;
}

int linkedListType::back() const {
	assert(last != nullptr);

	return last->info;
}

void linkedListType::insertFirst(const int& newItem) {
	nodeType *newNode;
	newNode = new nodeType;
	newNode->info = newItem;
	newNode->link = first;
	first = newNode;

	count++;

	if (last == nullptr)

		last = newNode;
}

void linkedListType::insertLast(const int& newItem) {
	nodeType *newNode;
	newNode = new nodeType;
	newNode->info = newItem;
	newNode->link = nullptr;

	if (first == nullptr) {
		first = newNode;
		last = newNode;
		count++;
	}
	else {
 		last->link = newNode;
		last = newNode;
		count++;
	}
}

void linkedListType::deleteFront() {
	if (first == nullptr)
		return;
	if (count == 1) {
		first = first->link;
		delete first;
		last = nullptr;
		count = 0;
		return;
	}

	nodeType *temp;
	temp = first;
	first = first->link;
	delete temp;
	count--;
}

void linkedListType::copyList(const linkedListType& otherList) {
	nodeType *newNode;
	nodeType *current;

	if (first != nullptr)
		destroyList();
	if (otherList.first == nullptr) {
		first = nullptr;
		last = nullptr;
		count = 0;
	}
	else {
		current = otherList.first;

		count = otherList.count;

		first = new nodeType;
		first->info = current->info;
		first->link = nullptr;

		last = first;

		current = current->link;

		while (current != nullptr) {
			newNode = new nodeType;
			newNode->info = current->info;
			newNode->link = nullptr;

			last->link = newNode;
			last = newNode;

			current = current->link;
		}
	}
}




class queueType : public linkedListType {

public:
	queueType();
	~queueType();
	const queueType& operator= (const queueType&);
	bool isEmptyQueue() const;
	int front() const;
	void addQueue(const int& n);
	void deleteQueue();

private:
	int maxQueueSize;
	queueType *list;

};

queueType::queueType() {
	count = 0;
	last = nullptr;
	first = nullptr;
	maxQueueSize = 100;
}

queueType::~queueType() {
	destroyList();
}

const queueType& queueType:: operator= (const queueType& rhs) {
	if (this != &rhs) {
		*this = rhs;
	}
	return *this;
}

bool queueType::isEmptyQueue() const {
	return (first == nullptr);
}

int queueType::front() const {
	assert(first != nullptr);

	return first->info;
}

void queueType::addQueue(const int& n) {
	insertLast(n);
}

void queueType::deleteQueue() {
	deleteFront();
}