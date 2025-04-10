/**
 * DiningServer.java
 *
 * This class contains the methods called by the  philosophers.
 */

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class DiningServerImpl  implements DiningServer
{  
	// different philosopher states
	enum State {THINKING, HUNGRY, EATING};
	
	// number of philosophers
	public static final int NUMBER_OF_PHILOSOPHERS = 5;
	
	// array to record each philosopher's state
	private State[] state;

	private final ReentrantLock lock = new ReentrantLock();
	private final Condition[] self = new Condition[NUMBER_OF_PHILOSOPHERS];
	
	public DiningServerImpl()
	{
		// array of philosopher's state
		state = new State[NUMBER_OF_PHILOSOPHERS];
		
		// originally all philosopher's are thinking
		for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
			state[i] = State.THINKING;
			self[i] = lock.newCondition();
		}
	}
	
	// called by a philosopher when they wish to eat 
	public void takeForks(int pnum)  {
		lock.lock();

		try {
			state[pnum] = State.HUNGRY;
			test(pnum);

			if (state[pnum] != State.EATING) {
				self[pnum].await();
			}
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
		} finally {
			lock.unlock();
		}
	}
	
	// called by a philosopher when they are finished eating 
	public void returnForks(int pnum) {
		lock.lock();
		try {
			state[pnum] = State.THINKING;

			test(leftNeighbor(pnum));
			test(rightNeighbor(pnum));
		} finally {
			lock.unlock();
		}
	}
	
	private void test(int i)
	{
		// in other words ... if I'm hungry and my left and
		// right nieghbors aren't eating, then let me eat!

		if (state[i] == State.HUNGRY && state[leftNeighbor(i)] != State.EATING && state[rightNeighbor(i)] != State.EATING) {
			state[i] = State.EATING;
			self[i].signal();
		}
	}
	
	// return the index of the left neighbor of philosopher i
	private int leftNeighbor(int i)
	{
        return ((i + 1) % NUMBER_OF_PHILOSOPHERS);
    }
	
	// return the index of the right neighbor of philosopher i
	private int rightNeighbor(int i)
	{
        return ((i + 4) % NUMBER_OF_PHILOSOPHERS);
	}
}
