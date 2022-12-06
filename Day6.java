// Day 6
// https://adventofcode.com/2022/day/6
import java.util.*;
import java.io.*;

public class Day6 {
  static boolean checkMarker(String substr) {
    for (int i=0; i<3; i++) {
      for (int j=i+1; j<4; j++) {
        if (substr.charAt(i) == substr.charAt(j)) {
          return false;
        }
      }
    }
    return true;
  }
  
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
 
    while(in.hasNext()) {
      String stream = in.nextLine();
      if (stream.equals("q!")) break;

      for (int i=0; i<stream.length()-3; i++) {
        boolean isMarker = checkMarker(stream.substring(i,i+4));
        if (isMarker) {
          System.out.println(i+4); break;
        }
      }
    }
    in.close();
  }
}
