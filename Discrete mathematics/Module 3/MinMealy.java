import java.io.*;
import java.util.*;

public class MinMealy {

    static class Status {
        int i;
        Status parent;
        int depth;
        Status pi;
        boolean was;
        List<Status> delt;

        Status() {
            delt = new ArrayList<>();
        }
    }

    static Status find(Status x) {
        Status root;
        if (x.parent == x) {
            root = x;
        } else {
            x.parent = find(x.parent);
            root = x.parent;
        }
        return root;
    }

    static void unionFunc(Status u, Status v) {
        Status rootU = find(u);
        Status rootV = find(v);
        if (rootU.depth < rootV.depth) {
            rootU.parent = rootV;
        } else {
            rootV.parent = rootU;
            if (rootU.depth == rootV.depth && rootU != rootV) {
                rootU.depth++;
            }
        }
    }

    static int split1(int n, int m, List<Status> state, List<List<String>> phi) {
        int mm = n;
        for (int i = 0; i < n; i++) {
            state.get(i).parent = state.get(i);
            state.get(i).depth = 0;
        }

        for (int q1 = 0; q1 < n; q1++) {
            for (int q2 = q1 + 1; q2 < n; q2++) {
                if (find(state.get(q1)) != find(state.get(q2))) {
                    boolean eq = true;
                    for (int x = 0; x < m; x++) {
                        if (!phi.get(q1).get(x).equals(phi.get(q2).get(x))) {
                            eq = false;
                            break;
                        }
                    }

                    if (eq) {
                        unionFunc(state.get(q1), state.get(q2));
                        mm -= 1;
                    }
                }
            }
        }

        for (int q = 0; q < n; q++) {
            state.get(q).pi = find(state.get(q));
        }

        return mm;
    }

    static int split(int n, int m, List<Status> state, List<List<String>> phi, List<List<Integer>> delta) {
        int mm = n;
        for (int i = 0; i < n; i++) {
            state.get(i).parent = state.get(i);
            state.get(i).depth = 0;
        }

        for (int q1 = 0; q1 < n; q1++) {
            for (int q2 = q1 + 1; q2 < n; q2++) {
                if (state.get(q1).pi == state.get(q2).pi &&
                        find(state.get(q1)) != find(state.get(q2))) {
                    boolean eq = true;
                    for (int x = 0; x < m; x++) {
                        Status w1 = state.get(q1).delt.get(x);
                        Status w2 = state.get(q2).delt.get(x);
                        if (w1.pi != w2.pi) {
                            eq = false;
                            break;
                        }
                    }

                    if (eq) {
                        unionFunc(state.get(q1), state.get(q2));
                        mm -= 1;
                    }
                }
            }
        }

        for (int q = 0; q < n; q++) {
            state.get(q).pi = find(state.get(q));
        }

        return mm;
    }

    static void DFS(int q0, List<List<Integer>> delta, Status s, Counter count, int m, List<Status> stat) {
        s.i = count.count;
        count.count++;
        s.was = true;
        for (int i = 0; i < m; i++) {
            int qq = delta.get(q0).get(i);
            if (!stat.get(qq).pi.was) {  // Access the Status object from the List stat
                DFS(qq, delta, stat.get(qq).pi, count, m, stat);  // Pass the Status object to DFS
            }
        }
    }

    static void printautomata(List<Status> state, List<List<String>> phi, int q0, 
                              int n, int m, BufferedWriter writer) throws IOException {
        writer.write("digraph {\n\trankdir = LR\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (state.get(i).was) {
                    writer.write(String.format("%d -> %d [label = \"%c(%s)\"]\n", state.get(i).i,
                            state.get(i).delt.get(j).pi.i, (char) (97 + j), phi.get(i).get(j)));
                }
            }
        }

        writer.write("}");
    }

    static class Counter {
        int count = 0;
    }

    static void AufenkampHohn(int n, int m, int q0, List<List<Integer>> delta, 
                              List<Status> state, List<List<String>> phi, Counter count) {
        int m1 = split1(n, m, state, phi);
        while (true) {
            int m2 = split(n, m, state, phi, delta);
            if (m1 == m2) {
                break;
            }

            m1 = m2;
        }

        DFS(q0, delta, state.get(q0).pi, count, m, state);
    }

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        scanner.useDelimiter("\\s+");

        int n = scanner.nextInt();
        int m = scanner.nextInt();
        int q0 = scanner.nextInt();
        scanner.nextLine();

        List<List<Integer>> delta = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            List<Integer> row = new ArrayList<>();
            for (int j = 0; j < m; j++) {
                row.add(scanner.nextInt());
            }
            scanner.nextLine();
            delta.add(row);
        }

        List<List<String>> phi = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            List<String> row = new ArrayList<>();
            for (int j = 0; j < m; j++) {
                phi.add(new ArrayList<>());
                phi.get(i).add(scanner.next());
            }

            scanner.nextLine();
        }

        List<Status> state = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            Status s = new Status();
            state.add(s);
        }
       for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                state.get(i).delt.add(state.get(delta.get(i).get(j)));
            }
        }
        Counter count = new Counter();
        AufenkampHohn(n, m, q0, delta, state, phi, count);
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
        printautomata(state, phi, q0, n, m, writer);
        writer.flush();
    }
}