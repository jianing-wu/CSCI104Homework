class Node {
public:
	bool key;
	Node *left, *right, *parent;
};

class TFTree {
public:
	bool verify() const;
	void insert(bool key);
private:
	Node* root;
	// Helper
	bool verifyHelper(Node* root);
};

bool TFTree::verify(){
	if (root == NULL) {
		return true;
	}
	if (root->key) {
		return verifyHelper(root->right, true);
	} else {
		return verifyHelper(root->left, false);
	}
}

bool TFTree::verifyHelper(Node* root, bool isTrue) {
	if (root == NULL){
		return true;
	}

	if (root->key != isTrue) {
		return false;
	}

	return verifyHelper(root.left, isTrue) && verifyHelper(root.right, isTrue);
}
