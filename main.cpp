//
//  main.cpp
//  pic10_hw3
//
//  Created by Runyu Qian on 5/28/18.
//  Copyright © 2018 Runyu Qian. All rights reserved.
//

#include <iostream>



// Description: An incomplete implementation of iterators for a
//              RingQueue class.
//
// Notes: The project DOES compile but there is no meaningful
//              output
//
// Your job: To complete this set of classes so that the output
//              produced by 'main' (below), matches the sample
//              file provided at the end of this file.


#include <iostream>

// Forward declaration
template <typename ItemType, int MAX_SIZE>
class RingQueue;



template <typename ItemType, int MAX_SIZE>
class RingQueue{
    
    // Nested Forward declaration of RingQueue<ItemType,MAX_SIZE>::iterator
    // This is needed if one plans to turn this home-made iterator into
    // one of the special categories of iterators (e.g., input, output,
    // forward, etc.).
public:
    class iterator;
    
    
    
    // Aliases.
    typedef ItemType* pointer;
    typedef ItemType& reference;
    
    
    
    // Definition of RingQueue<ItemType,MAX_SIZE>::iterator
public:
    class iterator{
    private:
        // A link to the parent container
        RingQueue* parent;
        
        // The position within the RingQueue is determined
        // by how far ahead we are from the begining of the
        // queue.
        int offset = 0;
        
    private:  // Private constructor???
        iterator(RingQueue* _parent, int _offset = 0 )
        : parent(_parent), offset(_offset) { }
        
        
        // It is quite common for Containers and their iterators
        // to be friends. After all, they should work closely together.
        friend class RingQueue<ItemType,MAX_SIZE>;
        
        
    public:
        reference operator*() {
            // Replace the line(s) below with your code.
            
            int ring_size = this->parent->ring_size;
            int begin_index = this->parent->begin_index;
            int Max =MAX_SIZE;
            int correction  = begin_index+ring_size-Max;
            int answer = begin_index+offset;
            
            
            
            
            if( (begin_index + offset) == Max){
            
                std::cout<<"  whaaaat      "<<  std::endl;
                if (correction>0){
                    answer = 0;
                    std::cout<<"  correction     correction   "<<  std::endl;
                }
                else{
                    answer = begin_index;
                }
            }
            else{
                answer = (begin_index+offset)% Max;
                
                //std::cout<<"  whaaaat     happpennnned   "<<offset<<"   "<<  std::endl;
            }
            
            
            
            
            return parent->buffer[answer] ;
        }
        
        iterator& operator++(){
            
            // Replace the line(s) below with your code.
        
            offset = (offset+1)%this->parent->ring_size;

            return *this;
        }
        
        iterator operator++( int unused ){
            
            offset++;
            return *this;
        }
        
        bool operator==( const iterator& rhs ) const {
            // Replace the line(s) below with your code.
            
            if((this->parent ==  *(&rhs.parent)) && (this->offset == rhs.offset)){
                 //std::cout<<"hahahahahahah    true        ahahahah"<<  (this ==  &rhs)<< "dljasdjaljd"<<std::endl;
               return true;
            }
            else{
                 //std::cout<<"hahaha=======hahah      false      ahahahahah"<<std::endl;
            return false;
            }
        }
        
        bool operator!=( const iterator& rhs ) const {
            // Replace the line(s) below with your code.
            if((this->parent ==  *(&rhs.parent)) && (this->offset == rhs.offset)){
                //std::cout<<"hahahahahah      false      ahahahahah"<<std::endl;
                return false;
            }
            else{
               
                /*
                if((this->offset != rhs.offset))
                {std::cout<<"hahahahahahah   offfffffsssseeett       ahahahah"<<std::endl;
                 std::cout<<"this   offset   "<<this->offset<<std::endl;
                    std::cout<<"rhs   offset "<<  rhs.offset<<std::endl;
                    std::cout<<std::endl;
                    
                    
                    
                }
                */
                
                //std::cout<<"hahahahahahah    true        ahahahah"<<std::endl;
                return true;
            }
        }
        
    };
    
    
    
