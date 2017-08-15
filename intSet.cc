#include <iostream>
#include "intSet.h"
#include <sstream>
 
using namespace std;

/*intSet(): Deafalt Ctor
   purpose: initialize field with deafalut value
*/
intSet::intSet(){
    this->size = 0;
    this->capacity = 0;
    this->data = nullptr; //null
}

/*Copy Ctor
   purpose: call copy constructor
*/
intSet::intSet(const intSet& is){
    if(is.data == nullptr){ //if is is a empty set
        this->data = nullptr;
        this->size = 0;
        this->capacity = 0;
    }
    else{ //if is is not a empty set
        this->size = is.size;
        this->data = new int [this->size+1];
        for(int pos = 0; pos<this->size; pos++){
            this->data[pos] = is.data[pos];
        }
        this->capacity = is.capacity;
    }
}

/* call destructor
   purpose: dtor call
*/
intSet::~intSet(){
    delete [ ] this->data; //delete array
}

/* move cotr
   purpose: initialize a rvalue
*/
intSet::intSet(intSet &&is){
    if(is.data == nullptr){ //if is a a empty set
        this->data = nullptr;
        this->size = 0;
        this->capacity = 0;
    } //if
    else{
        this->size = is.size;
        this->capacity = is.capacity;
        this->data = is.data;
        is.data = nullptr;  //set is to null
    }
}

/* copy assignment operator
  purpose: set equal?
*/
intSet& intSet::operator=(const intSet& is){
    intSet t = is;
    this->swap(t); //call copy and swap
    return *this;
}

/*move assignment operator
 purpose: set equal?
*/
intSet& intSet::operator=(intSet &&is){
    //if is is empty;
    if(is.data == nullptr){
        delete [ ] this->data;
        this->data = nullptr;
        this->size = 0;
        this->capacity = 0;
        return *this;
    }
    //if orginal is empty
    else if(this->data == nullptr){
        this->size = is.size;
        this->capacity = is.capacity;
        this->data = is.data;
        is.data = nullptr;
        return *this;
    }
    //otherwise
    else{
        delete [ ] this->data;
        this->size = is.size;
        this->data = is.data;
        this->capacity = is.capacity;
        is.data = nullptr;
        return *this;
    }
}

/*copy and swap
  purpose: copy and swap two arguments
*/
void intSet::swap(intSet &is){
    //if they are the same.
    if(this->size == is.size){
        int check = 0;
        for(int index = 0; index < this->size; index++){
            if(this->data[index] == is.data[index]){
                check++;
            }
        }
        if(check == this->size){
            return;
        }
    }
    //if is is empty;
    else if(is.data == nullptr){
        delete [ ] this->data;
        this->data = nullptr;
        this->size = 0;
        this->capacity = 0;
    }
    //if orginal is empty
    else if(this->data == nullptr){
        this->size = is.size;
        this->capacity = is.capacity;
        this->data = new int [this->size+1];
        for(int pos = 0; pos<this->size; pos++){
            this->data[pos] = is.data[pos];
        }
    }
    //otherwise
    else{
        delete [ ] this->data;
        this->size =is.size;
        this->data = new int [this->size];
        for(int pos = 0; pos<this->size; pos++){
            this->data[pos] = is.data[pos];
        }
        this->capacity = is.capacity;
    }
}

/*read function
 purpose: read in and store
*/
istream& operator >> (istream &in, intSet &is){
    cout << "read get" << endl;
    int arr[100];
    int index = 0;
    while(in){
        in >> arr[index];
        index++;
    }
    int mylen = index;
    delete [ ] is.data;
    is.data = new int [mylen];
    for(int pos = 0; pos<mylen; pos++){
        is.data[pos] = arr[pos];
    }
    is.size = mylen;
    is.capacity = mylen*2;
    return in;
}

