#include <cstdio>
#include <map>
#include <vector>

using namespace std;

struct Node
{
    int address;
    int data;
    int next;
};

int main()
{
    int first_address, n, k;
    scanf("%d %d %d", &first_address, &n, &k);

    map<int, Node> nodes;
    vector<Node> valid_nodes;

    for (int i = 0; i < n; ++i) {
        Node node;
        scanf("%d %d %d", &node.address, &node.data, &node.next);

        nodes[node.address] = node;
    }

    for (auto n = nodes[first_address]; ; n = nodes[n.next]) {
        valid_nodes.push_back(n);
        if (n.next == -1) {break;}
    }

    auto end = valid_nodes.size();
    
    for (int i = 0; i + k - 1 < end; i += k) {
        Node temp;
        for (int j = 0; j < k / 2; ++j) {
            temp = valid_nodes[i+j];
            valid_nodes[i+j] = valid_nodes[i+k-1-j];
            valid_nodes[i+k-1-j] = temp;
        }
    }

    for (int i = 0; i < end - 1; ++i) {
        valid_nodes[i].next = valid_nodes[i+1].address;
    }
    valid_nodes[end-1].next = -1;
    
    for (const auto node : valid_nodes) {
        printf("%05d %d ", node.address, node.data);
        printf(node.next == -1 ? "%d\n" : "%05d\n", node.next);
    }

    return 0;
}
