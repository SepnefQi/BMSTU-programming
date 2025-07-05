import java.util.*;

class Edge {
	int source;
	int dest;
	int weight;
	public Edge(int source, int dest, int weight) {
		this.source = source;
		this.dest = dest;
		this.weight = weight;
	}
}

class Graph {
	private int vert;
	private LinkedList<Edge>[] gr;

	public Graph(int vert) {
		this.vert = vert;
		gr = new LinkedList[vert];
		for (int i=0; i<vert; i++) {
			gr[i] = new LinkedList<>();
		}
	}

	void addEdge(int s1, int s2, int s3) {
		Edge edge1 = new Edge(s1, s2, s3);
		Edge edge2 = new Edge(s2, s1, s3);
		gr[s1].add(edge1);
		gr[s2].add(edge2);
	}

	void prim() {
		boolean[] inMST = new boolean[vert];
		PriorityQueue<Edge> prior = new PriorityQueue<>(Comparator.comparingInt(e -> e.weight));
			
		List<Edge> mst = new ArrayList<>();
		int start = 0;
		inMST[start] = true;
			
		for (Edge edge : gr[start]) {
			prior.add(edge);
		}
			
		while (!prior.isEmpty()) {
			Edge currentEdge = prior.poll();
				
			if (!inMST[currentEdge.dest]) {
				mst.add(currentEdge);
					
				inMST[currentEdge.dest] = true;
					
				for (Edge edge : gr[currentEdge.dest]) {
					if (!inMST[edge.dest]) {
						prior.add(edge);
					}
				}
			}
		}
		int sum = 0;
		for (Edge edge : mst) {
			sum += edge.weight;
		}
		System.out.print(sum);
	}
}

public class Prim {		
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		int m = scanner.nextInt();
		Graph graph = new Graph(n);
		
		for (int i=0; i<m; i++) {
			int s1 = scanner.nextInt();
			int s2 = scanner.nextInt();
			int s3 = scanner.nextInt();
			graph.addEdge(s1, s2, s3);
		}
		
		graph.prim();
	}
}