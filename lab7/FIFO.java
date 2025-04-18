/**
 * This class implements the FIFO page-replacement strategy.
 *
 */

public class FIFO extends ReplacementAlgorithm
{
	// FIFO list of page frames
	private FIFOList frameList;

	/**
	 * @param pageFrameCount - the number of physical page frames
	 */
	public FIFO(int pageFrameCount) {
		super(pageFrameCount);
		frameList = new FIFOList(pageFrameCount);
	}

	/**
	 * insert a page into a page frame.
	 * @param int pageNumber - the page number being inserted.
	 */
	public void insert(int pageNumber) {
		frameList.insert(pageNumber);
    }
		
	class FIFOList
	{
		// the page frame list
		int[] pageFrameList;

		// the number of elements in the page frame list
		int elementCount;

		FIFOList(int pageFrameCount) {
			pageFrameList = new int[pageFrameCount];

            // we initialize each entry to -1 to indicate initial value is invalid 
            java.util.Arrays.fill(pageFrameList,-1);
			elementCount = 0;
		}

		/**
	 	 * insert a page into a page frame.
	 	 * @param int pageNumber - the page number being inserted.
	 	 */
		void insert(int pageNumber) {
			// insert pageNumber into frameList using FIFO algorithm
			if (!search(pageNumber)) {
				pageFaultCount++;

				if (elementCount < pageFrameList.length) {
					pageFrameList[elementCount] = pageNumber;
				} else {
					int mod = elementCount % pageFrameList.length;
					pageFrameList[mod] = pageNumber;
				}

				elementCount++;
			}
    	}

		/**
		 * Searches for page pageNumber in the page frame list
		 * @return true if pageNumber was found
		 * @return false if pageNumber was not found
		 */
		boolean search(int pageNumber) {
			boolean returnVal = false;

			for (int i = 0; i < pageFrameList.length; i++) {
				if (pageNumber == pageFrameList[i]) {
					returnVal = true;
					break;
				}
			}
			return returnVal;
		}
	}
}
