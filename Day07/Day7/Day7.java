// Day 7
// https://adventofcode.com/2022/day/7

// created with reference aid from https://github.com/ash42/adventofcode/blob/main/adventofcode2022/src/nl/michielgraat/adventofcode2022/day07/Directory.java
package Day7;
import java.util.*;

public class Day7 {
 
  public static void main(String[] args) throws Exception {
    Scanner in = new Scanner(System.in);
    final Directory root = new Directory("/", null);
    Directory currentDirectory = root;

    while(in.hasNext()) {
      String command = in.nextLine();
      if (command.equals("q!")) break;

      if (command.startsWith("$ cd")) {
        final String parameter = command.split(" ")[2];

        if (parameter.equals("..")) {
          currentDirectory = currentDirectory.getParent();
        }
        else if (parameter.equals("/")) {
          currentDirectory = root;
        }
        else {
          currentDirectory = currentDirectory.enterSubDirectory(parameter);
        }
      } 
      else if (command.startsWith("$ ls")) {
        // do nothing
      } 
      else if (command.startsWith("dir")) {
        final String subDirName = command.split(" ")[1];
        currentDirectory.addSubDirectory(subDirName);
      }
      else if (Character.isDigit(command.charAt(0))) {
        Integer fileSize = Integer.parseInt(command.split(" ")[0]);
        String fileName = command.split(" ")[1];
        currentDirectory.addFile(fileName, fileSize);
      }
    }

    // Part 1
    final int maxSizeToFind = 100000;
    int totalSizes = root.getTotalMaxSubDirSizes(maxSizeToFind);
    System.out.print("Total sizes: "); System.out.println(totalSizes);

    // Part 2
    final int totalDiskSpace = 70000000;
    final int spaceNeeded = 30000000;
    Integer sizeToDelete = root.getFileToDeleteSize(totalDiskSpace, spaceNeeded);
    System.out.print("Size to delete: "); System.out.println(sizeToDelete);

    in.close();
  }
}
