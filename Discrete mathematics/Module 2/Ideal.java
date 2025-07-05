import java.util.*;

public class Ideal{

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();

        List<List<Edge>> adj = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            adj.add(new ArrayList<>());
        }

        for (int i = 0; i < m; i++) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            int c = scanner.nextInt();
            adj.get(a).add(new Edge(b, c));
            adj.get(b).add(new Edge(a, c));
        }

        Queue<State> queue = new LinkedList<>();
        queue.offer(new State(1, new ArrayList<>()));

        int[] dist = new int[n + 1];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[1] = 0;

        List<Integer> bestPath = null;

        while (!queue.isEmpty()) {
            State currentState = queue.poll();
            int u = currentState.node;
            List<Integer> path = currentState.path;

            if (u == n) {
                if (bestPath == null || path.size() < bestPath.size() ||
                        (path.size() == bestPath.size() && comparePaths(path, bestPath) < 0)) {
                    bestPath = new ArrayList<>(path);
                }
                continue;
            }

            if (path.size() > dist[u]) continue;
            
            for (Edge edge : adj.get(u)) {
                int v = edge.neighbor;
                int color = edge.color;

                List<Integer> newPath = new ArrayList<>(path);
                newPath.add(color);

                if (dist[v] >= newPath.size()) {
                    dist[v] = newPath.size();
                    queue.offer(new State(v, newPath));
                }
            }
        }

        System.out.println(bestPath.size());
        for (int color : bestPath) {
            System.out.print(color + " ");
        }
        System.out.println();
    }

    static class Edge {
        int neighbor;
        int color;

        public Edge(int neighbor, int color) {
            this.neighbor = neighbor;
            this.color = color;
        }
    }

    static class State {
        int node;
        List<Integer> path;

        public State(int node, List<Integer> path) {
            this.node = node;
            this.path = path;
        }
    }

    static int comparePaths(List<Integer> path1, List<Integer> path2) {
        for (int i = 0; i < Math.min(path1.size(), path2.size()); i++) {
            int cmp = Integer.compare(path1.get(i), path2.get(i));
            if (cmp != 0) {
                return cmp;
            }
        }
        return Integer.compare(path1.size(), path2.size());
    }
}