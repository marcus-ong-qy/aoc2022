// Day 6 Part 2
// https://adventofcode.com/2022/day/6#part2
import java.util.*;
import java.io.*;

public class Day6_2 {
  static boolean checkMarker(String substr, int markerLength) {
    for (int i=0; i<markerLength-1; i++) {
      for (int j=i+1; j<markerLength; j++) {
        if (substr.charAt(i) == substr.charAt(j)) {
          return false;
        }
      }
    }
    return true;
  }
  
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int markerLength = 14;

    while(in.hasNext()) {
      String stream = in.nextLine();
      if (stream.equals("q!")) break;

      for (int i=0; i<stream.length()-markerLength-1; i++) {
        boolean isMarker = checkMarker(stream.substring(i,i+markerLength), markerLength);

        if (isMarker) {
          System.out.println(i+markerLength); break;
        }
      }
    }
    in.close();
  }
}
