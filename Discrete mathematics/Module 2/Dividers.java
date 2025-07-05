import java.util.*;

public class Dividers {
	static boolean proverka(long x) {
		if (x==4) {
			return false;
		}
		for (long i=2; i<x/2; i++) {
			if (x%i==0) {
				return false;
			}
		}
		return true;
	}
	
	static void buildGraphTopDown(long x, List<Long> divisors) {
		for (int i=0; i<divisors.size(); i++) {
			for (int j=i+1; j<divisors.size(); j++) {
				if (divisors.get(i)%divisors.get(j)==0) {
					if (proverka((long)(divisors.get(i) / divisors.get(j)))) {
						System.out.println("    "+divisors.get(i)+"--"+divisors.get(j));
					}
			  }
		  }
	  }
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		long x = scanner.nextLong();
		System.out.println("graph {");

		List<Long> divisors = new ArrayList<>();
		divisors.add(x);
		System.out.println("    "+x);
		for (long i=x/2; i>0; i--) {
			if (x%i==0) {
				divisors.add(i);
				System.out.println("    "+i);
			}
		}
		buildGraphTopDown(x, divisors);

		System.out.println("}");
	}
}