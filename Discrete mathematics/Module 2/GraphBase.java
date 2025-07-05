import java.util.*;

public class GraphBase {
    static int n, m;
    static List<List<Integer>> adj, adjRev, condensedAdj, scc;
    static boolean[] visited;
    static Stack<Integer> stack;
    static int[] component, inDegree;
    static List<Integer> base;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();

        adj = new ArrayList<>();
        adjRev = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
            adjRev.add(new ArrayList<>());
        }

        for (int i = 0; i < m; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            adj.get(u).add(v);
            adjRev.get(v).add(u);
        }

        findSCC();
        buildCondensedGraph();
        findBase();

        Collections.sort(base);
        for (int vertex : base) {
            System.out.print(vertex + " ");
        }
    }

    static void findSCC() {
        visited = new boolean[n];
        stack = new Stack<>();
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs1(i);
            }
        }

        scc = new ArrayList<>();
        component = new int[n];
        Arrays.fill(component, -1);
        visited = new boolean[n];
        int sccCount = 0;
        while (!stack.isEmpty()) {
            int u = stack.pop();
            if (!visited[u]) {
                List<Integer> currentSCC = new ArrayList<>();
                dfs2(u, currentSCC, sccCount);
                scc.add(currentSCC);
                sccCount++;
            }
        }
    }

    static void dfs1(int u) {
        visited[u] = true;
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                dfs1(v);
            }
        }
        stack.push(u);
    }

    static void dfs2(int u, List<Integer> currentSCC, int sccId) {
        visited[u] = true;
        component[u] = sccId;
        currentSCC.add(u);
        for (int v : adjRev.get(u)) {
            if (!visited[v]) {
                dfs2(v, currentSCC, sccId);
            }
        }
    }

    static void buildCondensedGraph() {
        condensedAdj = new ArrayList<>();
        for (int i = 0; i < scc.size(); i++) {
            condensedAdj.add(new ArrayList<>());
        }

        inDegree = new int[scc.size()];
        Arrays.fill(inDegree, 0);

        for (int u = 0; u < n; u++) {
            for (int v : adj.get(u)) {
                if (component[u] != component[v]) {
                    condensedAdj.get(component[u]).add(component[v]);
                    inDegree[component[v]]++;
                }
            }
        }
    }

    static void findBase() {
        base = new ArrayList<>();
        for (int i = 0; i < scc.size(); i++) {
            if (inDegree[i] == 0) {
                int minVertex = Integer.MAX_VALUE;
                for (int vertex : scc.get(i)) {
                    minVertex = Math.min(minVertex, vertex);
                }
                base.add(minVertex);
            }
        }
    }
}