/**
 * Implementation of the Manager interface that
 * permits a number of licenses.
 */

import java.util.concurrent.locks.ReentrantLock;

public class LicenseManager implements Manager
{

    private final ReentrantLock mutex; //immutable

    // the number of available permits
    private int permits;
  
    public LicenseManager(int permits) {
        if (permits < 0)
            throw new IllegalArgumentException();
        this.permits = permits;

        this.mutex = new ReentrantLock();

    }
   
    public boolean acquirePermit() {
        mutex.lock();

        try {
            if (permits > 0) {
                permits--;
                return true;
            }

            return false;
        } finally {
            mutex.unlock();
        }
    }
  
    public void releasePermit() {
        mutex.lock();
        
        try {
            permits++;
        }
        finally {
            mutex.unlock();
        }
    }
}
  
