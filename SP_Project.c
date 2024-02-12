/*
Student ID: 220234
name : Bijoy Kumar Paul
project :Traversing a graph . finding all the path formed by given nodes.
*/


#include <stdio.h>



int flag[100000] = {0};
int pp = 0;

// Structure to represent a graph node
struct Node
{
    int nodeId;
    int adjCount;
    int adjs[10];
    int costs[10];
};

// Function to add a node to the graph
int addNode(struct Node *p, int nodeID, int count)
{
    int i = 0;
    int nodeCount = count;

    for (i = 0; i < count; i++)
    {
        if (p[i].nodeId == nodeID)
        {
            break;
        }
    }

    if (i == count)
    {
        p[i].nodeId = nodeID;
        p[i].adjCount = 0;
        nodeCount++;
    }

    return nodeCount;
}

// Function to add an adjacent node to a given node
void addAdjacent(struct Node *p, int nodeID1, int nodeID2, int cost, int count)
{
    int i = 0;
    int index;
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeId == nodeID1)
        {
            int c = p[i].adjCount;

            p[i].adjs[c] = nodeID2;
            p[i].costs[c] = cost;
            p[i].adjCount = c + 1;

            break;
        }
    }
}

// Function to check if a node is already in the list
int added(int *list, int list_node_count, int nodeID)
{
    int i = 0;


    for (i = 0; i < list_node_count; i++)
    {
        if (list[i] == nodeID)
        {
            return 1;
        }
    }

    return 0;
}

void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int list_node_count)
{
    int index = 0;


    if (list[list_node_count - 1] == end)
    {
        int totalCost = 0;
        int x = 1;

        // Check if all nodes in the path have the required visa
        for (int i = 0; i < list_node_count; i++)
        {
            if (flag[list[i]] == 0)
            {
                x = 0;
                break;
            }
        }


        if (x == 1)
        {
            printf("\n");

            for (int i = 0; i < list_node_count; i++)
            {
                printf(" %d ", list[i]);
                totalCost += clist[i];
            }

            pp++;
            printf(" cost = %d", totalCost);
        }

        return;
    }

    // Find the index of the starting node
    for (int i = 0; i < count; i++)
    {
        if (p[i].nodeId == start)
        {
            index = i;
            break;
        }
    }


    for (int i = 0; i < p[index].adjCount; i++)
    {
        int a = added(list, list_node_count, p[index].adjs[i]);


        if (a == 0)
        {
            list[list_node_count] = p[index].adjs[i];
            clist[list_node_count] = p[index].costs[i];
            list_node_count++;

            findpath(p, count, p[index].adjs[i], end, list, clist, list_node_count);
            list_node_count--;
        }
    }
}

int main()
{
    struct Node nodes[50];
    int nodeCount = 0;
    int n1 = 0;
    int n2 = 0;
    int c = 0;


    while (1)
    {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        // Terminate taking input
        if (n1 == -1 || n2 == -1 || c == -1)
        {
            break;
        }

        nodeCount = addNode(&nodes[0], n1, nodeCount);
        nodeCount = addNode(&nodes[0], n2, nodeCount);
        addAdjacent(&nodes[0], n1, n2, c, nodeCount);
        addAdjacent(&nodes[0], n2, n1, c, nodeCount);
    }

    // Input start and end nodes
    int start, end;
    printf("start, end ? ");
    scanf("%d %d", &start, &end);
    flag[start]++;

    // Input list of visa nodes
    int visa[50] = {0}; // Initializing array
    printf("List of visa: ");

    for (int i = 0; i < 50; i++)
    {
        scanf("%d", &visa[i]);

        if (visa[i] == -9)
        {
            break;
        }

        flag[visa[i]]++;
    }


    int NoNeedVisa[50] = {0}; // Initializing array
    printf("Enter the Node which do not need visa: ");

    for (int i = 0; i < 50; i++)
    {
        scanf("%d", &NoNeedVisa[i]);

        if (NoNeedVisa[i] == -9)
        {
            break;
        }

        flag[NoNeedVisa[i]]++;
    }


    int list[50] = {0};
    int clist[50] = {0};
    int list_node_count = 0;
    list[0] = start;
    clist[0] = 0;
    list_node_count = 1;

    // Find and print paths
    findpath(nodes, nodeCount, start, end, list, clist, list_node_count);

    // If no valid paths are found
    if (pp == 0)
    {
        printf("No path found");
    }

    return 0;
}
