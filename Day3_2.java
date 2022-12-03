// Day 3 Part 2
// https://adventofcode.com/2022/day/3#part2
import java.lang.reflect.Array;
import java.util.Scanner;

public class Day3_2 {
    static int getPriorityScore(char letter) {
        if ('A' <= letter && letter <= 'Z') {
            return letter - 'A' + 27;
        } else if ('a' <= letter && letter <= 'z') {
            return letter - 'a' + 1;
        } else {
            System.out.println("Invalid Input");
            return 0;
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int score = 0;
        int counter = 0;
        String bags[] = {"", "", ""};

        while(in.hasNext()) {
            String items = in.nextLine(); counter++;
            if (items.equals("q!")) break;

            Array.set(bags, counter % 3, items);
            
            if (counter % 3 == 0) {
                String bag1 = (String) Array.get(bags, 0);
                String bag2 = (String) Array.get(bags, 1);
                String bag3 = (String) Array.get(bags, 2);

                outerloop:
                for (int i=0; i < bag1.length(); i++) {
                    for (int j=0; j < bag2.length(); j++) {
                            for (int k=0; k < bag3.length(); k++) {
                            char item1 = bag1.charAt(i);
                            char item2 = bag2.charAt(j);
                            char item3 = bag3.charAt(k);

                            if (item1 == item2 && item2 == item3) {
                                score += getPriorityScore(item1);
                                break outerloop;
                            }
                        }
                    }
                }
            }
        }

        System.out.println(score);
        in.close();
    }
}
