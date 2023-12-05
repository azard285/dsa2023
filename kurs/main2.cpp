#include <iostream>
#include <vector>

using namespace std;

struct SegmentTreeNode {
    int sum;

    SegmentTreeNode(int s) : sum(s) {}
};


void buildTree(int* array, SegmentTreeNode* tree, int node, int start, int end) {
    if (start == end) {
       tree[node] = SegmentTreeNode(array[start]);
    } else {
        int mid = (start + end) / 2;
        buildTree(array, tree, 2 * node + 1, start, mid);
        buildTree(array, tree, 2 * node + 2, mid + 1, end);
        tree[node] = SegmentTreeNode(tree[2 * node + 1].sum + tree[2 * node + 2].sum);
    }
}

void update(int index, int newValue, SegmentTreeNode* tree, int node, int start, int end) {
    if (start == end) {
        tree[node].sum = newValue;
    } else {
        int mid = (start + end) / 2;
        if (index <= mid) {
            update(index, newValue, tree, 2 * node + 1, start, mid);
        } else {
            update(index, newValue, tree, 2 * node + 2, mid + 1, end);
        }
        tree[node].sum = tree[2 * node + 1].sum + tree[2 * node + 2].sum;
    }
}

int query(int left, int right, const SegmentTreeNode* tree, int node, int start, int end) {
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && right >= end) {
        return tree[node].sum;
    }
    int mid = (start + end) / 2;
    int leftSum = query(left, right, tree, 2 * node + 1, start, mid);
    int rightSum = query(left, right, tree, 2 * node + 2, mid + 1, end);
    return leftSum + rightSum;
}
void Print(const SegmentTreeNode* tree, int node, int start, int end, int level = 0) {
    if (start == end) {
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << "[" << start << "] = " << tree[node].sum << endl;
    } else {
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << "[" << start << ", " << end << "] = " << tree[node].sum << endl;

        int mid = (start + end) / 2;
        Print(tree, 2 * node + 1, start, mid, level + 1);
        Print(tree, 2 * node + 2, mid + 1, end, level + 1);
    }
}

int main() {
    int array[] = {1, 3, 5, 7, 9, 11 };
    int n = sizeof(array) / sizeof(array[0]);
    SegmentTreeNode* tree;

    buildTree(array, tree, 0, 0, n - 1);

    cout << "Segment Tree:" << endl;
    Print(tree, 0, 0, n - 1);

     int sum = query(2, 5, tree, 0, 0, n - 1);
    cout << "Sum of elements in range [2, 5]: " << sum << endl;

    update(3, 10, tree, 0, 0, n - 1);

    sum = query(2, 5, tree, 0, 0, n - 1);
    cout << "Sum of elements in range [2, 5] after update: " << sum << endl;

    delete[] tree;

    return 0;
}
