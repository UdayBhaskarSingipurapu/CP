// Generate all primes b/w [n, m]
// n, m <= 10^9;
// n - m <= 10^5

import java.util.*;

public class SegmentSieve {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Main. */
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        boolean[] compute = new boolean[1000000 + 1];
        Arrays.fill(compute, true);
        compute[0] = compute[1] = false;

        List<Integer> primes = new ArrayList<>();
        for(int i = 2; i <= 1000000; i++){
            if(compute[i] == true){
                primes.add(i);
                if((long)i * i > 1000000) continue;
                for(int j = i * i; j <= 1000000; j += i){
                    compute[j] = false;
                }
            }
        }

        while(t-- > 0){
            long m = sc.nextLong(), n = sc.nextLong();
            int sz = (int)(n - m + 1);
            boolean[] segment = new boolean[sz];
            Arrays.fill(segment, true);
            for(int pl: primes){
                long p = pl;
                if(p * p > n) break;
                long start = Math.max(p * p, ((m + p - 1) / p) * p);
                for(long j = start; j <= n; j += p){
                    int idx = (int)(j - m);
                    segment[idx] = false;
                }
            }

            for(long i = m; i <= n; i++){
                int idx = (int)(i - m);
                if(segment[idx] == true && i > 1){
                    System.out.println(i);
                }
            }
            System.out.println();
        }
    }
}