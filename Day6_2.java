// Day 6 Part 2
// https://adventofcode.com/2022/day/6#part2
import java.util.*;
import java.io.*;

public class Day6_2 {
  static int checkMarker(String substr) {
    int markerLength = substr.length();
    for (int i=0; i < markerLength-1; i++) {
      for (int j=i+1; j < markerLength; j++) {
        if (substr.charAt(i) == substr.charAt(j)) return i;
      }
    }
    return -1;
  }
  
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int markerLength = 14;
    int counter = 0;

    while(in.hasNext()) {
      String stream = in.nextLine();
      if (stream.equals("q!")) break;

      while (counter < stream.length() - markerLength - 1) {
        int duplicateMarker = checkMarker(
          stream.substring(counter, counter + markerLength)
        );

        if (duplicateMarker == -1) {
          System.out.println(counter + markerLength); break;
        } else {
          counter += duplicateMarker + 1;
        }
      }
    }
    in.close();
  }
}