/*output operator
  purpose: cout a set
*/
ostream& operator<<(ostream& out, const intSet& is){
    if(is.size == 0){
        cout << "()";
        return out;
    }//if
    out << "(";
    for(int pos = 0; pos < is.size; pos++){
        if(pos == (is.size-1)){out << is.data[pos];}
        else{out<< is.data[pos] << ",";}
    }//for
    out << ")";
    return out;
}

/*union of a set
   purpose: add two set
*/
intSet intSet::operator|(const intSet &other){
    intSet newone;
    newone.data = nullptr;
    newone.size = 0;
    newone.capacity = 0;
    //both are empty
    if(this->data == nullptr && other.data == nullptr){
        return newone;
    }
    //other is empty
    else if(other.data == nullptr){
        newone.size = this->size;
        newone.capacity = this->capacity;
        newone.data = new int [newone.size];
        for(int pos = 0; pos < newone.size; pos++){
            newone.data[pos] = this->data[pos];
        }
        return newone;
    }
    //this is empty
    else if(this->data == nullptr){
        newone.size = other.size;
        newone.capacity = other.capacity;
        newone.data = new int [newone.size];
        for(int pos = 0; pos < newone.size; pos++){
            newone.data[pos] = other.data[pos];
        }
        return newone;
    }
    //both are not empty
    else{
        int arr[1000];
        int index = 0;
        int i = 0, j = 0;
        while(i < this->size && j < other.size){
            if(this->data[i] < other.data[j]){
                arr[index] = this->data[i++];
                index++;
            }
            else if(other.data[j] < this->data[i]){
                arr[index] = other.data[j++];
                index++;
            }
            else{
                arr[index] = other.data[j++];
                index++;
                i++;
            }
        }
        while(i < this->size){
            arr[index] = this->data[i++];
            index++;
        }
        while(j < other.size){
            arr[index] = other.data[j++];
            index++;
        }
        newone.size = index;
        newone.capacity = index+1;
        newone.data = new int [index];
        for(int pos = 0; pos < index; pos++){
            newone.data[pos] = arr[pos];
        }
        return newone;
    }//else
}

/* intersection
  purpose: take the intersection of two set
*/
intSet intSet::operator&(const intSet &other){
    //both are empty set
    if(this->data == nullptr && other.data == nullptr){
        return *this;
    }
    //this is empty
    else if(this->data == nullptr){
        return *this;
    }
    //other is empty
    else if(other.data == nullptr){
        return other;
    }
    //both are not empty
    else{
        int arr[100];
        int len = 0;
        int i = 0, j = 0;
        while(i < this->size && j < other.size){
            if(this->data[i] < other.data[j]){
                i++;
            }
            else if(other.data[j] < this->data[i]){
                j++;
            }
            else{
                arr[len] = other.data[j++];
                len++;
                i++;
            }
        }
        intSet newone;
        newone.data = new int [len];
        newone.size = len;
        newone.capacity = len+1;
        for(int pos = 0; pos < len; pos++){
            newone.data[pos] = arr[pos];
        }
        return newone;
    }
}

/* two set equal
  purpose: true if two sets are equal
           false otherwise
*/
bool intSet::operator==(const intSet &other){
    //if both are empty
    if(this->size == 0 && other.size == 0){
        return true;
    }
    //if either one is empty
    else if(this->size == 0 || other.size == 0){
        return false;
    }
    //if both are not empty set
    else if(this->size == other.size){
        for(int pos = 0; pos<this->size; pos++){
            if(this->data[pos] != other.data[pos]){
                return false;
            }
        }
        return true;
    }
    else{return false;}
}

/* subset of two sets
 purpose: true if one set is a subset of the other one
           false otherwise
*/
bool intSet::isSubset(intSet s){
    //if both are empty set
    if(this->size == 0 && s.size == 0){
        return true;
    }
    //if s is a empty set
    else if(s.size == 0 && this->size != 0){
        return true;
    }
    //if s contain more elements than this
    else if(s.size > this->size){
        return false;
    }
    //if both are not empty set
    else{
        int count = 0;
        for(int pos = 0; pos < s.size; pos++){
            for(int index = 0; index < this->size; index++){
                if(s.data[pos] == this->data[index]){
                    count++;
                }
            }
        }
        if(count == s.size){return true;}
        else{return false;}
    }
}

