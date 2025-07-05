import java.util.*;

public class Mealy2Moore {
	static class Tuple {
	  int f;
    String s;

    public Tuple(int f, String s) {
      this.f = f;
      this.s = s;
    }

    @Override
    public boolean equals(Object o) {
	    if (this == o) return true;
      if (o == null || getClass() != o.getClass()) return false;
      Tuple tuple = (Tuple) o;
      return f == tuple.f && s.equals(tuple.s);
    }

    @Override
    public int hashCode() {
      int result = f;
      result = 31 * result + s.hashCode();
      return result;
    }
  }
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		System.gc();
		
		int kin = scanner.nextInt();
		scanner.nextLine();
		String[] inputAlphabet = scanner.nextLine().split(" ");
		
		int kout = scanner.nextInt();
		scanner.nextLine();
		String[] outAlphabet = scanner.nextLine().split(" ");
		
		int n = scanner.nextInt();
		scanner.nextLine();
		int[][] perMatrix = new int[n][kin];
		for (int i=0; i<n; i++) {
			String[] line = scanner.nextLine().split(" ");
			for (int j=0; j<kin; j++) {
				perMatrix[i][j] = Integer.parseInt(line[j]);
			}
		}
		
		String[][] outMatrix = new String[n][kin];
		for (int i=0; i<n; i++) {
			String[] line = scanner.nextLine().split(" ");
			for (int j=0; j<kin; j++) {
				outMatrix[i][j] = line[j];
			}
		}
		
		List<Tuple> pts = new ArrayList<>();
    Map<Tuple, Integer> nums = new HashMap<>();

    for (int i = 0; i < n; i++) {
	    for (int j = 0; j < kin; j++) {
        int nm = Integer.parseInt(outMatrix[i][j]);
        Tuple currentTuple = new Tuple(perMatrix[i][j], outAlphabet[nm]);
        if (!nums.containsKey(currentTuple)) {
          pts.add(currentTuple);
          nums.put(currentTuple, nums.size());
        }
      }
    }
		
		System.out.println("digraph {");
		System.out.println("\trankdir = LR");
		for (int i = 0; i < pts.size(); i++) {
			Tuple value = pts.get(i);
			System.out.printf("\t%d [label = \"(%d,%s)\"]\n", i, value.f, value.s);
		}
		for (int i=0; i<pts.size(); i++) {
			Tuple value = pts.get(i);
			for (int j=0; j<kin; j++) {
				int nm = Integer.parseInt(outMatrix[value.f][j]);
				Tuple tupleIn = new Tuple(perMatrix[value.f][j], outAlphabet[nm]);
				System.out.printf("\t%d -> %d [label = \"%s\"]\n", i, nums.get(tupleIn), inputAlphabet[j]);
			}
		}
		System.out.print("}");
	}
}