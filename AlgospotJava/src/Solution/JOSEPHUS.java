package Solution;

import java.util.ArrayList;
import java.util.List;

public class JOSEPHUS {

    public JOSEPHUS () {

    }

    public static List<Integer> getLastTwoSoldiers(int numOfSoldiers, int jump) {
        List<Integer> soldiers = new ArrayList<Integer>();
        int start = 0;

        for(int i = 0; i < numOfSoldiers; i++) {
            soldiers.add(i+1);
        }

        while(soldiers.size() > 2) {
            soldiers.remove(start);
            start = (start + jump - 1) % soldiers.size();
        } 

        return soldiers;
    }
}