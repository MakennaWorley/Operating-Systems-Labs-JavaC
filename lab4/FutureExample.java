/**
 * Summation program using exectuors/callable/futures
 */

import java.util.concurrent.*;
import java.util.ArrayList;
import java.util.List;

class Collatz implements Callable<List<Integer>> {
    private int start;

    public Collatz(int start) {
        this.start = start;
    }

    @Override
    public List<Integer> call() {
        List<Integer> sequence = new ArrayList<>();
        int n = start;

        while (n != 1) {
            sequence.add(n);
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
        }
        sequence.add(1);
        return sequence;
    }
}


public class FutureExample
{
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java Attempt1 <integer>");
            System.exit(0);
        }
        else {
            int value = Integer.parseInt(args[0]);

            ExecutorService pool = Executors.newSingleThreadExecutor();
            Future<List<Integer>> result = pool.submit(new Collatz(value));

            try {
                List<Integer> sequence = result.get();
                System.out.println("Collatz sequence: " + sequence);
            }
            catch (InterruptedException | ExecutionException ie) {
                ie.printStackTrace();
            } finally {
                pool.shutdown();
            }
        }
    }
}