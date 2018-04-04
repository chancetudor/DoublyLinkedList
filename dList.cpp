// Project Two by Chance Tudor: Implementing a doubly linked list
// using a node class and a dList class; sorting using mergesort
class node {
  public:
    node *prev = NULL;
    node *next = NULL;
    int key;
    char type;
};

class dList {
  private:
    node *head = NULL; // dummy head
    node *tail = NULL; // dummy tail

  public:
    dList() { // default constructor, creates empty list
      head = NULL;
      tail = NULL;
    }
    // destructor
    ~dList() {
      node *ptr = head;
      while (ptr != NULL) {
        node *next = ptr->next;
        delete ptr;
        ptr = next;
      }
      head = NULL;
      tail = NULL;
    }
    // searches list for occurence of int parameter and returns pointer to node containing key
    node *search(int k);
    // outputs all keys that have type equal to character parameter, front to back
    void find(char t);
    // parametrized constructor, initialize list w/ contents of arrays
    dList(int arrayNums[], char arrayChars[], int size);
    // creates new node at front of list
    void addFront(int k, char t);
    // creates new node at back of list
    void addBack(int k, char t);
    // moves node pointed to by parameter to front of list
    void moveFront(node* ptr);
    // moves node pointed to by parameter to back of list
    void moveBack(node* ptr);
    // outputs first int elements of list, starting at front or back depending on char parameter
    void out(int num, char = 'f');
    // splits list in two
    node *split(node* first1);
    // merges two linked lists
    node *mergeLists(node* first, node* second);
    // performs mergeSort on linked list
    node *mergeSort(node* headRef);
    // peforms an O(NlogN) sort on list; list should be in increasing order based on integer key
    void sort();
};

// parametrized constructor, initialize list w/ contents of arrays
dList::dList(int arrayNums[], char arrayChars[], int size) {
  for (int i = 0; i < size; i++) { // iterates through arrays
    node *newNode = new node; // creates new node each iteration
    newNode->key = arrayNums[i]; // assigns key the corresponding number from int array
    newNode->type = arrayChars[i]; // assigns type the corresponding char from char array
    newNode->prev = NULL; // to avoid garbage pointers
    newNode->next = NULL; // to avoid garbage pointers

    if (head == NULL) { // if empty list
      head = newNode; // newNode becomes head
      tail = newNode; // and tail
    }

    else { // if not empty list
      tail->next = newNode; // links last-created node to newNode
      newNode->prev = tail; // links newNode to last-created node
      tail = newNode; // assigns newNode to be the last-created node
    }
  }
}

void dList::addFront(int k, char t) { // creates new node at front of list
  node *newNode = new node; // creates new node
  newNode->key = k; // key now = to int argument
  newNode->type = t; // type now = to char arg

  if (head != NULL) { // if not empty list
    newNode->next = head; // links newNode to head
    newNode->prev = NULL;
    head->prev = newNode; // links head to newNode
    head = newNode; // assigns newNode as new head
  }
  else { // empty list
    newNode->prev = NULL; // newNode doesn't have any links, only adding 1 node
    newNode->next = NULL; // newNode doesn't have any links, only adding 1 node
    head = newNode; // newNode becomes head
    tail = newNode; // and tail
  }
}

void dList::addBack(int k, char t) { // creates new node at back of list
  node *newNode = new node; // creates new node
  newNode->key = k; // key now = to int argument
  newNode->type = t; // type now = to char arg

  node *ptr = head; // temp ptr to iterate through list with

  if (ptr != NULL) { // if not empty list
    while (ptr->next != NULL) { // iterates through list
      ptr = ptr->next;
    }
    ptr->next = newNode; // linking list with newNode
    newNode->next = NULL; // newNode doesn't have a next, is the new tail
    newNode->prev = ptr; // links newNode with list
    tail = newNode; // newNode is now tail
  }
  else { // empty list
    newNode->next = NULL; // newNode doesn't have any links, only adding 1 node
    newNode->prev = NULL; // newNode doesn't have any links, only adding 1 node
    ptr = newNode; // basically head = newNode
    tail = ptr; // tail = newNode
    head = ptr; // head = newNode
  }
}

void dList::moveFront(node *ptr) { // moves node pointed to by parameter to front of list
  if (ptr == head) { // if node is already head
    return; // no need to continue
  }
  else if (ptr == tail) { // else if at back of list
    ptr->prev->next = NULL; // removes  ptr as tail
    tail = ptr->prev; // new tail is the previous pointer to ptr
  }
  else {
    ptr->prev->next = ptr->next; // removes node in middle of list
    ptr->next->prev = ptr->prev; // links the surrounding nodes together
  }

  head->prev = ptr; // links head with ptr
  ptr->next = head; // links ptr with head
  ptr->prev = NULL; // new head, so doesn't need prev
  head = ptr; // ptr is now new head
}

