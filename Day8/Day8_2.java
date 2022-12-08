// Day 8 Part 2
// https://adventofcode.com/2022/day/8#part2

import java.util.*;

public class Day8_2 {
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

    int[][] scoreMap = new int[mapHeight][mapWidth]; 

    for (int j=0; j < mapWidth; j++) {
      for (int i=1; i < mapHeight; i++) {
        int score = 1;
        int curHeight = map.get(i).get(j);
        for (int k=i-1; k > 0; k--) {
          int treeHeight = map.get(k).get(j);
          if (treeHeight < curHeight) {
            score++;
          } else {break;}
        }
        scoreMap[i][j] += score; // initialise by adding value
      }
    }
    // scan down to up
    for (int j=0; j < mapWidth; j++) {
      for (int i=mapHeight-2; i >= 0; i--) {
        int score = 1;
        int curHeight = map.get(i).get(j);
        for (int k=i+1; k < mapHeight-1; k++) {
          int treeHeight = map.get(k).get(j);
          if (treeHeight < curHeight) {
            score++;
          } else {break;}
        }
        scoreMap[i][j] *= score;
      }
    }
    // scan left to right
    for (int i=0; i < mapHeight; i++) {
      for (int j=1; j < mapWidth; j++) {
        int score = 1;
        int curHeight = map.get(i).get(j);
        for (int k=j-1; k > 0; k--) {
          int treeHeight = map.get(i).get(k);
          if (treeHeight < curHeight) {
            score++;
          } else {break;}
        }
        scoreMap[i][j] *= score;
      }
    }
    // scan right to left
    for (int i=0; i < mapHeight; i++) {
      for (int j=mapWidth-2; j >= 0; j--) {
        int score = 1;
        int curHeight = map.get(i).get(j);
        for (int k=j+1; k < mapWidth-1; k++) {
          int treeHeight = map.get(i).get(k);
          if (treeHeight < curHeight) {
            score++;
          } else {break;}
        }
        scoreMap[i][j] *= score;
      }
    }

    // calculate best scenic score
    int bestScore = 0;
    for (int i = 0; i < mapHeight; i++) {
      for (int j = 0; j < mapWidth; j++) {
        int score = scoreMap[i][j];
        if (score > bestScore) {bestScore = score;}
      }
    }
    System.out.print("Best scenic score: "); System.out.println(bestScore);
    in.close();
  }
}