/* contain
 purpose: true if set is contain integer e
          false otherwise
*/
bool intSet::contains(int e){
    //if this is a empty set
    if(this->size == 0){return false;}
    //else
    else{
        for(int pos = 0; pos < this->size; pos++){
            if(this->data[pos] == e){
                return true;
            }
        }//for
        return false;
    }//else
}

/* sort
  purpose: sort a integer array
*/
void sort(intSet &a){
    int temp;
    for(int i = 0; i < a.size; i++){
        for(int j = 0; j < a.size-1; j++){
            if(a.data[j] > a.data[j+1]){
                temp = a.data[j];
                a.data[j] = a.data[j+1];
                a.data[j+1] = temp;
            }//for
        }//for
    }//for
}

/* add
 purpose: add a integer e to the set
*/
void intSet::add(int e){
    //if it is orginal set
    if(this->data == nullptr){
        this->capacity = 5;
        this->data = new int [this->capacity];
    }//check if e is already int set
    for(int index = 0; index < this->size; index++){
        if(e == this->data[index]){
            return;
        }
    }
    if(this->size >= this->capacity){
        //double the capacity, enrich the size
        this->capacity = this->capacity * 2;
        int *temp = new int [this->capacity];
        for(int index = 0; index<this->size; index++){
            //ues a temp for temporary store
            temp[index] = this->data[index];
        } //for
        delete [ ] this->data;
        this->data = temp;
    }//if
    this->data[this->size] = e;
    this->size++;
    sort(*this);
}

/* remove 
  purpose: element e is removed from the set
*/
void intSet::remove(int e){
    //if e is not the set
    int count = 0;
    for(int pos = 0; pos < this->size; pos++){
        if(e == this->data[pos]){
            count = 1;
        }
    }//fpr
    if(count == 0){return;}
    //if e is the first element of the set
    else if(this->data[0] == e){
        intSet newone;
        newone.size = this->size-1;
        newone.capacity = this->capacity;
        newone.data = new int [newone.size];
        int count = 1;
        for(int pos = 0; pos < newone.size;pos++){
            newone.data[pos] = this->data[count];
            count++;
        }//fpr
        delete [ ] this->data;
        this->size = newone.size;
        this->capacity = newone.capacity;
        this->data = new int [this->size];
        for(int pos = 0; pos < this->size; pos++){
            this->data[pos] = newone.data[pos];
        }
    }//else
    //if e is the last element of the set
    else if(this->data[size-1] == e){
        intSet newone;
        newone.size = this->size-1;
        newone.capacity = this->capacity;
        newone.data = new int [newone.size];
        int count = 0;
        for(int pos = 0; pos < newone.size; pos++){
            newone.data[pos] = this->data[count];
            count++;
        }//for
        delete [ ] this->data;
        this->size = newone.size;
        this->capacity = newone.capacity;
        this->data = new int [this->size];
        for(int pos = 0; pos < this->size; pos++){
            this->data[pos] = newone.data[pos];
        }
    }//else
    //otherwise
    else{
        for(int pos = 0; pos < this->size; pos++){
            if(this->data[pos] == e){
                intSet newone;
                newone.size = this->size-1;
                newone.capacity = this->capacity;
                newone.data = new int [newone.size];
                int index = 0;
                while(index < pos){
                    newone.data[index] = this->data[index];
                    index++;
                }
                int mypos = index;
                index++;
                while(index < this->size){
                    newone.data[mypos] = this->data[index];
                    index++;
                    mypos++;
                }
                delete [ ] this->data;
                this->size = newone.size;
                this->capacity = newone.capacity;
                this->data = new int [this->size];
                for(int pos = 0; pos < this->size; pos++){
                    this->data[pos] = newone.data[pos];
                }
                break;
            }
        }//for
    }//else
}
