// Day 10
// https://adventofcode.com/2022/day/10

import java.util.*;

public class Day10 {
  public static void main(String[] args){
    Scanner in = new Scanner(System.in);
    final int addxDelay = 2;
    int x = 1; int cycle = 0;
    Integer[] sampIntervals = {20, 60, 100, 140, 180, 220}; 
    int ptr = 0; int sampInt = sampIntervals[ptr];
    int sampValues = 0;
    
    while(in.hasNext()) {
      String line = in.nextLine();
      if (line.equals("q!")) break;

      String command = line.split(" ")[0];

      if (command.equals("noop")) {
        cycle++;
        if (cycle == sampInt) {
          sampValues += cycle*x; 
          if (ptr < sampIntervals.length-1) sampInt = sampIntervals[++ptr];
        }
      } else if (command.equals("addx")) {
        int value = Integer.parseInt(line.split(" ")[1]);

        for (int i=0; i < addxDelay; i++) {
          cycle++;
          if (cycle == sampInt) {
            sampValues += cycle*x; 
            if (ptr < sampIntervals.length-1) sampInt = sampIntervals[++ptr];
          }
        }
        x += value;
      }
    }

    System.out.print("Value: "); System.out.println(sampValues);
    in.close();
  }
}
