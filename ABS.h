//
//  ABS.h
//  Lab 3 - Array-Based Stack and Queue
//
//  Created by David Denis on 2/4/23.
//

#define ABS_h
#include <iostream>

using namespace std;

template <typename T>
class ABS
{
    
    float scale_factor = 2.0f;
    T* arrayPtr = nullptr;
    int max_capacity;
    int current_size;
    int top = -1;
    
public:
    
    ABS();
    ABS(int capacity);
    ABS(const ABS &d);
    ABS &operator=(const ABS &d);
    ~ABS();
    
    void push(T data);
    
    T pop();
    T peek();
    
    unsigned int getSize();
    unsigned int getMaxCapacity();
    
    T* getData();
    
    
};

// Default Constructor
template <typename T>
ABS<T>:: ABS(){
    max_capacity = 1;
    current_size = 0;
    arrayPtr = new T[max_capacity];
    
}

// Constructor with capacity parameter
template <typename T>
ABS<T>:: ABS(int capacity){
    max_capacity = capacity;
    arrayPtr = new T[max_capacity];
    current_size = 0;
}

// Copy Constructor
template <typename T>
ABS<T>:: ABS(const ABS &d){
    arrayPtr = new T[max_capacity];         // allocate memory
    
    max_capacity = d.max_capacity;           // set capacities equal
    
    for(int i = 0; i < current_size; i++){  // deep copy
        arrayPtr[i] = d.arrayPtr[i];
    }
    
}

// Copy Assignment Operator
template <typename T>
ABS<T>& ABS<T>::operator=(const ABS<T> &d){
    arrayPtr = new T[max_capacity];         // allocate memory
    
    for(int i = 0; i < current_size; i++){  // deep copy
        arrayPtr[i] = d.arrayPtr[i];
    }
    
    return *this;
}

// Destructor
template <typename T>
ABS<T>:: ~ABS(){
    delete[] arrayPtr;
}


// push new item to the top of the stack
template <typename T>
void ABS<T>:: push(T data){
    
    current_size += 1;                                  // push method called: increase size of elements in array
    top += 1;                                           // increase top to reference new item in array
    
    if (current_size > max_capacity) {                  // check capacity
        max_capacity = max_capacity * scale_factor;     // increase capacity
        
        T* tempArray = new T[max_capacity];             // allocate memory for temp larger array --> + 1 ensures that there is no overflow when current_size == max_capacity
        
        for(int i = 0; i < current_size; i++){          // create new array up to current size (# of elements to store in the new array)
            tempArray[i] = arrayPtr[i];                 // deep copy old array into temp one
        }
        
        tempArray[top] = data;                          // add new data to the top of the array
       
        delete[] arrayPtr;                              // delete memory for old array
        arrayPtr = tempArray;                           // re-direct pointers from old array to temp array
    
        
        
    }
    else {
        
       arrayPtr[top] = data;                            // place data at the top of array
        
    }
    
  
}


// pop element from top of the stack
template <typename T>
T ABS<T>:: pop(){
    
    if (current_size == 0)
    {
        throw runtime_error("");                        // check size for runtime error
    }
    
    T value_to_pop = arrayPtr[top];                     // store value to pop in variable
    current_size -= 1;                                  // reduce size of elements in array
    top -= 1;                                           // decrease top to next element in array
    
    if ((float (current_size) / max_capacity) < (1 / scale_factor))
    {
        max_capacity = max_capacity / scale_factor;
        T* tempArray = new T[max_capacity];             // allocate memory for temp smaller array
        
        for(int i = 0; i < current_size; i++){          // create new array up to current size (# of elements to store in the new array)
            tempArray[i] = arrayPtr[i];                 // deep copy old arrat into temp one
        }
        
        
        delete[] arrayPtr;                              // delete memory of temp array
        arrayPtr = tempArray;                           // re-direct pointers from old array to new array
    }
    

    return value_to_pop;                                // return popped value
}



template <typename T>
T ABS<T>:: peek(){
    
    if (current_size == 0)                              // if stack is empty, trow runtime error
    {
        throw runtime_error("");
    }
    
    return arrayPtr[top];                               // returns value at the top of the stack
    
}

template <typename T>
unsigned int ABS<T>:: getSize(){
    
    return current_size;                                // returns current size
}


template <typename T>
unsigned int ABS<T>:: getMaxCapacity(){
    
    return max_capacity;                                // returns max capacity
}


template <typename T>                                   // returns memory location of first element in array
T* ABS<T>:: getData(){
    
    return arrayPtr;
}


