/**
 * This program creates a separate thread by implementing the Runnable interface.
 */

/**
 * The instance of the shared object
 */

class Sum
{
    private int sum;

    public int get() {
        return sum;
    }

    public void set(int sum) {
        this.sum = sum;
    }
}

/**
 * This runs as a separate Java thread.
 *
 * This performs a summation from 1 .. upper 
 */
class Summation implements Runnable
{
    private int value;

    public Summation(int value) {
        this.value = value;
    }

    public void run() {
        while (value != 1) {
            if (value % 2 == 0) {
                value /= 2;
            } else {
                value = 3 * value + 1;
            }
            System.out.println(value);
        }
    }
}

public class Driver
{
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage java Driver <integer>");
            System.exit(0);
        }

        if (Integer.parseInt(args[0]) < 0) {
            System.err.println(args[0] + " must be >= 0");
            System.exit(0);
        }

        // Create the shared object
        Sum sumObject = new Sum();
        int value = Integer.parseInt(args[0]);

        Thread worker = new Thread(new Summation(value));
        worker.start();

        try {
            worker.join();
        } catch (InterruptedException ie) { System.err.println(ie); }
    }
}