    /**
     class const_iterator{
     private:
     RingQueue* parent;
     int offset;
     
     private:
     // Only RingQueue objects can create const_iterators...
     const_iterator() ;
     
     public:
     // ... however, const_iterators can be 'copied'.
     const_iterator( const const_iterator& ) ;
     
     friend class RingQueue<ItemType,MAX_SIZE>;
     };
     */
    
    
    
    // Friendship goes both ways here.
    friend class iterator;
    // friend class const_iterator;  // not implemented... yet.
    
    
    
private:
    // A fixed-size static array with constant capacity that represents
    // the RingQueue
    ItemType buffer[MAX_SIZE];
    
    // The starting index. It changes according to a very
    // specific set of rules (below).
    int begin_index;
    
    // The actual size of the RingQueue. Not to be confused with
    // its capacity.
    int ring_size;
    
    
    
    // A helper function that computes the index of 'the end'
    // of the RingQueue
    
    int end_index() const {
        
        // Replace the line(s) below with your code.
        int end_index = (this->begin_index + this->ring_size) % MAX_SIZE;
        return end_index;
    }
    
    
    
public:
    // Constructor
    RingQueue() : begin_index(0), ring_size(0) { }
    
    // Accessors. Note: 'back()' is not considered part of the array.
    ItemType front() const {
        if ( ring_size == 0 ) std::cerr<< "Warning: Empty ring!\n" ;
        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        // Feel free to throw instead...
        
        
        // Replace the line(s) below with your code.
        
        int answer = begin_index;
        
        
        return buffer[answer];
    }
    ItemType back() const {
        if ( ring_size == 0 ) std::cerr<< "Warning: Empty ring!\n" ;
        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        // Feel free to throw instead...
        
        
        // Replace the line(s) below with your code.
        int answer = this->end_index();
        
        return buffer[answer];
    }
    
    
    
    // Mutators
    void push_back( const ItemType& value ){
        

        if(ring_size == 0){
            
            int end_index2 = this->end_index();
            this->buffer[end_index2] = value;
            
            this->ring_size++;
            
        }
        else{
            if((this->ring_size+this->begin_index) != MAX_SIZE){
                int end_index2 = this->end_index();
                this->buffer[end_index2] = value;
                this->ring_size++;
                
            }
            else{
                int end_index2 = this->end_index();
                this->buffer[end_index2] = value;
                this->begin_index = (this->begin_index+1)%(MAX_SIZE-1);
                
                
            }
        }
     
        
         std::cout << "  begin_index: " << this->begin_index << "   ring_size : " << this->ring_size << "   end_index : " << this->end_index()<< '\n';
        
        
        return;
    }
    void pop_front(){
        
        if(ring_size == 0){
            std::cout << "  ring_size is zero: " <<'\n';
        }
        else{
            
            
            this->ring_size--;
            this->begin_index = (this->begin_index+1)%(MAX_SIZE-1);
            
            std::cout << "  begin_index: " << this->begin_index << "   ring_size : " << this->ring_size << "   end_index : " << this->end_index()<< '\n';
        
        }
        return;
    }
    
    // Functions that return iterators
    iterator begin() {
        

        return iterator(this,0);
    }
    iterator end() {
        // Replace the line(s) below with your code.
        
        
        //std::cout<<"           end  index:    "<< this->ring_size<<std::endl;
        
        return iterator(this,this->ring_size-1);
        
        
        
        
        
        
    }
    
    // Miscellaneous functions
    size_t size() const {
        // Replace the line(s) below with your code.
        return this->ring_size;
    }
    
    // Debugging functions
    void dump_queue() const {
        std::cout << "Raw queue...\n";
        for ( size_t i = 0 ; i < MAX_SIZE ; ++i )
            std::cout << "Val: " << buffer[i] << ", at: " << buffer+i << '\n';
        std::cout << '\n';
        return;
    }
    
};

