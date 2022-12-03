// Day 3
// https://adventofcode.com/2022/day/3
import java.util.Scanner;

public class Day3 {
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

        while(in.hasNext()) {
            String allItems = in.nextLine();
            if (allItems.equals("q!")) break;
            
            int itemsCount = allItems.length();
            int divider = itemsCount / 2;

            outerloop:
            for (int i=0; i < divider; i++) {
                for (int j=divider; j < itemsCount; j++) {
                    char item1 = allItems.charAt(i);
                    char item2 = allItems.charAt(j);
                    if (item1 == item2) {
                        score += getPriorityScore(item1);
                        break outerloop;
                    }
                }
            }
        }

        System.out.println(score);
        in.close();
    }
}
