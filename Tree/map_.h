#pragma once
#include <iostream>
using namespace std;

template<class T1, class T2>
struct node {
	T1 key;
	T2 value;
	node<T1, T2> *parent = nullptr;
	node<T1, T2> *left = nullptr;
	node<T1, T2> *right = nullptr;
};


template<class T1, class T2>
class map_
{
	node<T1, T2> *root;
	int size;
public:
	map_();
	void insert(const T1& key, const T2& value);
	T1& min()const;
	node<T1, T2>* minNode(node<T1, T2>*nd)const;

	T1& max()const;
	node<T1, T2>* maxNode(node<T1, T2>*nd)const;

	node<T1, T2>* nextElement(const T1& key);
	node<T1, T2>* prevElement(const T1& key);

	void erase(const T1& key);	

	T2& find(const T1& key);
	void print()const;
	void printNode(node<T1, T2>*nd) const;

	void copyNode(node<T1, T2>*nd);
	map_(const map_<T1, T2>&obj);

	map_(map_<T1, T2>&&obj);
	map_<T1, T2>& operator=(const map_<T1, T2>&obj);
	map_<T1, T2>& operator=(map_<T1, T2>&&obj);
	
	~map_();
	void deleteNodes(node<T1, T2>*nd);
};



template<class T1, class T2>
inline map_<T1, T2>::map_()
{
	root = nullptr;
	size = 0;
}

template<class T1, class T2>
void map_<T1, T2>::insert(const T1 & key, const T2 & value)
{
	node<T1, T2> *newNode = new node<T1, T2>;
	newNode->key = key;
	newNode->value = value;
	if (root == nullptr) {
		root = newNode;
		size = 1;
		return;
	}
	node<T1, T2>*tmp = root;
	node<T1, T2>*y = nullptr;
	while (tmp != nullptr) {
		y = tmp;
		if (key < tmp->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	if (key < y->key)
		y->left = newNode;
	else
		y->right = newNode;
	newNode->parent = y;
	size++;
}

template<class T1, class T2>
inline T1 & map_<T1, T2>::min() const
{	
	return minNode(root)->key;
}

template<class T1, class T2>
inline node<T1,T2>* map_<T1, T2>::minNode(node<T1, T2>* nd) const
{
	while (nd->left != nullptr) {
		nd = nd->left;
	}
	return nd;
}

template<class T1, class T2>
inline T1 & map_<T1, T2>::max() const
{
	return maxNode(root)->key;
}

template<class T1, class T2>
inline node<T1,T2>* map_<T1, T2>::maxNode(node<T1, T2>* nd) const
{
	while (nd->right != nullptr) {
		nd = nd->right;
	}
	return nd;
}

template<class T1, class T2>
inline node<T1,T2>* map_<T1, T2>::nextElement(const T1& key) 
{
	node<T1, T2>*tmp = root;
	while (tmp != nullptr && key != tmp->key) {
		if (key < tmp->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	
	if (tmp->right != nullptr) {
		return minNode(tmp->right);
	}
	node<T1, T2>*y = tmp->parent;
	while (y != nullptr && tmp == tmp->right) {
		tmp = y;
		y = y->parent;
	}
	return y;
}

template<class T1, class T2>
inline node<T1,T2>* map_<T1, T2>::prevElement(const T1 & key)
{
	node<T1, T2>*tmp = root;
	while (tmp != nullptr && key != tmp->key) {
		if (key < tmp->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	if (tmp->left != nullptr) {
		return maxNode(tmp->left);
	}
	node<T1, T2>*y = tmp->parent;
	while (y != nullptr && tmp == tmp->left) {
		tmp = y;
		y = y->parent;
	}
	return y;
}

template<class T1, class T2>
inline void map_<T1, T2>::erase(const T1 & key)
{
	if (root == nullptr)
		return;	
	node<T1, T2>*tmp = root;
	while (tmp != nullptr && key != tmp->key) {
		if (key < tmp->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	
	
	if (tmp->left == nullptr && tmp->right == nullptr) {
		if (tmp->parent->left==tmp)
			tmp->parent->left = nullptr;
		if (tmp->parent->right==tmp)
			tmp->parent->right = nullptr;
		delete tmp;
	}
	else if (tmp->left == nullptr || tmp->right == nullptr) {
		if (tmp->left == nullptr) {
			if (tmp->parent->left == tmp)
				tmp->parent->left = tmp->right;
			else 
				tmp->parent->right = tmp->right;
			tmp->right->parent = tmp->parent;				
		}
		else {
			if (tmp->parent->left == tmp)
				tmp->parent->left = tmp->left;
			else
				tmp->parent->right = tmp->left;
			tmp->left->parent = tmp->parent;
		}
		delete tmp;
	}
	else {
		node<T1, T2>*y = nextElement(tmp->key);
		tmp->key = y->key;
				
		if (y->parent->left == y) {
			y->parent->left = y->right;
			if (y->right != nullptr)
				y->right->parent = y->parent;
		}
		else {
			y->parent->right = y->right;
			if (y->right != nullptr)
				y->right->parent = y->parent;
		}
		delete y;
	}	
	
	size--;

}


template<class T1, class T2>
inline T2 & map_<T1, T2>::find(const T1 & key)
{
	node<T1, T2>*tmp = root;
	while (tmp != nullptr && key != tmp->key) {		
		if (key < tmp->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return tmp->value;	
}

template<class T1, class T2>
inline void map_<T1, T2>::print() const
{
	printNode(root);
}

template<class T1, class T2>
inline void map_<T1, T2>::printNode(node<T1, T2>* nd) const
{
	if (nd != nullptr) {
		printNode(nd->left);
		cout << nd->key << " " << nd->value << endl;
		printNode(nd->right);
	}
}

template<class T1, class T2>
inline void map_<T1, T2>::copyNode(node<T1, T2>* nd)
{
	if (nd != nullptr)
	{
		insert(nd->key, nd->value);
		copyNode(nd->left);
		copyNode(nd->right);
	}

}

template<class T1, class T2>
inline map_<T1, T2>::map_(const map_<T1, T2>& obj)
{
	copyNode(obj.root);
}

template<class T1, class T2>
inline map_<T1, T2>::map_(map_<T1, T2>&& obj)
{
	this->root = obj.root;
	this->size = obj.size;
	obj.root = nullptr;
	obj.size = 0;
}

template<class T1, class T2>
inline map_<T1, T2>& map_<T1, T2>::operator=(const map_<T1, T2>& obj)
{
	if (this == &obj) return *this;
	this->~map_();
	copyNode(obj.root);
	return *this;
}

template<class T1, class T2>
inline map_<T1, T2>& map_<T1, T2>::operator=(map_<T1, T2>&& obj)
{
	swap(obj.root, this->root);
	swap(obj.size, this->size);
	return *this;
}



template<class T1, class T2>
inline map_<T1, T2>::~map_()
{
	deleteNodes(root);
	root = nullptr;
	size = 0;
}

template<class T1, class T2>
inline void map_<T1, T2>::deleteNodes(node<T1, T2>* nd)
{
	if (nd != nullptr) {
		deleteNodes(nd->left);
		deleteNodes(nd->right);
		delete nd;
		size--;
	}
}