void dList::moveBack(node *ptr) { // moves node pointed to by parameter to back of list
  if (ptr == tail) { // if pointer is to tail
    return; // no need to continue
  }
  else if (ptr == head) { // ptr is at front of list
    head = ptr->next; // head is now next pointer to ptr
    tail->next = ptr; // links tail to ptr
    ptr->prev = tail; // links ptr to tail
    ptr->next = NULL; // ptr is tail, so doesn't need next pointer
    tail = ptr; // ptr is now new tail
  }
  else {
    ptr->prev->next = ptr->next; // removes node in middle of list
    ptr->next->prev = ptr->prev; // links the surrounding nodes together
    tail->next = ptr; // links tail to ptr
    ptr->prev = tail; // links ptr to tail
    ptr->next = NULL; // ptr is tail, so doesn't need next pointer
    tail = ptr; // ptr is now new tail
  }
}
// searches list for occurence of int parameter and returns pointer to node containing key
node *dList::search(int k) {
  node *ptr = head; // temp pointer to iterate with
  while (ptr->next != NULL) { // iterates through list
    if (ptr->key == k) { // if key matches
      return ptr; // return the pointer
    }
    else {
      ptr = ptr->next; // else iterate through
    }
  }

  return NULL; // if key was not found, return NULL
}
// outputs all keys that have type equal to character parameter, front to back
void dList::find(char t) {
  node *ptr = head; // temp ptr to iterate with
  while (ptr->next != NULL) { // iterates through list
    if (ptr->type == t) { // if type matches search argument
      cout << ptr->key << " " << ptr->type << "   "; // output the key and the type
      ptr = ptr->next; // iterate
    }
    else {
      ptr = ptr->next; // else just iterate
    }
  }
  cout << endl; // for formatting
}
// outputs first num elements of list, starting at front or back depending on char parameter
void dList::out(int num, char side) {
  if (side == 'b') { // if side was not default argument
    node *ptr = tail; // temp ptr to iterate through
    for (int i = 0; i < num; i++) { // to output first num elements of list
      cout << ptr->key << " " << ptr->type << "   "; // output the key and the type
      ptr = ptr->prev; // iterate through BACKWARDS
    }
    cout << endl; // for formatting
  }
  else {
    node *ptr = head; // temp ptr to iterate through
    for (int i = 0; i < num; i++) { // to output first num elements of list
      cout << ptr->key << " " << ptr->type << "   "; // output the key and the type
      ptr = ptr->next; // iterate through normally
    }
    cout << endl; // formatting
  }
}

// calls split function to start sort
void dList::sort() {
  head = split(head); // splits main list in two (head passed as arg) and head is updated upon return
  head->prev = NULL; // safety code

  node *temp = head; // temp ptr to iterate
  while (temp->next != NULL) {
    temp = temp->next;
  }
  tail = temp; // updates tail pointer from newly sorted list
}

//splits linked list in two
node *dList::split(node* headRef) {
  if (headRef->next == NULL) { // if list only has one node
    return headRef; // return because it is sorted
  }

  else { // list has more than one node
    int length = 0; // to keep track of number of nodes
    node *temp = headRef; // temp ptr to iterate with
    while (temp != NULL) {
      length++; // count each node to track length of list
      temp = temp->next; // iterate
    }

    temp = headRef; // redefine temp to iterate again
    for (int i = 0; i < (length / 2); i++) { // to mark the middle node
      temp = temp->next;
    }

    node *middleNode = temp; // temp is the middle node after for loop, so name it such
    middleNode->prev->next = NULL; // cuts the middleNode list
    middleNode->prev = NULL;  // from the main list
    temp = headRef; // redefine temp to pass as argument

    temp = split(temp); // recursively split
    middleNode = split(middleNode); // recursively split

    return mergeLists(temp, middleNode); // return a function call to merge the sorted lists
  }
}

// merges two linked lists
node *dList::mergeLists(node *first, node *second) {
  node *newHead; // pointer for head of newly merged list
  node *current; // pointer to iterate with

  if (first->key < second->key) { // if first node of first list's key is smaller than first node of second list's
    newHead = first; // head of newly merged list is first node of first list
    first = first->next; // step through first list
    current = newHead; // to link the other nodes with newHead
  }
  else { // first node of second list's key is smaller than first node of first list's
    newHead = second; // head of newly merged list is first node of second list
    second = second->next; // step through second list
    current = newHead; // to link the other nodes with newHead
  }

  while (first != NULL && second != NULL) { // for iterating through the rest of first and second list
    if (first->key < second->key) { // same as above: check which key is smaller
      current->next = first; // links merged list w/ current node of first list
      first->prev = current; // links current node w/ merged list
      first = first->next; // step through first list
      current = current->next; // step through merged list
    }
    else { // second list's node's key was smaller
      current->next = second; // links merged list w/ current node of first list
      second->prev = current; // links current node w/ merged list
      second = second->next; // step through first list
      current = current->next; // step through merged list
    }
  }

  if (first == NULL) { // if first list became NULL first
    while (second != NULL) { // iterate through second list
      current->next = second; // links merged list with current node in second
      second->prev = current; // links current node in second with merged list
      second = second->next; // steps through second
      current = current->next; // steps through merged
    }
  }
  else { // second list became NULL first
    while (first != NULL) { // iterate through first list
      current->next = first; // links merged list with current node in first
      first->prev = current; // links current node in first with merged list
      first = first->next; // steps through first
      current = current->next; // steps through merged
    }
  }

  return newHead; // returns head of newly merged list
}
