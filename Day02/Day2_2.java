// Day 2 Part 2
// https://adventofcode.com/2022/day/2#part2
import java.util.Map;
import java.util.Scanner;

public class Day2_2 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int score = 0;

        Map<Character, Integer> toLoseMap = Map.of(
            'A', 3,
            'B', 1,
            'C', 2
        );

        Map<Character, Integer> toWinMap = Map.of(
            'A', 2,
            'B', 3,
            'C', 1
        );

        Map<Character, Integer> toDrawMap = Map.of(
            'A', 1,
            'B', 2,
            'C', 3
        );

        Map<Character, Integer> outcomeScoreMap = Map.of(
            'X', 0,
            'Y', 3,
            'Z', 6
        );

        
        while(in.hasNext()) {
            String line = in.nextLine();

            if (line.equals("end")) {
                break;
            }

            Character opponentMove = line.charAt(0);
            Character playerAction = line.charAt(2);

            score += outcomeScoreMap.get(playerAction);

            if (playerAction == 'X') {
                // to lose
                score += toLoseMap.get(opponentMove);
            } else if (playerAction == 'Z') {
                // to win
                score += toWinMap.get(opponentMove);
            } else {
                // to draw
                score += toDrawMap.get(opponentMove);
            }
        }
        System.out.println(score);
        in.close();
    }
}
