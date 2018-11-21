package Solution;

import java.util.LinkedList;
import java.util.Queue;

public class ITES {
	public static int getSubSumNumber(int k, int n) {
		long seqNum = 0;
		int inputNum = 0;
		Queue<Integer> seq = new LinkedList<Integer>();
		int sum = 0;
		int result = 0;
		
		for(int i = 0; i < n; i++) {
			seqNum = getNextNumber(i,seqNum);
			inputNum = getNextInputNumber(seqNum);
			
			seq.add(inputNum);
			sum += inputNum;
			
			while(sum > k) {
				sum -= seq.peek();
				seq.poll();
			}
			if(sum == k)
				result++;
		}
		
		return result;
	}
	
	public static long getNextNumber(int idx, long preNum) {
		if(idx == 0)
			return 1983;
		return (long) ((preNum * 214013 + 2531011) % Math.pow(2,32));
	}
	
	public static int getNextInputNumber(long num) {
		return (int) (num % 10000 + 1);
	}
}
