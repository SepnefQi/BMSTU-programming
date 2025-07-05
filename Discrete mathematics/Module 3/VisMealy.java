import java.util.*;

public class VisMealy {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		int m = scanner.nextInt();
		int q0 = scanner.nextInt();
		int[][] matper = new int[n][m];
		String[][] matout = new String[n][m];

		for (int i=0; i<n; i++) {
			for (int j=0; j<m; j++) {
				matper[i][j] = scanner.nextInt();
			}
		}

		for (int i=0; i<n; i++) {
			for (int j=0; j<m; j++) {
				matout[i][j] = scanner.next();
			}
		}

		System.out.println("digraph {");
		System.out.println("    rankdir = LR");
		for (int i=0; i<n; i++) {
			for (int j=0; j<m; j++) {
				System.out.printf("    %d -> %d [label = \"%c(%s)\"]\n", i, matper[i][j], 'a'+j, matout[i][j]);
			}
		}
		System.out.print("}");
	}
} 