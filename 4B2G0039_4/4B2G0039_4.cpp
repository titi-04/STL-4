// 4B2G0039_4.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// Binary Search Tree (BST) 節點定義
class BSTNode {
public:
    int val;        // 節點的值
    BSTNode* left;  // 左子節點
    BSTNode* right; // 右子節點
    // 節點構造函數，初始化節點值，並將左、右子節點設為 nullptr
    BSTNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// Binary Search Tree (BST) 類別
class BinarySearchTree {
public:
    BSTNode* root;  // 樹的根節點

    // 構造函數，初始化 BST 根節點為 nullptr
    BinarySearchTree() : root(nullptr) {}

    // 插入節點
    // 這是遞迴函數，根據 BST 的特性，插入節點至適當位置
    BSTNode* insert(BSTNode* node, int value) {
        if (node == nullptr) {
            return new BSTNode(value);  // 如果節點為 nullptr 則創建新節點
        }
        if (value < node->val) {   // 如果值小於當前節點的值，插入左子樹
            node->left = insert(node->left, value);
        }
        else {                   // 否則插入右子樹
            node->right = insert(node->right, value);
        }
        return node;
    }

    // 中序遍歷 (Inorder Traversal)
    // 將遍歷的結果存入 vector 中
    void inorder(BSTNode* node, vector<int>& result) {
        if (node == nullptr) return;  // 如果節點為 nullptr，直接返回
        inorder(node->left, result);   // 遞迴遍歷左子樹
        result.push_back(node->val);   // 訪問當前節點
        inorder(node->right, result);  // 遞迴遍歷右子樹
    }

    // 建立 BST，從一個整數陣列中插入每個值
    void build(const vector<int>& values) {
        for (int value : values) {
            root = insert(root, value);  // 依次插入每個值到 BST 中
        }
    }

    // 印出 BST 中序遍歷結果
    void print_inorder() {
        vector<int> result;
        inorder(root, result);  // 中序遍歷 BST
        cout << "BST 中序遍歷結果 (陣列): ";
        for (int val : result) {
            cout << val << " ";   // 輸出遍歷結果
        }
        cout << endl;
    }

    // 樹狀圖方式印出 Binary Search Tree
    void print_tree() {
        int height = getHeight(root);  // 計算樹的高度
        printLevelOrder(root, height); // 層次遍歷打印樹
    }

    // 計算樹的高度
    // 返回樹的最大深度
    int getHeight(BSTNode* node) {
        if (node == nullptr) return 0;  // 如果節點為 nullptr，高度為 0
        return max(getHeight(node->left), getHeight(node->right)) + 1; // 取左右子樹的最大高度 + 1
    }

    // 根據高度打印每層
    void printLevelOrder(BSTNode* node, int height) {
        for (int i = 1; i <= height; i++) {
            printCurrentLevel(node, i, height);  // 打印每一層的節點
            cout << endl;
        }
    }


    // 打印當前層的節點，適當縮排
    void printCurrentLevel(BSTNode* node, int level, int height) {
        if (node == nullptr) {
            printSpaces(height - level); // 如果節點為 nullptr，打印空格來對齊
            return;
        }
        if (level == 1) {
            cout << node->val;           // 如果是當前層的節點，打印節點值
            printSpaces(1);              // 打印空格來對齊
        }
        else {
            printCurrentLevel(node->left, level - 1, height);  // 遞迴打印左子樹
            printCurrentLevel(node->right, level - 1, height); // 遞迴打印右子樹
        }
    }

    // 打印空格來對齊
    void printSpaces(int count) {
        for (int i = 0; i < count; i++) {
            cout << " ";
        }
    }
};

// Max-Heap 類別
class MaxHeap {
public:
    vector<int> heap; // 用一個陣列來儲存堆積結構

    // 調整堆積結構 (heapify)
    // 保證堆積結構符合最大堆的特性
    void heapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;  // 左子節點索引
        int right = 2 * i + 2; // 右子節點索引

        if (left < n && heap[left] > heap[largest]) {  // 如果左子節點比當前節點大，更新 largest
            largest = left;
        }
        if (right < n && heap[right] > heap[largest]) { // 如果右子節點比 largest 更大，更新 largest
            largest = right;
        }

        if (largest != i) {  // 如果 largest 不是當前節點，交換並繼續調整
            swap(heap[i], heap[largest]);
            heapify(n, largest);  // 遞迴調整
        }
    }

    // 建立 Max-Heap
    // 將陣列中的元素轉換成 Max-Heap
    void build_heap(vector<int>& values) {
        heap = values;  // 將給定的值複製到 heap 中
        int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; i--) {  // 從最後一個非葉子節點開始調整堆積結構
            heapify(n, i);
        }
    }

    // 印出 Max-Heap (陣列表示)
    void print_heap() {
        cout << "Max-Heap (陣列表示): ";
        for (int val : heap) {
            cout << val << " ";  // 輸出 Max-Heap 的陣列表示
        }
        cout << endl;
    }

    // 樹狀圖方式印出 Max-Heap
    void print_tree() {
        int n = heap.size();
        int height = (int)log2(n) + 1;  // 計算 Max-Heap 樹的高度
        for (int i = 1; i <= height; i++) {
            int levelStart = (1 << (i - 1)) - 1; // 每一層的起始索引
            int levelEnd = min((1 << i) - 2, n - 1); // 每一層的結束索引
            for (int j = levelStart; j <= levelEnd; j++) {
                cout << heap[j] << " ";  // 打印每層的節點
            }
            cout << endl;
        }
    }
};

int main() {
    vector<int> values; // 儲存用戶輸入的數值
    int num;

    cout << "請輸入一組整數，用空格分開 (輸入 0 結束): ";
    while (cin >> num && num != 0) {
        values.push_back(num);  // 讀取數字直到輸入 0
    }

    // 建立 Binary Search Tree
    BinarySearchTree bst;
    bst.build(values);      // 使用用戶輸入的數字建立 BST
    bst.print_inorder();    // 打印中序遍歷結果
    cout << "BST 樹狀圖顯示:\n";
    bst.print_tree();       // 打印樹狀圖

    // 建立 Max-Heap
    MaxHeap maxHeap;
    maxHeap.build_heap(values);  // 使用用戶輸入的數字建立 Max-Heap
    maxHeap.print_heap();        // 打印 Max-Heap 的陣列表示
    cout << "Max-Heap 樹狀圖顯示:\n";
    maxHeap.print_tree();        // 打印 Max-Heap 的樹狀圖

    return 0;
}


// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
