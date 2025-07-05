import java.util.*;

public class MaxComponent {

    static class Top {
        int val;
        char mark;
        int place;
        int there;

        public Top(int val) {
            this.val = val;
            this.mark = 'w';
            this.place = 0;
            this.there = 0;
        }
    }

    static class Big {
        int top;
        int rib;

        public Big(int top, int rib) {
            this.top = top;
            this.rib = rib;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long tops = scanner.nextLong();
        long ribs = scanner.nextLong();
        scanner.nextLine();

        List<Top> graph = new ArrayList<>();
        for (int i = 0; i < tops; i++)
            graph.add(new Top(i));

        List<List<Top>> matrix = new ArrayList<>();
        for (int i = 0; i < tops; i++)
            matrix.add(new ArrayList<>());

        for (int i = 0; i < ribs; i++) {
            int j = scanner.nextInt();
            int t = scanner.nextInt();
            scanner.nextLine();

            Top topT = new Top(t);
            topT.there = 1;
            matrix.get(j).add(topT);

            if (j != t) {
                Top topJ = new Top(j);
                matrix.get(t).add(topJ);
            }
        }

        List<Big> reds = new ArrayList<>();
        dfs(graph, matrix, reds);

        int maxPlace = max(reds);
        if (maxPlace != -1) {
            dfsReds(graph, matrix, maxPlace + 1);
        }
        graphPrint(graph, matrix);
    }

    public static void graphPrint(List<Top> graph, List<List<Top>> matrix) {
        System.out.println("graph {");
        for (int i = 0; i < graph.size(); i++) {
            System.out.print("    " + i);
            if (graph.get(i).mark == 'r') {
                System.out.print(" [color = red]");
            }
            System.out.println();
        }

        for (int i = 0; i < graph.size(); i++) {
            for (int t = 0; t < matrix.get(i).size(); t++) {
                if (matrix.get(i).get(t).there == 1) {
                    System.out.print("    " + i + " -- " + matrix.get(i).get(t).val);
                    if (matrix.get(i).get(t).mark == 'r') {
                        System.out.print(" [color = red]");
                    }
                    System.out.println();
                }
            }
        }
        System.out.println("}");
    }

    public static void visitVertexIterative(List<Top> graph, int startVertex, List<List<Top>> matrix, 
                                            IntWrapper nTops, IntWrapper nRibs, int place) {
        Stack<Integer> stack = new Stack<>();
        stack.push(startVertex);

        while (!stack.isEmpty()) {
            int v = stack.pop();

            if (graph.get(v).mark != 'w' && graph.get(v).place == place) continue;

            graph.get(v).mark = 'g';

            if (graph.get(v).place != place) {
                nTops.value++;
                graph.get(v).place = place;
            }


            for (int i = 0; i < matrix.get(v).size(); i++) {
                Top neighborTop = matrix.get(v).get(i);
                int neighbor = neighborTop.val;

                if (neighborTop.mark == 'w') {
                    neighborTop.mark = 'g';
                    neighborTop.place = place;
                     if (neighborTop.there == 1) {
                        nRibs.value++;
                    }
                    stack.push(neighbor);
                }

            }
        }
    }

    static class IntWrapper {
        int value;

        public IntWrapper(int value) {
            this.value = value;
        }
    }

    public static void dfs(List<Top> graph, List<List<Top>> matrix, List<Big> reds) {
        int place = 0;
        for (int v = 0; v < graph.size(); v++) {
            if (graph.get(v).mark == 'w') {
                place++;
                IntWrapper nTops = new IntWrapper(0);
                IntWrapper nRibs = new IntWrapper(0);
                visitVertexIterative(graph, v, matrix, nTops, nRibs, place);
                reds.add(new Big(nTops.value, nRibs.value));
            }
        }
    }

    public static int max(List<Big> reds) {
        int maxVal = -1;
        int place = -1;
        int maxRibs = -1;
        for (int i = 0; i < reds.size(); i++) {
            if (reds.get(i).top > maxVal || (reds.get(i).top == maxVal && reds.get(i).rib > maxRibs)) {
                maxVal = reds.get(i).top;
                maxRibs = reds.get(i).rib;
                place = i;
            }
        }
        return place;
    }

    public static void visitVertexRedsIterative(List<Top> graph, int startVertex, 
                                                List<List<Top>> matrix, int place) {
        Stack<Integer> stack = new Stack<>();
        stack.push(startVertex);

        while (!stack.isEmpty()) {
            int v = stack.pop();

            if (graph.get(v).mark == 'r') continue;

            graph.get(v).mark = 'r';

            for (int i = 0; i < matrix.get(v).size(); i++) {
                Top neighborTop = matrix.get(v).get(i);

                if (neighborTop.mark != 'r') {
                    neighborTop.mark = 'r';
                    stack.push(neighborTop.val);
                }
            }
        }
    }


    public static void dfsReds(List<Top> graph, List<List<Top>> matrix, int place) {
        for (int v = 0; v < graph.size(); v++) {
            if (graph.get(v).place == place) {
                visitVertexRedsIterative(graph, v, matrix, place);
                break;
            }
        }
    }
}