#include <iostream>

using namespace std;

class UnionClass {
    int parent[100];

    public: void Declare(int n) {
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
		}
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

void swap_values(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

int main() {
    int vertices_count;
    int vertices[100];
    int edges_count;
    int edges[100][3];

    cout << "Введіть кількість вершин (якщо хочете варіант за замовчуванням введіть 0): ";
    cin >> vertices_count;

    int vertices_copy_from[11] = {1,2,3,4,5,6,7,8,9,10,11};
    int edges_copy_from[17][3] = {
        {2,5,2},{5,8,4},{1,2,4},{2,7,1},{3,5,7}, {5,9,4},{6,8,4},{8,11,7},
        {1,3,3},{3,6,7}, {9,11,6},{1,4,1},{4,6,2},{6,10,5},{10,11,5}, {4,7,2},{7,10,3}
    };

    if (vertices_count == 0) {
        vertices_count = 11;
        edges_count = 17;
        for (int i = 0; i < vertices_count; ++i) {
            vertices[i] = vertices_copy_from[i];
        }
        for (int i = 0; i < edges_count; ++i) {
            edges[i][0] = edges_copy_from[i][0];
            edges[i][1] = edges_copy_from[i][1];
            edges[i][2] = edges_copy_from[i][2];
        }
    } 
    else {
        cout << "Введіть вершини: ";
        for (int i = 0; i < vertices_count; ++i) {
            cin >> vertices[i];
        }
        
        cout << "Введіть кількість ребер: ";
        cin >> edges_count;

        cout << "Введіть ребра (приклад: 1 2 5, де 1 2 - вершини, а 5 - вага):\n";
        for (int i = 0; i < edges_count; ++i) {
            cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        }
    }

    for (int i = 1; i < edges_count; ++i) {
        for (int j = i; j > 0; --j) {
            if (edges[j][2] < edges[j-1][2]) {
                for (int k = 0; k < 3; ++k) {
                    swap_values(edges[j][k], edges[j-1][k]);
                }
            } else {
                break;
            }
        }
    }

    // Алгоритм Краскала
    UnionClass union1;
	  union1.Declare(vertices_count);
    int spanning_tree[100][2];
    int spanning_tree_count = 0;
    int spanning_tree_length = 0;

    for (int i = 0; i < edges_count; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];

        if (union1.unite(u, v)) {
            spanning_tree[spanning_tree_count][0] = u;
            spanning_tree[spanning_tree_count][1] = v;
            spanning_tree_count++;
            spanning_tree_length += weight;
        }
    }

    // Виведення результату
    cout << "\nОстовне дерево: ";
    for (int i = 0; i < spanning_tree_count; i++) {
        cout << "(" << spanning_tree[i][0] << ", " << spanning_tree[i][1] << ") ";
    }
    cout << "\nДовжина = " << spanning_tree_length << endl;

    return 0;
}
