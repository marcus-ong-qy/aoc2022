// Day 10 Part 2
// https://adventofcode.com/2022/day/10#part2

import java.util.*;

public class Day10_2 {
  public static void main(String[] args){
    Scanner in = new Scanner(System.in);
    final int addxDelay = 2;
    final int WIDTH = 40; final int HEIGHT = 6;
    int X = 1; int printPtr = -1;

    int[][] screen = new int[HEIGHT][WIDTH];
    
    while(in.hasNext()) {
      String line = in.nextLine();
      if (printPtr == WIDTH*HEIGHT-2) break;

      String command = line.split(" ")[0];

      if (command.equals("noop")) {
        printPtr++;
        int x = printPtr % WIDTH;
        if (Math.abs(x-X) < 2) {
          int y = printPtr/WIDTH; screen[y][x] = 1;
        }
      } else if (command.equals("addx")) {
        int value = Integer.parseInt(line.split(" ")[1]);

        for (int i=0; i < addxDelay; i++) {
          printPtr++;
          int x = printPtr % WIDTH;
          if (Math.abs(x-X) < 2) {
            int y = printPtr/WIDTH; screen[y][x] = 1;
          }
        }
        X += value;
      }
    }

    // print the screen
    for (int i=0; i<WIDTH*HEIGHT; i++) {
      int x = i % WIDTH; int y = i / WIDTH;
      char pix = screen[y][x] == 1 ? '#' : '.';

      if (x == 0) {System.out.println();}
      System.out.print(pix);
    }
    in.close();
  }
}
