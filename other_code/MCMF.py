from math import radians, cos, sin, asin, sqrt
from collections import deque

INF = 1e9
eps = 1e-6


class Edge:
    def __init__(self, u, v, w, c, edge_id):
        self.u = u
        self.v = v
        self.w = w
        self.c = c
        self.nxt = edge_id


class Graph:
    """
    Edge is save by Chain Forward Star.
    """
    def __init__(self, max_vec_number):
        self.N = int(max_vec_number)
        self.head = [-1 for i in range(self.N)]
        self.cnt = 0
        self.edge = []

    def __ad(self, u, v, w, c):
        self.edge.append(Edge(u, v, w, c, self.head[u]))
        self.head[u] = self.cnt
        self.cnt += 1

    def add(self, u, v, w, c):
        self.__ad(u, v, w, c)
        self.__ad(v, u, 0, -c)


class MCMF:
    def __init__(self, s, t, g):
        self.N = g.N
        self.s = s
        self.t = t
        self.graph = g
        self.vis = [0 for i in range(self.N)]
        self.inq = [0 for i in range(self.N)]
        self.max_flow = 0
        self.mini_cost = 0

    def spfa(self):
        d = [INF for i in range(self.N)]
        d[self.s] = self.inq[self.s] = 1
        q = deque()
        q.append(self.s)
        while len(q) > 0:
            u = q.popleft()
            self.inq[u] = 0
            edge_id = self.graph.head[u]
            while edge_id != -1:
                v = self.graph.edge[edge_id].v
                if (self.graph.edge[edge_id].w > 0 and
                        d[v] > d[u] + self.graph.edge[edge_id].c):
                    d[v] = d[u] + self.graph.edge[edge_id].c
                    if self.inq[v] == 0:
                        self.inq[v] = 1
                        q.append(v)
                edge_id = self.graph.edge[edge_id].nxt
        self.d = d
        # for e in self.graph.edge:
        # 	print(e.u, e.v, e.w, e.c, e.nxt)
        return d[self.t] < INF

    def dfs(self, u, w):
        self.vis[u] = 1
        if u == self.t:
            return w
        dlt = w
        edge_id = self.graph.head[u]
        while edge_id != -1:
            v = self.graph.edge[edge_id].v
            if (self.vis[v] == 0 and self.graph.edge[edge_id].w > 0 and abs(
                    self.d[u] + self.graph.edge[edge_id].c - self.d[v]) < eps):
                x = self.dfs(v, min(dlt, self.graph.edge[edge_id].w))
                self.graph.edge[edge_id].w -= x
                self.graph.edge[edge_id ^ 1].w += x
                # print(x, edge_id, self.graph.edge[edge_id].u, self.graph.edge[edge_id].v)
                self.mini_cost += x * self.graph.edge[edge_id].c
                dlt -= x
                if dlt == 0:
                    return w
            edge_id = self.graph.edge[edge_id].nxt
        # print(w - dlt)
        return w - dlt

    def main(self):
        while self.spfa() == 1:
            do_while = True
            while do_while:
                self.vis = [0 for i in range(self.N)]
                self.max_flow += self.dfs(s, INF)
                if self.vis[self.t] == 0:
                    do_while = False
        return self.mini_cost