int main(){
    
    
    RingQueue<int,7> rq;
    rq.dump_queue();
    
    for ( int i = 0 ; i < 8 ; ++i )
        rq.push_back(i+1);
    
    
     std::cout << "hhhhh      hhhhhhhh: "<< '\n';
    rq.dump_queue();
    rq.pop_front();
    
    
    std::cout << "Queue via size: \n";
    
    // RingQueue<int,7>::iterator it = rq.begin() ;
    auto it = rq.begin() ;

    
    std::cout << "hhhhh      hhhhhhh   hhhhhhhhhhhhhhhhhhhhh: "<<rq.size()<< '\n';
    for ( size_t i = 0 ; i < rq.size() ; ++i ) {
        std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
        std::cout << '\n';
        ++it;
    }
    std::cout << '\n';
    
    
    
    // Uncomment the block below only when you have a working
    // implementation of RingQueue<ItemType,int>::end().
    // If the implementation is not correct, it might result in
    // an infinite loop.
    
    
    auto it2 = rq.begin();
    auto it3 = rq.begin();
    
    
    std::cout<<" chech ======    " << (it2 == it3)<<std:: endl;
    
    
    
     std::cout << "Queue via iterators: \n";
     for ( auto it = rq.begin() ; it != rq.end() ; ++it ) {
     std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
     }
     std::cout << '\n';
    
    
    
    
    rq.dump_queue();
    
    return 0;
}



/**
 +++++++++++++++++++++++++++++++++++++++++++++++
 The output of your program [once the missing
 code is added] should look more or less like
 the output below.
 
 Note:
 It is dependent on the device where
 this driver is executed. However, it
 should be clear that the difference
 between consecutive memory addresses
 is equal to the number reported by
 'size_of( int )'.
 +++++++++++++++++++++++++++++++++++++++++++++++
 
 Raw queue...
 Val: 2, at: 0x7ffcdeeaab40
 Val: 0, at: 0x7ffcdeeaab44
 Val: 4198285, at: 0x7ffcdeeaab48
 Val: 0, at: 0x7ffcdeeaab4c
 Val: 0, at: 0x7ffcdeeaab50
 Val: 0, at: 0x7ffcdeeaab54
 Val: 0, at: 0x7ffcdeeaab58
 
 Raw queue...
 Val: 8, at: 0x7ffcdeeaab40
 Val: 2, at: 0x7ffcdeeaab44
 Val: 3, at: 0x7ffcdeeaab48
 Val: 4, at: 0x7ffcdeeaab4c
 Val: 5, at: 0x7ffcdeeaab50
 Val: 6, at: 0x7ffcdeeaab54
 Val: 7, at: 0x7ffcdeeaab58
 
 Queue via size:
 Value: 3, address: 0x7ffcdeeaab48
 Value: 4, address: 0x7ffcdeeaab4c
 Value: 5, address: 0x7ffcdeeaab50
 Value: 6, address: 0x7ffcdeeaab54
 Value: 7, address: 0x7ffcdeeaab58
 Value: 8, address: 0x7ffcdeeaab40
 
 Queue via iterators:
 Value: 3, address: 0x7ffcdeeaab48
 Value: 4, address: 0x7ffcdeeaab4c
 Value: 5, address: 0x7ffcdeeaab50
 Value: 6, address: 0x7ffcdeeaab54
 Value: 7, address: 0x7ffcdeeaab58
 Value: 8, address: 0x7ffcdeeaab40
 
 Raw queue...
 Val: 8, at: 0x7ffcdeeaab40
 Val: 2, at: 0x7ffcdeeaab44
 Val: 3, at: 0x7ffcdeeaab48
 Val: 4, at: 0x7ffcdeeaab4c
 Val: 5, at: 0x7ffcdeeaab50
 Val: 6, at: 0x7ffcdeeaab54
 Val: 7, at: 0x7ffcdeeaab58
 */
