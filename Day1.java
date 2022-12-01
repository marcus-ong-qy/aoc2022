// Day 1
// https://adventofcode.com/2022/day/1
import java.util.Scanner;

public class Day1 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int maxSum = 0;
        int curSum = 0;
        
        while(in.hasNext()) {
            String line = in.nextLine();
            if (line.equals("")) {
                if (curSum > maxSum) maxSum = curSum;
                curSum = 0;
            } else if (line.equals("end")) {
                if (curSum > maxSum) {
                    maxSum = curSum;
                    curSum = 0;
                }
                break;
            } else {
                int num = Integer.parseInt(line);
                curSum += num;
            }
        }
        
        System.out.println(maxSum);
        in.close();
    }
}
