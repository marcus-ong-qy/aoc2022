// Day 5 Part 2
// https://adventofcode.com/2022/day/5#part2
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day5_2 {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
 
    String[] crates = {
        "WRF", "THMCDVWP", "PMZNL", 
        "JCHR", "CPGHQTB", "GCWLFZ", 
        "WVLQZJGC", "PNRFWTVC", "JWHGRSV"
    };
      
    String pattern = "^move (\\d+) from (\\d+) to (\\d+)$";
    Pattern r = Pattern.compile(pattern);

    while(in.hasNext()) {
      String line = in.nextLine();
      if (line.equals("q!")) break;
      Matcher matcher = r.matcher(line);

      if (matcher.find()) {
        int moveCount = Integer.parseInt(matcher.group(1));
        int fromStackIdx = Integer.parseInt(matcher.group(2)) - 1;
        int toStackIdx = Integer.parseInt(matcher.group(3)) - 1;
        
        String fromCrateString = crates[fromStackIdx];
        int fromCratesLength = fromCrateString.length();
        String cratesToMove = fromCrateString.substring(fromCratesLength-moveCount, fromCratesLength);
        
        crates[fromStackIdx] = fromCrateString.substring(0,fromCratesLength-moveCount);
        crates[toStackIdx] = crates[toStackIdx] + cratesToMove;
      }   
    }

    for (int i=0; i<9; i++) {
      String crateString = crates[i];
      System.out.print(crateString.charAt(crateString.length()-1));
    }

    in.close();
  }
}
