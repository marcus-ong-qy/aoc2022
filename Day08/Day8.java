// Day 8
// https://adventofcode.com/2022/day/8

import java.util.*;

public class Day8 {
  public static void main(String[] args) throws Exception {
    Scanner in = new Scanner(System.in);
    ArrayList<ArrayList<Integer>> map = new ArrayList<ArrayList<Integer>>();

    while(in.hasNext()) {
      String line = in.nextLine();
      if (line.equals("q!")) break;

      ArrayList<Integer> row = new ArrayList<Integer>();

      for (int i=0; i < line.length(); i++) {
        char tree = line.charAt(i);
        int treeVal = tree - '0';
        row.add(treeVal);
      }
      map.add(row);
    }

    int mapWidth = map.get(0).size();
    int mapHeight = map.size();

    int[][] binMap = new int[mapHeight][mapWidth]; 
    binMap[0][0] = 1; binMap[0][mapWidth-1] = 1; binMap[mapWidth-1][0] = 1; binMap[mapWidth-1][mapWidth-1] = 1;

    // scan up to down
    for (int j=1; j < mapWidth-1; j++) {
      int tallest = -1;
      for (int i=0; i < mapHeight; i++) {
        int curHeight = map.get(i).get(j);
        if (curHeight > tallest) {
          binMap[i][j] = 1;
          if (curHeight == 9) break;
          tallest = curHeight;
        }
      }
    }
    // scan down to up
    for (int j=1; j < mapWidth-1; j++) {
      int tallest = -1;
      for (int i=mapHeight-1; i >= 0; i--) {
        int curHeight = map.get(i).get(j);
        if (curHeight > tallest) {
          binMap[i][j] = 1;
          if (curHeight == 9) break;
          tallest = curHeight;
        }
      }
    }
    // scan left to right
    for (int i=1; i < mapHeight-1; i++) {
      int tallest = -1;
      for (int j=0; j < mapWidth; j++) {
        int curHeight = map.get(i).get(j);
        if (curHeight > tallest) {
          binMap[i][j] = 1;
          if (curHeight == 9) break;
          tallest = curHeight;
        }
      }
    }
    // scan right to left
    for (int i=1; i < mapHeight-1; i++) {
      int tallest = -1;
      for (int j=mapWidth-1; j >= 0; j--) {
        int curHeight = map.get(i).get(j);
        if (curHeight > tallest) {
          binMap[i][j] = 1;
          if (curHeight == 9) break;
          tallest = curHeight;
        }
      }
    }

    // count number of ones
    int visibleTrees = 0;
    for (int i = 0; i < mapHeight; i++) {
      for (int j = 0; j < mapWidth; j++) {
        visibleTrees += binMap[i][j];
      }
    }
    System.out.print("Visible trees: "); System.out.println(visibleTrees);

    in.close();
  }
}
