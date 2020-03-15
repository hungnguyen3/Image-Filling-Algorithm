/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 */

/**
 * Default constructor. Remember to initialize any variables you need
 * and allocate any required memory. The initial size of `items` should
 * be DEFAULTCAPACITY defined in stack.h.
 *
 */
template <class T> Stack<T>::Stack()
{
    /**
     * @todo Your code here!
     */
    //TO-DO: ask this
    
    // allocate 'stack array', size: DEFAULTCAPACITY, type: T
    this->items = new T[DEFAULTCAPACITY];

    // no item in the stack
    this->num_items = 0; 

    // max of 4 items since the array has size 4
    this->max_items = DEFAULTCAPACITY;
}

/**
 * Destructor. Remember to free any memory allocated.
 *
 */
template <class T> Stack<T>::~Stack()
{
    /**
     * @todo Your code here!
     */
    
    //TO-DO: ask this!
    delete [] items;
    max_items = DEFAULTCAPACITY;
    num_items = 0;
}

/**
 * Adds the parameter object to the top of the Stack. If the dynamic array
 * holding the stack elements is full the array should be resized. Resize should be
 * called by multiplying current capacity EXPANSIONFACTOR defined in stack.h.
 * To be clear resize should happen before adding the element to the stack and only
 * when the stack is completely full.
 *
 * @param: value The object to be added to the Stack.
 */
template <class T>
void Stack<T>::push(const T &newItem){
    /**
     * @todo Your code here!
     */

    // if it is full
    if(this->num_items >= this->max_items){  
        // Resize should be called by multiplying  current capacity EXPANSIONFACTOR
        resize((this->max_items)*EXPANSIONFACTOR);
        
        // add item onto the stack at the top of the stack
        this->items[this->num_items] = newItem;
        this->num_items++;
    }
    // if not full
    else{
        // add item onto the stack at the top of the stack
        this->items[this->num_items] = newItem;
        this->num_items++;
    }
};

/**
 * Remove the object on top of the Stack, and returns it. You may assume this function
 * is only called when the Stack is not empty. If the size of the stack changes
 * to strictly less than 1 / SHRINKRATE (where SHRINKRATE is defined in stack.h)
 * after the item is removed the Stack should be resized to 1 / EXPANSIONFACTOR.
 * The capacity of the stack should never decrease below DEFAULTCAPACITY to avoid
 * corner cases where the stack size goes to zero.
 *
 * @return The element that used to be at the top of the Stack.
 */
template <class T>
T Stack<T>::pop(){
    /**
     * @todo Your code here!
     */

    // decrease the number of elements in the stack
    this->num_items--;

    // find the value at the top of the stack
    T ret = this->items[this->num_items];

    // resize if needed
    if(num_items < capacity()/SHRINKRATE && capacity()/EXPANSIONFACTOR >= DEFAULTCAPACITY){
        resize(capacity()/EXPANSIONFACTOR);
    }
    
    // return the object on top of the Stack
    return ret;
};

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T> void Stack<T>::add(const T &theItem)
{
    /**
     * @todo Your code here! Hint: this should call another Stack function
     *  to add the element to the Stack.
     */
    (*this).push(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T> T Stack<T>::remove()
{
    /**
     * @todo Your code here! Hint: this should call another Stack function
     * to remove an element from the Stack and return it.
     */
    T ret = (*this).pop();
    return ret;
}

/**
 * Finds the object on top of the Stack, and returns it to the caller.
 * Unlike pop(), this operation does not alter the Stack itself. It should
 * look at the beginning of the list. You may assume this function is only
 * called when the Stack is not empty.
 *
 * @return The element at the top of the Stack.
 */
template <class T>
T Stack<T>::peek(){
    /**
     * @todo Your code here!
     */
    // find the value at the top of the stack
    T ret = this->items[this->num_items-1];

    //return element at the top of the Stack
    return ret;
};

/**
 * Determines if the Stack is empty.
 *
 * @return Whether or not the stack is empty (bool).
 */
template <class T>
bool Stack<T>::isEmpty() const {
    /**
     * @todo Your code here!
     */
    if(num_items == 0){
        return true;
    }
    else{
        return false;
    }
};

/**
 * Return the maximum number of items the stack can hold.
 *
 * Note: This is an implementation detail we would normally hide.
 * We include it here for testing purposes.
 *
 * @return Maximum number of items the stack can hold (int)
 */
template <class T>
size_t Stack<T>::capacity() const {
    return this->max_items;
};

/**
 * Return the number of items on the stack.
 *
 * @return Number of items on the stack (int)
 */
template <class T>
size_t Stack<T>::size() const {
    return this->num_items;
};

/**
 * Resize the the member variable `items`.
 * Don't forget to free up any memory that is no longer used.
 *
 * @param n The size of the stack after resizing
 */
template <class T>
void Stack<T>::resize(size_t n){
    /**
     * @todo Your code here!
     */

    // create tmp of new size
    T *tmp = new T[n];

    // copy content from *items into tmp
    for(size_t i = 0; i < num_items; i++){
        tmp[i] = items[i];
    }

    delete[] items;

    // update max_items
    this->max_items = n;
    items = tmp;
};
