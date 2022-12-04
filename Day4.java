// Day 4
// https://adventofcode.com/2022/day/4
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day4 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int score = 0;

        while(in.hasNext()) {
            String line = in.nextLine();
            if (line.equals("q!")) break;
            String pattern = "^(\\d+)-(\\d+),(\\d+)-(\\d+)$";

            Pattern r = Pattern.compile(pattern);
            Matcher matcher = r.matcher(line);

            if (matcher.find()) {
                int num1 = Integer.parseInt(matcher.group(1));
                int num2 = Integer.parseInt(matcher.group(2));
                int num3 = Integer.parseInt(matcher.group(3));
                int num4 = Integer.parseInt(matcher.group(4));
                
                boolean isSubset = (num3 <= num1 && num4 >= num2) || (num1 <= num3 && num2 >= num4);
                if (isSubset) score++;
            } 
        }
        System.out.println(score);
        in.close();
    }
}
