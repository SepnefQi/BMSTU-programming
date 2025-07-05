import java.util.*;

public class EqMealy {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n1 = Integer.parseInt(scanner.nextLine());
    int m1 = Integer.parseInt(scanner.nextLine());
    int q0_1 = Integer.parseInt(scanner.nextLine());

    int[][] delta1 = new int[n1][m1];
    for (int i = 0; i < n1; i++) {
	    String[] line = scanner.nextLine().split(" ");
	    for (int j = 0; j < m1; j++) {
        delta1[i][j] = Integer.parseInt(line[j]);
      }
    }

    String[][] phi1 = new String[n1][m1];
    for (int i = 0; i < n1; i++) {
	    String[] line = scanner.nextLine().split(" ");
      for (int j = 0; j < m1; j++) {
        phi1[i][j] = line[j];
      }
    }

    MealyMachine machine1 = new MealyMachine(n1, m1, q0_1, delta1, phi1);

    int n2 = Integer.parseInt(scanner.nextLine());
    int m2 = Integer.parseInt(scanner.nextLine());
    int q0_2 = Integer.parseInt(scanner.nextLine());

    int[][] delta2 = new int[n2][m2];
    for (int i = 0; i < n2; i++) {
	    String[] line = scanner.nextLine().split(" ");
	    for (int j = 0; j < m2; j++) {
        delta2[i][j] = Integer.parseInt(line[j]);
      }
    }

    String[][] phi2 = new String[n2][m2];
    for (int i = 0; i < n2; i++) {
	    String[] line = scanner.nextLine().split(" ");
      for (int j = 0; j < m2; j++) {
        phi2[i][j] = line[j];
      }
    }

    MealyMachine machine2 = new MealyMachine(n2, m2, q0_2, delta2, phi2);

    if (areEquivalent(machine1, machine2)) {
	    System.out.println("EQUAL");
    } else {
      System.out.println("NOT EQUAL");
    }
  }

  static boolean areEquivalent(MealyMachine machine1, MealyMachine machine2) {
	  if (machine1.m != machine2.m) {
      return false;
    }

    int m = machine1.m;

    Queue<StatePair> queue = new LinkedList<>();
    queue.offer(new StatePair(machine1.q0, machine2.q0));

    List<StatePair> visited = new ArrayList<>();
    visited.add(new StatePair(machine1.q0, machine2.q0));

    while (!queue.isEmpty()) {
        StatePair currentPair = queue.poll();
        int state1 = currentPair.state1;
        int state2 = currentPair.state2;

        for (int input = 0; input < m; input++) {
            if (!machine1.phi[state1][input].equals(machine2.phi[state2][input])) {
                return false;
            }

            int nextState1 = machine1.delta[state1][input];
            int nextState2 = machine2.delta[state2][input];

            if (nextState1 < 0 || nextState1 >= machine1.n || nextState2 < 0 || nextState2 >= machine2.n) {
	            return false;
            }

            StatePair nextPair = new StatePair(nextState1, nextState2);
            if (!visited.contains(nextPair)) {
              boolean validState1 = nextState1 >= 0 && nextState1 < machine1.n;
              boolean validState2 = nextState2 >= 0 && nextState2 < machine2.n;

              if (validState1 && validState2) {
                queue.offer(nextPair);
                visited.add(nextPair);
              }
           }
        }
    }
    return true;
  }

  static class MealyMachine {
    int n;
    int m;
    int q0;
    int[][] delta;
    String[][] phi;

    public MealyMachine(int n, int m, int q0, int[][] delta, String[][] phi) {
        this.n = n;
        this.m = m;
        this.q0 = q0;
        this.delta = delta;
        this.phi = phi;
    }
  }

  static class StatePair {
    int state1;
    int state2;

    public StatePair(int state1, int state2) {
        this.state1 = state1;
        this.state2 = state2;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        StatePair statePair = (StatePair) obj;
        return state1 == statePair.state1 && state2 == statePair.state2;
    }

    @Override
    public int hashCode() {
	    return java.util.Objects.hash(state1, state2);
    }
  }
}