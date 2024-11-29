//frame code for programming assignment 5;
//file name must be same as the main class name, i.e., sr_manager.java

public class sr_manager // main class
{
    static sr1 r1 = new sr1();
    static sr2 r2 = new sr2();

    public static void main(String args[]) {
        // create and start 6 threads for 6 concurrent processes
        process[] p = new process[6];

        for (int i = 0; i < 6; i++) {
            p[i] = new process(i, r1, r2);
            p[i].start();
        }
    }
}

class sr1 // monitor class for shared resource r1
{
    private static int avail1 = 3;

    public synchronized void acquire(int id) {
        while (avail1 == 0) {
            System.out.println("process_" + id + " waiting for resource 1");
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        avail1--;
        System.out.println("process_" + id + " acquired resource 1");
    }

    public synchronized void release(int id) {
        avail1++;
        System.out.println("process_" + id + " released resource 1");
        notify();
    }
}

class sr2 // monitor class for shared resource r2
{
    private static int avail2 = 2;

    public synchronized void acquire(int id) {
        while (avail2 == 0) {
            System.out.println("process_" + id + " waiting for resource 2");
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        System.out.println("process_" + id + " acquired resource 2");
        avail2--;
    }

    public synchronized void release(int id) {
        avail2++;
        System.out.println("process_" + id + " released resource 2");
        notifyAll();
    }
}

class process extends Thread // thread class
{
    static sr1 r1;
    static sr2 r2;
    final int id;

    public process(int k, sr1 r1, sr2 r2) // constructor
    {
        this.r1 = r1;
        this.r2 = r2;
        this.id = k;
    }

    @Override
    public void run() {

        // acquire r1 and r2;
        r1.acquire(id);
        r2.acquire(id);
        System.out.println("process_" + id + " is working");

        try {
            Thread.sleep(500); // 500 milliseconds = 0.5 seconds
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        // release r1 and r2;
        r1.release(id);
        r2.release(id);
    }
}// class process
