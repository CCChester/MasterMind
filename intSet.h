#ifndef _INTSET_H_
#define _INTSET_H_
#include <iostream>
struct intSet {
    int *data;
    int size;
    int capacity;
    
    intSet();
    intSet(const intSet& is);
    ~intSet();
    intSet(intSet &&is);
    intSet &operator=(const intSet& is);
    intSet &operator=(intSet &&is);
    void swap(intSet &is);
    intSet operator|(const intSet &other); // Set union
    intSet operator&(const intSet &other); // Set intersection.
    bool operator==(const intSet &other);  // Set equality.
    bool isSubset(intSet s);  // True if s is a subset of *this
    bool contains(int e);     // True if *this contains e
    void add(int e);          // Adds int e to this set.
    void remove(int e);       // Removes int e ot this set.
};
std::ostream& operator<<(std::ostream& out, const intSet& is);
std::ostream& operator>>(std::istream& in, const intSet &is);
#endif
