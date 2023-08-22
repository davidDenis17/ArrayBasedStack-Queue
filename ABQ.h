//
//  ABQ.h
//  Lab 3 - Array-Based Stack and Queue
//
//  Created by David Denis on 2/6/23.
//

#define ABQ_h
#include <iostream>

using namespace std;

template <typename T>
class ABQ
{
    
    float scale_factor = 2.0f;
    T* arrayPtr = nullptr;
    int max_capacity;
    int current_size;
    int bottom = 0;
    int top = -1;
    
public:
    
    ABQ();
    ABQ(int capacity);
    ABQ(const ABQ &d);
    ABQ &operator=(const ABQ &d);
    ~ABQ();
    
    void enqueue(T data);
    
    T dequeue();
    T peek();
    
    unsigned int getSize();
    unsigned int getMaxCapacity();
    
    T* getData();
    
};

// Default Constructor
template <typename T>
ABQ<T>:: ABQ(){
    max_capacity = 1;
    current_size = 0;
    arrayPtr = new T[max_capacity];
}


// Constructors with Capacity Parameter
template <typename T>
ABQ<T>:: ABQ(int capacity){
    max_capacity = capacity;
    arrayPtr = new T[max_capacity];
    current_size = 0;
    
}


// Copy Constructor
template <typename T>
ABQ<T>:: ABQ(const ABQ &d){
    
    arrayPtr = new T[max_capacity];             // allocate memory for new object
    
    max_capacity = d.max_capacity;              // set capacities equal
    
    for (int i = 0; i < current_size; i++)
    {
        arrayPtr[i] = d.arrayPtr[i];            // deep copy to new object
    }
}


// Copy Assignment Operator
template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T> &d){
    
    arrayPtr = new T[max_capacity];             // allocate memory for new object
    
    for (int i = 0; i < current_size; i++)
    {
        arrayPtr[i] = d.arrayPtr[i];            // deep copy to new object
    }
    
    return *this;
}


// Destructor
template <typename T>
ABQ<T>:: ~ABQ(){
    delete[] arrayPtr;
}


// Adds item to the end of the queue (top of stack)
template <typename T>
void ABQ<T>:: enqueue(T data){
    
    current_size += 1;                                          // increase size of queue by 1
    top += 1;                                                   // location to stores data goes up by 1 (last in array/stack)
    
    if(current_size > max_capacity)
    {
        max_capacity *= scale_factor;                           // increase max capacity
        
        T* newArray = new T[max_capacity];                       // allocate new memory for new larger array
        
        for (int i = 0; i < current_size; i++){
            
            newArray[i] = arrayPtr[i];                          // deep copy
        }
        
        newArray[top] = data;                                   // add data to end of queue
        
        delete[] arrayPtr;                                      // delete old array
        arrayPtr = newArray;                                    // re-direct old pointer to new larger array
        
    }
    else
    {
        arrayPtr[top] = data;
    }
}


// pops first elemento of the array [bottom element]
template <typename T>
T ABQ<T>:: dequeue(){
    
    if (current_size == 0)
    {
        throw runtime_error("");                                    // check for runtime errors
    }
    
    T value_to_dequeue = arrayPtr[bottom];                          // assign value at location 0 of the array to a variable of type T
    current_size -= 1;                                              // decrease current size of queue
    //bottom += 1;
    
    if((float (current_size) / max_capacity) < (1 / scale_factor))
    {
        max_capacity /= scale_factor;                               // decrease capacity if half-full
        T* newArray = new T[max_capacity];                          // allocate memory for new smaller array
        
        for(int i = 0; i < current_size; i++){
            newArray[i] = arrayPtr[i + 1];                          // deep copy starting from 1 (first element [0] was popped)
        }
        
        delete[] arrayPtr;                                          // delete old array memory
        arrayPtr = newArray;                                        // re-direct old array pointer to new array
        
    }
    else
    {
        T* newArray = new T[max_capacity];                          // allocate memory to deep copy new array without bottom value
        
        for(int i = 0; i < current_size; i++){
            newArray[i] = arrayPtr[i + 1];                          // deep copy starting from 1 (first element [0] was popped)
        }
        
        delete[] arrayPtr;                                          // delete old array memory
        arrayPtr = newArray;
    }
    
    return value_to_dequeue;                                        // return value to dequeue
}


// returns first element in queue [element 0]
template <typename T>
T ABQ<T>:: peek(){
    if (current_size == 0){
        throw runtime_error("");
    }
    
    return arrayPtr[bottom];
}


// returns current size of queue
template <typename T>
unsigned int ABQ<T>:: getSize(){
    
    return current_size;
}


// returns max capacity of queue
template <typename T>
unsigned int ABQ<T>:: getMaxCapacity(){
    
    return max_capacity;
}


// return adress of arrayPtr's first element
template <typename T>
T* ABQ<T>:: getData(){
    
    return arrayPtr;
}
