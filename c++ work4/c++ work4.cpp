#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

// 節點結構用於二元搜尋樹
struct BSTNode {
    int value;  // 節點的值
    BSTNode* left;  // 左子節點
    BSTNode* right; // 右子節點
    BSTNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// 將值插入二元搜尋樹
BSTNode* insertBST(BSTNode* root, int value) {
    if (!root) return new BSTNode(value); // 如果樹是空的，創建新節點
    if (value < root->value)
        root->left = insertBST(root->left, value); // 插入左子樹
    else
        root->right = insertBST(root->right, value); // 插入右子樹
    return root;
}

// 調整堆積結構以滿足最大堆積的特性
void heapify(vector<int>& heap, int n, int i) {
    int largest = i; // 初始化最大值為父節點
    int left = 2 * i + 1; // 左子節點索引
    int right = 2 * i + 2; // 右子節點索引

    // 如果左子節點比父節點大，更新最大值索引
    if (left < n && heap[left] > heap[largest])
        largest = left;
    // 如果右子節點比當前最大值大，更新最大值索引
    if (right < n && heap[right] > heap[largest])
        largest = right;
    // 如果最大值索引不是父節點，進行交換並遞迴調整
    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapify(heap, n, largest);
    }
}

// 建立最大堆積
void buildMaxHeap(vector<int>& heap) {
    // 從最後一個非葉節點開始調整
    for (int i = heap.size() / 2 - 1; i >= 0; --i)
        heapify(heap, heap.size(), i);
}

// 打印二元搜尋樹的樹狀結構
void printBST(BSTNode* root, int space = 0, int indent = 4) {
    if (!root) return;
    space += indent; // 增加縮進
    printBST(root->right, space); // 打印右子樹
    cout << setw(space) << root->value << "\n"; // 打印當前節點
    printBST(root->left, space); // 打印左子樹
}

// 打印陣列
void printArray(const vector<int>& arr) {
    for (int val : arr) cout << val << " ";
    cout << endl;
}

// 主函數
int main() {
    vector<int> values; // 存儲使用者輸入的數值
    int input;

    cout << "Enter integers (type 'q' to quit): " << endl;
    // 讀取使用者輸入，直到輸入非數字為止
    while (cin >> input) {
        values.push_back(input);
    }
    cin.clear(); // 清除輸入錯誤狀態
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩餘輸入

    // 建立二元搜尋樹
    BSTNode* bstRoot = nullptr;
    for (int val : values) {
        bstRoot = insertBST(bstRoot, val);
    }

    // 建立最大堆積
    vector<int> maxHeap = values;
    buildMaxHeap(maxHeap);

    // 輸出結果
    cout << "\nBST (Tree Representation):" << endl;
    printBST(bstRoot); // 打印二元搜尋樹

    cout << "\nMax-Heap (Array Representation):" << endl;
    printArray(maxHeap); // 打印最大堆積的陣列表示

    return 0;
}
