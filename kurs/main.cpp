#include <iostream>
#include <vector>

using namespace std;

struct SegmentTreeNode {
    int sum;

    SegmentTreeNode(int s) : sum(s) {}
};

// Функция для построения сегментного дерева
void buildTree(int* array, SegmentTreeNode* tree, int node, int start, int end) {
    if (start == end) {
        // Если достигнут листовой узел, устанавливаем сумму равной значению из исходного массива
        tree[node] = SegmentTreeNode(array[start]);
    } else {
        // Иначе рекурсивно строим дерево для левой и правой половинок
        int mid = (start + end) / 2;
        buildTree(array, tree, 2 * node + 1, start, mid);
        buildTree(array, tree, 2 * node + 2, mid + 1, end);
        // Обновляем сумму текущего узла как сумму левого и правого поддеревьев
        tree[node] = SegmentTreeNode(tree[2 * node + 1].sum + tree[2 * node + 2].sum);
    }
}

// Функция для обновления значения в сегментном дереве
void update(int index, int newValue, SegmentTreeNode* tree, int node, int start, int end) {
    if (start == end) {
        // Если достигнут узел с обновляемым значением, обновляем его сумму
        tree[node].sum = newValue;
    } else {
        int mid = (start + end) / 2;
        if (index <= mid) {
            // Если обновляемый индекс находится в левом поддереве, рекурсивно вызываем функцию для левого поддерева
            update(index, newValue, tree, 2 * node + 1, start, mid);
        } else {
            // Иначе обновляемый индекс находится в правом поддереве, рекурсивно вызываем функцию для правого поддерева
            update(index, newValue, tree, 2 * node + 2, mid + 1, end);
        }
        // Обновляем сумму текущего узла как сумму левого и правого поддеревьев
        tree[node].sum = tree[2 * node + 1].sum + tree[2 * node + 2].sum;
    }
}

// Функция для запроса суммы в заданном диапазоне
int query(int left, int right, const SegmentTreeNode* tree, int node, int start, int end) {
    if (left > end || right < start) {
        // Если заданный диапазон полностью не пересекается с текущим узлом, возвращаем 0
        return 0;
    }
    if (left <= start && right >= end) {
        // Если заданный диапазон полностью содержит текущий узел, возвращаем его сумму
        return tree[node].sum;
    }
    // Иначе рекурсивно вызываем функцию для левого и правого поддеревьев
    int mid = (start + end) / 2;
    int leftSum = query(left, right, tree, 2 * node + 1, start, mid);
    int rightSum = query(left, right, tree, 2 * node + 2, mid + 1, end);
    // Возвращаем сумму левого и правого поддеревьев
    return leftSum + rightSum;
}
// Функция для печати сегментного дерева
void Print(const SegmentTreeNode* tree, int node, int start, int end, int level = 0) {
    if (start == end) {
        // Выводим узел-лист
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << "[" << start << "] = " << tree[node].sum << endl;
    } else {
        // Выводим узел суммы и рекурсивно печатаем его дочерние узлы
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
    // Создаем массив для хранения сегментного дерева с запасом в 4 раза больше размера исходного массива
    SegmentTreeNode* tree;

    // Построение сегментного дерева на основе исходного массива
    buildTree(array, tree, 0, 0, n - 1);

    // Печать сегментного дерева
    cout << "Segment Tree:" << endl;
    Print(tree, 0, 0, n - 1);

    // Запрос суммы элементов в диапазоне [2, 5]
    int sum = query(2, 5, tree, 0, 0, n - 1);
    cout << "Sum of elements in range [2, 5]: " << sum << endl;

    // Обновление значения элемента с индексом 3 на 10
    update(3, 10, tree, 0, 0, n - 1);

    // Повторный запрос суммы элементов в диапазоне [2, 5] после обновления
    sum = query(2, 5, tree, 0, 0, n - 1);
    cout << "Sum of elements in range [2, 5] after update: " << sum << endl;

    // Освобождение памяти, выделенной для сегментного дерева
    delete[] tree;

    return 0;
}