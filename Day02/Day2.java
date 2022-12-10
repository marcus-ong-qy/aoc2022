// Day 2
// https://adventofcode.com/2022/day/2
import java.util.Map;
import java.util.Scanner;

public class Day2 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int score = 0;

        Map<Character, Character> conversionMap = Map.of(
            'Y','B', 
            'X','A',
            'Z', 'C'
        );

        Map<Character, Character> playerWinsMap = Map.of(
            'Y','A', 
            'X','C',
            'Z', 'B'
        );

        Map<Character, Integer> moveScoreMap = Map.of(
            'X', 1,
            'Y', 2,
            'Z', 3
        );

        
        while(in.hasNext()) {
            String line = in.nextLine();

            if (line.equals("end")) {
                break;
            }

            Character opponent = line.charAt(0);
            Character player = line.charAt(2);

            score += moveScoreMap.get(player);

            if (conversionMap.get(player) == opponent) {
                score += 3; // draw
            } else if (playerWinsMap.get(player) == opponent) {
                score += 6; // win
            } else {
                // System.out.println("lose");
                // lose
            }
        }
        System.out.println(score);
        in.close();
    }
}
