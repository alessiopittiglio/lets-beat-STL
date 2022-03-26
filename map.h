#pragma once

template<class T>
class node {
private:
	int _key;
	T _elem;
public:
	node* _left;
	node* _right;
	int _height;

	node(int key, T elem);

	int key() { return _key; }
	void setKey(int key) { _key = key; }
};

template<class T>
class map {
private:
	node<T>* _root;
	unsigned int _size;

	node<T>* insert(node<T>*& root, int key, T elem);
	node<T>* find(node<T>* root, int key);
	node<T>* erase(node<T>*& root, int key);
	node<T>* rotateLeft(node<T>* root);
	node<T>* rotateRight(node<T>* root);

	int height(node<T>* root);
	void inorderTraversal(node<T>* root);

	node<T>* minValueNode(node<T>* node);
	int getBalance(node<T>* n);
public:
	map();

	void insert(int key, T elem);
	bool find(int key);
	void erase(int key);
	void inorderTraversal();
};

template<class T>
node<T>::node(int key, T elem) {
	_key = key;
	_left = nullptr;
	_right = nullptr;
	_height = 0;
	_elem = elem;
}

template<class T>
map<T>::map() {
	_root = nullptr;
	_size = 0;
}

template<class T>
void map<T>::insert(int key, T elem) {
	_root = insert(_root, key, elem);
}

template<class T>
node<T>* map<T>::insert(node<T>*& root, int key, T elem) {
	if (!root) {
		node<T>* temp = new node<T>(key, elem);
		return temp;
	}
	else if (key < root->key()) {
		root->_left = insert(root->_left, key, elem);
		if (height(root->_left) - height(root->_right) == 2) {
			if (key > root->_left->key())
				root->_left = rotateLeft(root->_left);
			root = rotateRight(root);
		}
	}
	else if (key > root->key()) {
		root->_right = insert(root->_right, key, elem);
		if (height(root->_right) - height(root->_left) == 2) {
			if (key < root->_right->key())
				root->_right = rotateRight(root->_right);
			root = rotateLeft(root);
		}
	}
	root->_height = 1 + std::max(height(root->_right), height(root->_left));
	return root;
}

template<class T>
node<T>* map<T>::rotateLeft(node<T>* root) {
	node<T>* temp = root->_right;
	root->_right = temp->_left;
	temp->_left = root;
	root->_height = 1 + std::max(height(root->_left), height(root->_right));
	temp->_height = 1 + std::max(height(temp->_left), height(temp->_right));
	return temp;
}

template<class T>
node<T>* map<T>::rotateRight(node<T>* root) {
	node<T>* temp = root->_left;
	root->_left = temp->_right;
	temp->_right = root;
	root->_height = 1 + std::max(height(root->_left), height(root->_right));
	temp->_height = 1 + std::max(height(temp->_left), height(temp->_right));
	return temp;
}

template<class T>
int map<T>::height(node<T>* root) {
	if (root == nullptr)
		return -1;
	else
		return root->_height;
}

template<class T>
bool map<T>::find(int key) {
	if (find(_root, key))
		return true;
	else
		return false;
}

template<class T>
node<T>* map<T>::find(node<T>* root, int key) {
	if (root)
		if (key == root->key())
			return root;
		else if (key > root->key())
			return find(root->_right, key);
		else
			return find(root->_left, key);
	else
		return nullptr;
}

template<class T>
node<T>* map<T>::minValueNode(node<T>* n) {
	node<T>* current = n;
	while (current->_left != nullptr)
		current = current->_left;
	return current;
}

template<class T>
int map<T>::getBalance(node<T>* n) {
	if (n == nullptr)
		return 0;
	return height(n->_left) - height(n->_right);
}


template<class T>
void map<T>::erase(int key) {
	erase(_root, key);
}

template<class T>
node<T>* map<T>::erase(node<T>*& root, int key) {
	if (root == nullptr)
		return root;

	if (key < root->key())
		root->_left = erase(root->_left, key);
	else if (key > root->key())
		root->_right = erase(root->_right, key);
	else {
		if (root->_left == nullptr || root->_right == nullptr) {

			node<T>* temp = root->_left ? root->_left : root->_right;

			if (temp == nullptr) {
				temp = root;
				root = nullptr;
			}
			else
				*root = *temp;
			free(temp);
		}
		else {
			node<T>* temp = minValueNode(root->_right);
			root->setKey(temp->key());
			root->_right = erase(root->_right, temp->key());
		}
	}
	if (root == nullptr)
		return root;

	root->_height = 1 + std::max(height(root->_left), height(root->_right));

	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->_left) >= 0)
		return rotateRight(root);

	if (balance > 1 && getBalance(root->_left) < 0) {
		root->_left = rotateLeft(root->_left);
		return rotateRight(root);
	}

	if (balance < -1 && getBalance(root->_right) <= 0)
		return rotateLeft(root);

	if (balance < -1 && getBalance(root->_right) > 0) {
		root->_right = rotateRight(root->_right);
		return rotateLeft(root);
	}

	return root;
}

template<class T>
void map<T>::inorderTraversal() {
	inorderTraversal(_root);
}

template<class T>
void map<T>::inorderTraversal(node<T>* root) {
	if (root == nullptr)
		return;
	inorderTraversal(root->_left);
	printf("%u ", root->key());
	inorderTraversal(root->_right);
}
