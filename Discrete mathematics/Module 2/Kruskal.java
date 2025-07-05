import java.util.*;
import java.lang.Math;
import java.text.DecimalFormat;

public class Kruskal {
	static class About {
		int parent, rank;
	}

	static class Edge implements Comparable<Edge> {
		int now, in;
		double weight;

		Edge(int now, int in, double weight) {
			this.now = now;
			this.in = in;
			this.weight = weight;
		}

		@Override
		public int compareTo(Edge other) {
			return Double.compare(this.weight, other.weight);
		}
	}

	static int find(About[] pairs, int i) {
		if (pairs[i].parent != i) {
			pairs[i].parent = find(pairs, pairs[i].parent);
		}
		return pairs[i].parent;
	}
	
	static void union(About[] subsets, int x, int y) {
		int xx = find(subsets, x);
		int yy = find(subsets, y);
		
		if (subsets[xx].rank < subsets[yy].rank) {
			subsets[xx].parent = yy;
		} else if (subsets[xx].rank > subsets[yy].rank) {
			subsets[yy].parent = xx;
		} else {
			subsets[yy].parent = xx;
			subsets[xx].rank++;
		}
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		int[][] coord = new int[n][2];
		for (int i=0; i<n; i++) {
			coord[i][0] = scanner.nextInt();
			coord[i][1] = scanner.nextInt();
		}

		List<Edge> edges = new ArrayList<>();
		// edges - список: откуда, куда, какое расстояние

		for (int i=0; i<n; i++) {
			for (int j=i+1; j<n; j++) {
				double dist = Math.sqrt(Math.pow(coord[i][0]-coord[j][0], 2) + 
				                        Math.pow(coord[i][1]-coord[j][1], 2));
				edges.add(new Edge(i, j, dist));
			}
		}

		Collections.sort(edges); // сортирует, за счёт определённого нами compareTo
		About[] subsets = new About[n];

		for (int i=0; i<n; i++) {
			subsets[i] = new About();
			subsets[i].parent = i;
			subsets[i].rank = 0;
		}

		double min_len = 0;
		int s_edge = 0, i = 0;

		while (s_edge < n-1 && i < edges.size()) {
			Edge edge = edges.get(i++);
			int x = find(subsets, edge.now);
			int y = find(subsets, edge.in);

			if (x!=y) {
				min_len += edge.weight;
				union(subsets, x, y);
				s_edge++;
			}
		}

		DecimalFormat df = new DecimalFormat("0.00");
		System.out.print(df.format(min_len));
	}
}