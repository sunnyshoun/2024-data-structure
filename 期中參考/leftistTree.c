#include <stdio.h>
#include <stdlib.h>

// 節點結構
typedef struct Node {
    int key;              // 儲存值
    int npl;              // 零路徑長度 (null path length)
    struct Node* left;    // 左子樹
    struct Node* right;   // 右子樹
} Node;

// 創建新節點
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->npl = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 合併兩棵左傾樹
Node* merge(Node* h1, Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    // 確保 h1 的根節點小於等於 h2
    if (h1->key > h2->key) {
        Node* temp = h1;
        h1 = h2;
        h2 = temp;
    }

    // 合併 h1 的右子樹和 h2
    h1->right = merge(h1->right, h2);

    // 維護左傾樹的性質
    if (!h1->left || h1->left->npl < h1->right->npl) {
        Node* temp = h1->left;
        h1->left = h1->right;
        h1->right = temp;
    }

    // 更新零路徑長度
    h1->npl = h1->right ? h1->right->npl + 1 : 0;

    return h1;
}

// 插入元素
Node* insert(Node* root, int key) {
    Node* newNode = createNode(key);
    return merge(root, newNode);
}

// 刪除最小值
Node* deleteMin(Node* root, int* minKey) {
    if (!root) return NULL;

    *minKey = root->key;
    Node* newRoot = merge(root->left, root->right);
    free(root);

    return newRoot;
}

// 中序遍歷
void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d(%d) ", root->key, root->npl);
        inorderTraversal(root->right);
    }
}

// 主程式
int main() {
    Node* root = NULL;

    // 插入數據
    root = insert(root, 20);
    root = insert(root, 12);
    root = insert(root, 18);
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 8);
    root = insert(root, 10);
    root = insert(root, 15);

    printf("中序遍歷: ");
    inorderTraversal(root);
    printf("\n");

    // 刪除最小值
    int minKey;
    root = deleteMin(root, &minKey);
    printf("刪除的最小值: %d\n", minKey);

    printf("中序遍歷: ");
    inorderTraversal(root);
    printf("\n");

    // 釋放資源
    while (root) {
        root = deleteMin(root, &minKey);
    }

    return 0;
}
