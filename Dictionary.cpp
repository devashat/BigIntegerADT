/********************************************************************************* 
* Devasha Trivedi, detrived
* 2022 Spring CSE101 PA8
* Dictionary.cpp
* Implementation of the Dictionary ADT
*********************************************************************************/
#include <iostream>
#include "Dictionary.h"

// Class Constructors & Destructors ----------------------------------------

using namespace std;

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

Dictionary::Dictionary() {
    nil = nullptr;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary &D) {
    nil = D.nil;
    root = nil;
    current = nil;
    num_pairs = 0;

    preOrderCopy(D.root, nullptr);
}

// Destructor
Dictionary::~Dictionary() {
    nil = nullptr;
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    bool return_val = true;

    Node *node = search(root, k);
    if (node == nil) {
        return_val = false;
    }

    return return_val;
}

valType &Dictionary::getValue(keyType k) const {
    Node *n = search(root, k);

    if (n == nil) {
        throw std::range_error("Error{getValue()}: No key 'k' exists");
    }

    return n->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const {
    return (current != nil);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const {
    if (hasCurrent() == false) {
        throw std::logic_error("Error{hasCurrent()}: current not defined.");
    }
    return current->key;
}

valType &Dictionary::currentVal() const {
    if (hasCurrent() == false) {
        throw std::logic_error("Error{hasCurrent()}: current not defined.");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    while (size() != 0) {
        postOrderDelete(root);
        root = nil;
        current = nil;
        num_pairs = 0;
    }
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {

    Node *y = nil;
    Node *x = root;

    while (x != nil) {
        y = x;
        if (k < x->key) {
            x = x->left;
        } else if (k > x->key) {
            x = x->right;
        } else {
            x->val = v;
            return;
        }
    }

    Node *z = new Dictionary::Node(k, v);
    z->left = nil;
    z->right = nil;
    z->color = RED;

    z->parent = y;

    if (y == nil) {
        root = z;
        root->color = BLACK;
    } else {
        if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
        RB_InsertFixUp(z);
    }

    num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    Node *x, *y;
    int y_color;

    Node *z = search(root, k);

    if (z != nil) {
        y = z;
        y_color = y->color;

        if (z->left == nil) {
            x = z->right;
            RB_Transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            RB_Transplant(z, z->left);
        } else {
            Node *y = findMin(z->right);
            y_color = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x != nil) {
                    x->parent = y;
                }
            } else {
                RB_Transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            RB_Transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        if (current == z) {
            current = nil;
        }

        if (y_color == BLACK) {
            RB_DeleteFixUp(x);
        }

        num_pairs--;
    }
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {
    if (num_pairs > 0) {
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end() {
    if (num_pairs > 0) {
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (hasCurrent() == false) {
        current = nil;
    } else {
        Node *x = current;
        if (x->right != nil) { // case 1
            current = findMin(x->right);
        } else {
            Node *y = x->parent; // case 2
            while (y != nil and x == y->right) {
                x = y;
                y = y->parent;
            }

            current = y;
        }
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (hasCurrent() == false) {
        current = nil;
    } else {
        Node *x = current;

        if (x->left != nil) { // case 1
            current = findMax(x->left);
        } else {
            Node *y = x->parent; // case 2
            while (y != nil and x == y->left) {
                x = y;
                y = y->parent;
            }

            current = y;
        }
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary &D) const {
    bool result = true;

    if (num_pairs != D.size()) {
        result = false;
    } else {
        if (num_pairs != 0 && D.size() != 0) {
            Dictionary tmpA;
            tmpA.nil = nil;
            tmpA.preOrderCopy(root, nullptr);
            Dictionary tmpB = Dictionary(D);

            tmpA.begin();
            tmpB.begin();

            while (tmpA.hasCurrent() && tmpB.hasCurrent()) {
                if ((tmpA.currentKey() != tmpB.currentKey())
                    || (tmpA.currentVal() != tmpB.currentVal())) {
                    result = false;
                }

                tmpA.next();
                tmpB.next();
            }
        }
    }

    return result;
}

std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
    stream << D.to_string() << endl;

    return stream;
}

bool operator==(const Dictionary &A, const Dictionary &B) {
    return A.equals(B);
}

Dictionary &Dictionary::operator=(const Dictionary &D) {
    Dictionary tmp = D;

    std::swap(nil, tmp.nil);
    std::swap(current, tmp.current);
    std::swap(root, tmp.root);
    std::swap(num_pairs, tmp.num_pairs);

    return *this;
}
