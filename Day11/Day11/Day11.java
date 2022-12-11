// Day 11
// https://adventofcode.com/2022/day/11

package Day11;
import java.util.*;

public class Day11 {
  public static void main(String[] args){
    final int rounds = Integer.parseInt(args[0]);
    final int worrySoothingQuot = Integer.parseInt(args[1]);
    final int[] divTestQuots = {7, 11, 13, 3, 17, 2, 5, 19};

    // find common factor of all divTestQuots to prevent numbers from spiralling to infinity (Part 2)
    int commonFactor = 1; for (int quot : divTestQuots) {commonFactor*=quot;}

    Monkey M0 = new Monkey(
      new ArrayList<Long>(Arrays.asList(63L, 57L)),
      new Operation() {
        public long updateWorry(long old) {
          return old*11;
        }
      }, divTestQuots[0], worrySoothingQuot, commonFactor
    );

    Monkey M1 = new Monkey(
      new ArrayList<Long>(Arrays.asList(82L, 66L, 87L, 78L, 77L, 92L, 83L)),
      new Operation() {
        public long updateWorry(long old) {
          return old+1;
        }
      }, divTestQuots[1], worrySoothingQuot, commonFactor
    );

    Monkey M2 = new Monkey(
      new ArrayList<Long>(Arrays.asList(97L, 53L, 53L, 85L, 58L, 54L)),
      new Operation() {
        public long updateWorry(long old) {
          return old*7;
        }
      }, divTestQuots[2], worrySoothingQuot, commonFactor
    );

    Monkey M3 = new Monkey(
      new ArrayList<Long>(Arrays.asList(50L)),
      new Operation() {
        public long updateWorry(long old) {
          return old+3;
        }
      }, divTestQuots[3], worrySoothingQuot, commonFactor
    );

    Monkey M4 = new Monkey(
      new ArrayList<Long>(Arrays.asList(64L, 69L, 52L, 65L, 73L)),
      new Operation() {
        public long updateWorry(long old) {
          return old+6;
        }
      }, divTestQuots[4], worrySoothingQuot, commonFactor
    );

    Monkey M5 = new Monkey(
      new ArrayList<Long>(Arrays.asList(57L, 91L, 65L)),
      new Operation() {
        public long updateWorry(long old) {
          return old+5;
        }
      }, divTestQuots[5], worrySoothingQuot, commonFactor
    );

    Monkey M6 = new Monkey(
      new ArrayList<Long>(Arrays.asList(67L, 91L, 84L, 78L, 60L, 69L, 99L, 83L)),
      new Operation() {
        public long updateWorry(long old) {
          return old*old;
        }
      }, divTestQuots[6], worrySoothingQuot, commonFactor
    );

    Monkey M7 = new Monkey(
      new ArrayList<Long>(Arrays.asList(58L, 78L, 69L, 65L)),
      new Operation() {
        public long updateWorry(long old) {
          return old+7;
        }
      }, divTestQuots[7], worrySoothingQuot, commonFactor
    );

    M0.setReceivingMonkeys(M6, M2);
    M1.setReceivingMonkeys(M5, M0);
    M2.setReceivingMonkeys(M4, M3);
    M3.setReceivingMonkeys(M1, M7);
    M4.setReceivingMonkeys(M3, M7);
    M5.setReceivingMonkeys(M0, M6);
    M6.setReceivingMonkeys(M2, M4);
    M7.setReceivingMonkeys(M5, M1);
    final Monkey[] monkeys = {M0, M1, M2, M3, M4, M5, M6, M7};

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
