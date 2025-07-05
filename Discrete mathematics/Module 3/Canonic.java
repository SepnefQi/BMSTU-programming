import java.util.*;

public class Canonic {
    public static void main (String[] args) {
        Scanner scanner = new Scanner(System.in);
        int x = 0;
        int n = scanner.nextInt();
        scanner.nextLine();
        int m = scanner.nextInt();
        scanner.nextLine();
        int q = scanner.nextInt();
        scanner.nextLine();
        
        int[][] perMatrix = new int[n][m];
        String[][] outMatrix = new String[n][m];
        
        for (int i=0; i<n; i++) {
            String[] line = scanner.nextLine().trim().split(" ");
            for (int j=0; j<m; j++) {
                perMatrix[i][j] = Integer.parseInt(line[j]);
            }
        }
        
        for (int i=0; i<n; i++) {
            String[] line = scanner.nextLine().trim().split(" ");
            for (int j=0; j<m; j++) {
                outMatrix[i][j] = line[j];
            }
        }
        
        int[] p1 = new int[n];
        int[] p2 = new int[n];
        Arrays.fill(p2, -1);

        Stack<Integer> stack = new Stack<>();
        stack.push(q);

        while (!stack.isEmpty()) {
            int qn = stack.pop();

            if (p2[qn] == -1) {
                p2[qn] = x;
                p1[x++] = qn;
                for (int i = m - 1; i >= 0; i--) {
                    int next = perMatrix[qn][i];
                    if (p2[next] == -1) {
                        stack.push(next);
                    }
                }
            }
        }
        
        System.out.println(n+"\n"+m+"\n"+0);
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                System.out.print(p2[perMatrix[p1[i]][j]]+" ");
            }
            System.out.println();
        }
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                System.out.print(outMatrix[p1[i]][j]+" ");
            }
            System.out.println();
        }
    }
}