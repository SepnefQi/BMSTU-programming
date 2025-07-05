import java.util.*;

public class EqDist {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();

        List<List<Integer>> edges = new ArrayList<>();
        for (int i=0; i<n; i++) {
            edges.add(new ArrayList<>());
        }

        for (int i=0; i<m; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            edges.get(u).add(v);
            edges.get(v).add(u);
        }

        int k = scanner.nextInt();
        int[] support = new int[k];
        for (int i=0; i<k; i++) {
            support[i] = scanner.nextInt();
        }

        List<Integer> res = myfind(edges, support, n);

        if (res.isEmpty()) {
            System.out.print("-");
        } else {
            Collections.sort(res);
            for (int vert : res) {
                System.out.print(vert+" ");
            }
        }
    }

    public static List<Integer> myfind(List<List<Integer>> edges, int[] support, int n) {
        List<Integer> wasFind = new ArrayList<>();

        int[][] alldist = new int[n][support.length];
        for (int j = 0; j < support.length; j++) {
            int supp = support[j];
            int[] distFromSupport = bfs(edges, supp, n);
            for (int i = 0; i < n; i++) {
               alldist[i][j] = distFromSupport[i];
            }
        }

        for (int i = 0; i < n; i++) {
            if (isEqually(alldist, i, support.length)) {
                wasFind.add(i);
            }
        }

        return wasFind;
    }

    public static boolean isEqually(int[][] alldist, int i, int n) {
        if (n == 0) {
            return true;
        }

        int dist = -1;

        for (int j=0; j<n; j++) {
            int distance = alldist[i][j];
            if (distance==-1) { // если вершины достичь невозможно
                return false;
            }

            if (dist==-1) {
                dist = distance;
            } else if (dist!=distance) {
                return false;
            }
        }

        return true;
    }
    
    public static int[] bfs(List<List<Integer>> edges, int start, int n) {
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);

        int[] distances = new int[n];
        Arrays.fill(distances, -1);
        distances[start] = 0;

        while(!queue.isEmpty()) {
            int curr = queue.poll();

            for (int neighbor : edges.get(curr)) {
                if (distances[neighbor]==-1) {
                    distances[neighbor] = distances[curr] + 1;
                    queue.offer(neighbor);
                }
            }
        }
        return distances; 
    }
}