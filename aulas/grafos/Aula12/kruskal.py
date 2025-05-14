class Edge:
    def __init__(self, u, v, weight):
        self.u = u
        self.v = v
        self.weight = weight

def kruskal(nVertex, nEdges, graph):
    graph.sort(key=lambda edge: edge.weight)

    roots = []
    ranks = []

    for i in range(nVertex):
        roots.append(i)
        ranks.append(0)
    minCost = 0

    for i in range(nEdges):
        root1 = find_root(roots, graph[i].u)
        root2 = find_root(roots, graph[i].v)
        if root1 != root2:
            minCost = minCost + graph[i].weight
            print(f"Edge {graph[i].u} -- {graph[i].v} weight {graph[i].weight}")
            union_sets(root2, root1, roots, ranks)
    print(f"Cost = {minCost}")

def find_root(roots, x):
    while roots[x] != x:
        roots[x] = roots[roots[x]]
        x = roots[x]
    return x

def union_sets(v1, v2, roots, ranks):
    if ranks[v1] < ranks[v2]:
        roots[v1] = v2
    elif ranks[v1] > ranks[v2]:
        roots[v2] = v1
    else:
        roots[v2] = v1
        ranks[v1] += 1

nVertex = 9
graph = [ Edge(0, 1, 4), Edge(0, 7, 8), Edge(1, 7, 11), Edge(1, 2, 8), Edge(2, 3, 7), Edge(2, 5, 4), Edge(2, 8, 2), Edge(3, 4, 9), Edge(3, 5, 14),  Edge(5, 6, 2), Edge(6, 7, 1), Edge(6, 8, 6)]

kruskal(nVertex, len(graph), graph)