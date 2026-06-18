#include <iostream>
using namespace std;

// Binary Search Tree Node structure
struct TreeNode {
    int fileID;                       // Stores the file ID
    TreeNode* left;                   // Pointer to left child
    TreeNode* right;                  // Pointer to right child
    TreeNode(int id) : fileID(id), left(nullptr), right(nullptr) {}  // Constructor
};

class FileSystem {
private:
    TreeNode* root;                   // Root of BST

    // Helper function to insert a file ID into BST
    TreeNode* insert(TreeNode* node, int id) {
        if (node == nullptr) {        // Found empty spot
            return new TreeNode(id);  // Create new node
        }

        if (id < node->fileID) {     // Go to left subtree
            node->left = insert(node->left, id);
        } else if (id > node->fileID) {  // Go to right subtree
            node->right = insert(node->right, id);
        }
        return node;                  // Return unchanged node
    }

    // Helper function to find minimum value node in subtree
    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) {  // Keep going left
            node = node->left;
        }
        return node;                  // Return leftmost node
    }

    // Helper function to delete a file ID from BST
    TreeNode* remove(TreeNode* node, int id) {
        if (node == nullptr) return node;  // ID not found

        if (id < node->fileID) {     // Search left subtree
            node->left = remove(node->left, id);
        } else if (id > node->fileID) {  // Search right subtree
            node->right = remove(node->right, id);
        } else {                     // Found node to delete
            // Case 1: No child or one child
            if (node->left == nullptr) {
                TreeNode* temp = node->right;  // Right child or nullptr
                delete node;            // Delete current node
                return temp;           // Return right child
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;   // Left child
                delete node;            // Delete current node
                return temp;           // Return left child
            }

            // Case 2: Two children
            TreeNode* temp = findMin(node->right);  // Find successor
            node->fileID = temp->fileID;  // Copy successor's ID
            node->right = remove(node->right, temp->fileID);  // Delete successor
        }
        return node;                  // Return updated node
    }

    // Helper function to search for file ID in BST
    bool search(TreeNode* node, int id) {
        if (node == nullptr) return false;  // Not found
        if (node->fileID == id) return true;  // Found

        // Search left or right subtree
        return id < node->fileID ? search(node->left, id) : search(node->right, id);
    }

    // Helper function for in-order traversal (left, root, right)
    void inOrder(TreeNode* node) {
        if (node == nullptr) return;  // Base case
        inOrder(node->left);          // Visit left subtree
        cout << node->fileID << " ";  // Print current node
        inOrder(node->right);         // Visit right subtree
    }

public:
    FileSystem() : root(nullptr) {}   // Initialize empty BST

    // Public insert function
    void insert(int id) {
        root = insert(root, id);     // Call recursive insert
        cout << "Inserted file " << id << "\n";
    }

    // Public delete function
    void remove(int id) {
        if (!search(root, id)) {      // Check if file exists
            cout << "File " << id << " not found\n";
            return;
        }
        root = remove(root, id);      // Call recursive remove
        cout << "Deleted file " << id << "\n";
    }

    // Public search function
    void search(int id) {
        cout << "File " << id << (search(root, id) ? " found\n" : " not found\n");
    }

    // Public display function (in-order traversal)
    void display() {
        cout << "Files (in-order): ";
        inOrder(root);               // Call recursive in-order
        cout << "\n";
    }
};

int main() {
    cout << "=== Digital Library File System ===\n\n";
    FileSystem fs;

    // Insert files to build BST
    fs.insert(50);                   // Root
    fs.insert(30);                   // Left of root
    fs.insert(70);                   // Right of root
    fs.insert(20);                   // Left of 30
    fs.insert(40);                   // Right of 30
    fs.insert(60);                   // Left of 70
    fs.insert(80);                   // Right of 70
    fs.display();                    // Show initial BST

    // Demonstrate all deletion cases
    cout << "\n--- Deletion Tests ---\n";

    // Case 1: Delete leaf node (20)
    cout << "\nCase 1: Delete leaf node (20)\n";
    fs.remove(20);                   // Leaf node deletion
    fs.display();                    // Show updated BST

    // Case 2: Delete node with one child (70)
    cout << "\nCase 2: Delete node with one child (70)\n";
    fs.remove(70);                   // Node with one child
    fs.display();                    // Show updated BST

    // Case 3: Delete node with two children (30)
    cout << "\nCase 3: Delete node with two children (30)\n";
    fs.remove(30);                   // Node with two children
    fs.display();                    // Show updated BST

    // Verify searches
    cout << "\n--- Search Tests ---\n";
    fs.search(40);                   // Existing file
    fs.search(99);                   // Non-existent file

    return 0;
}
