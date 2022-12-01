// Day 1 Part 2
// https://adventofcode.com/2022/day/1#part2
import java.util.Arrays;
import java.util.Scanner;

public class Day1_2 {

    
    static int[] checkMax(int[] maxSums, int curSum) {
        int minIdx = 0;
        int minOfMax = maxSums[minIdx];

        for (int i = 0; i < 3; i++) {
            if (maxSums[i] <= minOfMax) {
                minOfMax = maxSums[i];
                minIdx = i;
            }
        }

        if (curSum > minOfMax) {
            maxSums[minIdx] = curSum;
        }
        return maxSums;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int[] maxSums = {0, 0, 0};
        int curSum = 0;
        
        while(in.hasNext()) {
            String line = in.nextLine();
            if (line.equals("")) {
                maxSums = checkMax(maxSums, curSum);
                curSum = 0;
            } else if (line.equals("end")) {
                maxSums = checkMax(maxSums, curSum);
                curSum = 0;
                break;
            } else {
                int num = Integer.parseInt(line);
                curSum += num;
            }
        }
        
        System.out.println(Arrays.stream(maxSums).sum());
        in.close();
    }
}
