    #include <galaxy-explorer/AsteroidList.hpp>
#include <iostream>
using namespace std;

AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
        
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
       
	this->next = nullptr;
	this->data = new Asteroid(a.getID(), a.getMass(), a.getHealth(),a.getCurrentHitbox(), a.getVelocity());
}

AsteroidListItem::~AsteroidListItem() {
    
    if(data){
        delete data;
        data = nullptr;
   
    }

    
 }
    
AsteroidList::AsteroidList()
{
    
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
        const AsteroidListItem * ptr = (src.head.getNext()); 
        AsteroidListItem * last = NULL; 
        AsteroidListItem * nptr = NULL; 
        head.setNext(NULL); 
        while(ptr != NULL) { 
          nptr = new AsteroidListItem(ptr->getData()); 
          if (last == NULL) head.setNext(nptr); 
          else last->setNext(nptr); 
          ptr = ptr->getNext(); 
          last = nptr; 
        } 
  
       
}

AsteroidList::~AsteroidList() {
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
    
    clear();
}

void AsteroidList::pushFront(Asteroid e) {

    AsteroidListItem* tptr = new AsteroidListItem(e); 
    if(head.getNext())
        tptr->setNext(head.getNext());
    head.setNext(tptr);
   
    
}

Asteroid& AsteroidList::front() {
	return (head.getNext()->getData());
}

const Asteroid& AsteroidList::front() const {
	return (head.getNext()->getData());
}

bool AsteroidList::isEmpty() const {
	return (!head.getNext());
}

int AsteroidList::size() const {
    if(isEmpty()) return 0;
    int counter = 0;
    const AsteroidListItem* tptr = head.getNext(); 
    while (tptr != nullptr) {
      tptr= tptr->getNext(); 
      counter++;
    } 
    
    return counter;
}

AsteroidListItem* AsteroidList::beforeBegin() {
	return (&head);
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	return (&head);
}

AsteroidListItem* AsteroidList::begin() {
    return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
    return head.getNext();
}

AsteroidListItem* AsteroidList::beforeEnd() {
    AsteroidListItem* tptr = head.getNext(); 
    while (tptr->getNext() != NULL) {
      tptr= tptr->getNext(); 
    } 
    return (tptr); 
	
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    
    const AsteroidListItem* tptr = begin();
    while (tptr->getNext()  != nullptr) {
      tptr= tptr->getNext(); 
    } 
    return (tptr);
    
}

AsteroidListItem* AsteroidList::end() {
	return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
	return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
 
    AsteroidListItem* tptr = new AsteroidListItem(e);   
    tptr->setNext(prev->getNext());
    prev->setNext(tptr);
 
    return prev->getNext();

     
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    if(prev == nullptr || others.isEmpty()) return prev;
   // AsteroidList* tptr = new AsteroidList(others);
    AsteroidListItem* nptr =  prev;
    AsteroidListItem* temp =  prev->getNext();
    
    for (const AsteroidListItem* it = others.begin(); it != others.end(); it = it->getNext()) { 
        nptr->setNext(new AsteroidListItem(it->getData()));
        nptr = nptr->getNext();
       
    // should never get here if the list is empty
    }
    if(temp)
        nptr->setNext(temp);
   
    return nptr;
    
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    if(prev == nullptr || prev->getNext() == nullptr) return nullptr;
    
    AsteroidListItem* tptr = prev->getNext();
    prev->setNext(tptr->getNext());
    delete tptr;
    tptr = nullptr;
    return prev->getNext();
}

void AsteroidList::clear() {
    if(isEmpty()) return;
    AsteroidListItem* tptr;
    AsteroidListItem* ttptr = head.getNext();
   
    while (ttptr != nullptr) { 
        tptr = ttptr;
        ttptr = tptr->getNext();
        delete tptr;
        tptr = nullptr;
 
       
    }

    head.setNext(nullptr);
    return;
    
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
            if (this == &src) return (*this); 
            
            clear();
            insertAfter(&head, src);
            
            return (*this);
}   
