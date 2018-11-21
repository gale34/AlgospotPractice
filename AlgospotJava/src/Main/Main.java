package Main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Main {
//    public static void main(String[] args) {
//        /*Scanner sc = new Scanner(System.in);
//        int cases = sc.nextInt();*/
//
//        try {
//            File file = new File("./input.txt");
//            FileReader reader = new FileReader(file);
//            BufferedReader bufReader = new BufferedReader(reader);
//            String line = bufReader.readLine();
//    
//            int cases = Integer.parseInt(line);
//            for(int i = 0; i < cases; i++) {
//                //String bracket = sc.nextLine();
//                String bracket = bufReader.readLine();
//    
//                Boolean result = BRACKETS2.isRightBracket(bracket);
//                if(result)
//                    System.out.println("YES");
//                else
//                    System.out.println("NO");
//            }
//
//            bufReader.close();
//        } catch (IOException e) {
//            System.out.println(e);
//        }
//
//    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int cases = Integer.parseInt(sc.nextLine());

        for(int i = 0; i < cases; i++) {
        	int k = sc.nextInt();
        	int n = sc.nextInt();
        	
            int result = getSubSumNumber(k, n);
            System.out.println(result);
        }
        sc.close();
    }
    
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

