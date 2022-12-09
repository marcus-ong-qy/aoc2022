// Day 9 Part 2
// https://adventofcode.com/2022/day/9#part2

import java.util.*;

public class Day9_2 {
  static int[] moveH(int[] hPos, char dir) {
    int xH = hPos[0]; int yH = hPos[1];
    int xHnew = xH; int yHnew = yH;

    if (dir == 'U') yHnew++;
    if (dir == 'D') yHnew--;
    if (dir == 'L') xHnew--;
    if (dir == 'R') xHnew++;

    int[] hNew = {xHnew, yHnew}; return hNew;
  }

  static int[] moveT(int[] hPos, int[] tPos) {
    int xH = hPos[0]; int yH = hPos[1];
    int xT = tPos[0]; int yT = tPos[1];
    int xTnew = xT; int yTnew = yT;

    if (xH - xT < -1 || (xH - xT < 0 && Math.abs(yH - yT) > 1)) xTnew--;
    if (xH - xT > 1  || (xH - xT > 0 && Math.abs(yH - yT) > 1)) xTnew++; 
    if (yH - yT < -1 || (yH - yT < 0 && Math.abs(xH - xT) > 1)) yTnew--;
    if (yH - yT > 1  || (yH - yT > 0 && Math.abs(xH - xT) > 1)) yTnew++; 

    int[] tNew = {xTnew, yTnew}; return tNew;
  }

  public static void main(String[] args){
    Scanner in = new Scanner(System.in);
    int[][] rope = {{0, 0}, {0, 0}, {0, 0}, {0, 0},
                            {0, 0}, {0, 0}, {0, 0},
                            {0, 0}, {0, 0}, {0, 0},};

    HashMap<Integer, Set<Integer>> tHistory = new HashMap<Integer, Set<Integer>>();
    tHistory.put(rope[0][0], new HashSet<Integer>(Arrays.asList(rope[0][1])));

    while(in.hasNext()) {
      String line = in.nextLine();
      if (line.equals("q!")) break;

      char dir = line.charAt(0);
      int steps = Integer.parseInt(line.split(" ")[1]);

      for (int i=0; i<steps; i++) {
        rope[0] = moveH(rope[0], dir);
        for (int j = 1; j < 10; j++) {
          rope[j] = moveT(rope[j-1], rope[j]);
        }

        if (tHistory.containsKey(rope[9][0])) {
          Set<Integer> updatedSet = tHistory.get(rope[9][0]);
          updatedSet.add(rope[9][1]);
          tHistory.put(rope[9][0], updatedSet);
        } else {
          tHistory.put(rope[9][0], new HashSet<Integer>(Arrays.asList(rope[9][1])));
        }
      }
    }

    // count how many unique locations Tail visited
    int count = 0;
    for (Integer key : tHistory.keySet()) {
      Set<Integer> set = tHistory.get(key);
      count += set.size();
    }

    System.out.print("Placed visited by Tail: "); System.out.println(count);
    in.close();
  }
}
