// Day 11 Part 2
// https://adventofcode.com/2022/day/11#part2

package Day11;
import java.util.*;

public class Day11sample {
  public static void main(String[] args){
    final int rounds = Integer.parseInt(args[0]);
    final int worrySoothingQuot = Integer.parseInt(args[1]);
    final int[] divTestQuots = {23, 19, 13, 17};
    int commonFactor = 1; for (int quot : divTestQuots) {commonFactor*=quot;}

    Monkey M0 = new Monkey(
      new ArrayList<Long>(Arrays.asList(79L, 98L)),
      new Operation() {
        public long updateWorry(long old) {
          return old*19;
        }
      }, divTestQuots[0], worrySoothingQuot, commonFactor
    );

    Monkey M1 = new Monkey(
      new ArrayList<Long>(Arrays.asList(54L, 65L, 75L, 74L)),
      new Operation() {
        public long updateWorry(long old) {
          return old+6;
        }
      }, divTestQuots[0], worrySoothingQuot, commonFactor
    );

    Monkey M2 = new Monkey(
      new ArrayList<Long>(Arrays.asList(79L, 60L, 97L)),
      new Operation() {
        public long updateWorry(long old) {
          return old*old;
        }
      }, divTestQuots[0], worrySoothingQuot, commonFactor
    );

    Monkey M3 = new Monkey(
      new ArrayList<Long>(Arrays.asList(74L)),
      new Operation() {
        public long updateWorry(long old) {
          return old+3;
        }
      }, divTestQuots[0], worrySoothingQuot, commonFactor
    );

    M0.setReceivingMonkeys(M2, M3);
    M1.setReceivingMonkeys(M2, M0);
    M2.setReceivingMonkeys(M1, M3);
    M3.setReceivingMonkeys(M0, M1);
    final Monkey[] monkeys = {M0, M1, M2, M3};

    // simulate monkeys
    for (int n=0; n<rounds; n++) {
      for (int m=0; m<monkeys.length; m++) {
        monkeys[m].inspectAll();
      }
    }

    long mostBizMonkey = 0;
    long secondMostBizMonkey = 0;

    for (int m=0; m<monkeys.length; m++) {
      long bizCount = monkeys[m].getInspectionCount();
      if (bizCount > mostBizMonkey) {
        secondMostBizMonkey = mostBizMonkey;
        mostBizMonkey = bizCount;
      } else if (bizCount > secondMostBizMonkey) {
        secondMostBizMonkey = bizCount;
      }
    }

    System.out.println(mostBizMonkey);
    System.out.println(secondMostBizMonkey);
    long totalMonkeyBiz = mostBizMonkey*secondMostBizMonkey;
    System.out.print("Total Monkey Business: "); System.out.println(totalMonkeyBiz);
  }
}
