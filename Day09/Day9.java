// Day 9
// https://adventofcode.com/2022/day/9

import java.util.*;

public class Day9 {
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
    int[] hPos = {0, 0}; int[] tPos = {0, 0};

    HashMap<Integer, Set<Integer>> tHistory = new HashMap<Integer, Set<Integer>>();
    tHistory.put(tPos[0], new HashSet<Integer>(Arrays.asList(tPos[1])));

    while(in.hasNext()) {
      String line = in.nextLine();
      if (line.equals("q!")) break;

      char dir = line.charAt(0);
      int steps = Integer.parseInt(line.split(" ")[1]);

      for (int i=0; i<steps; i++) {
        hPos = moveH(hPos, dir);
        tPos = moveT(hPos, tPos);

        if (tHistory.containsKey(tPos[0])) {
          Set<Integer> updatedSet = tHistory.get(tPos[0]);
          updatedSet.add(tPos[1]);
          tHistory.put(tPos[0], updatedSet);
        } else {
          tHistory.put(tPos[0], new HashSet<Integer>(Arrays.asList(tPos[1])));
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
