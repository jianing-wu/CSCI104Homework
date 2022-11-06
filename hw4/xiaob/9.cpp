template <class T>
class set {
  public:

    set (); // empty set constructor

    void insert (const T & item); // runs in O(log n); ignores duplicates

    void remove (const T & item); // runs in O(log n); does nothing if item is not in set

    bool contains (const T & item) const; // runs in O(log n)


    class iterator{

        set<T>::iterator operator++ (); // assume this runs in O(1)

        set<T>::iterator operator= (const set<T>::iterator & other); // runs in O(1)

        bool operator== (const set<T>::iterator & other) const; // runs in O(1)

        const T & operator* (); // runs in O(1)

    };


    set<T>::iterator begin() const; // runs in O(1)

    set<T>::iterator end() const; // runs in O(1)

};


template <class T>
class extendedset : public set {
public:
	extendedset();
	void insert(const T & item) {
		set::insert(item);
	}

	void remove(const T & item) {
		set::remove(item);
	}

	bool contains(const T & item) const{
		return set::contains(item);
	}

	extendedset<T> operator|| (const set<T>& other) const;
	extendedset<T> operator&& (const set<T>& other) const;
};

template <class T>
extendedset<T> extendedset::operator|| (const set<T>& other) const {
	extendedset<T> unionSet;
	set<T>::iterator it;
	for (it = this.begin(); it != this.end(); it++) {
		unionSet.insert(*it);
	}

	for (it = other.begin(); it < other.end(); it++) {
		unionSet.insert(*it);
	}
	return unionSet;
}

template <class T>
extendedset<T> extendedset::operator&& (const set<T>& other) const {
	extendedset<T> interSet;
	set<T>::iterator it;
	for (it = this.begin(); it != this.end(); it++) {
		if(other.contains(*it)) {
			interSet.insert(*it);
		}
	}

	return interSet;
}


int main() {
	return 0;
}