package Day11;
import java.util.*;

interface Operation {
    long updateWorry(long old);
}

public class Monkey {
    private long inspectionCount = 0;
    private ArrayList<Long> currentItems;
    private final ArrayList<Long> receivedItems = new ArrayList<Long>();
    private Operation operation;
    private int divTestQuot;
    private int worrySoothingQuot;
    private int commonFactor;
    private Monkey throwToIfTrue; private Monkey throwToIfFalse;

    public Monkey(
        final ArrayList<Long> startItems,
        final Operation operation,
        final int divTestQuot,
        final int worrySoothingQuot,
        final int commonFactor
    ) {
        this.currentItems = startItems;
        this.operation = operation;
        this.divTestQuot = divTestQuot;
        this.worrySoothingQuot = worrySoothingQuot;
        this.commonFactor = commonFactor;
    }

    public void setReceivingMonkeys(Monkey throwToIfTrue, Monkey throwToIfFalse) {
        this.throwToIfTrue = throwToIfTrue;
        this.throwToIfFalse = throwToIfFalse;
    }

    public void inspectAll() {
        currentItems.addAll(receivedItems);
        receivedItems.clear();

        for (int i=0; i < currentItems.size(); i++) {
            long worryLevel = currentItems.get(i);
            long updatedWorryLevel = updateWorry(worryLevel);
            boolean isDivisible = updatedWorryLevel % divTestQuot == 0;
            if (isDivisible) {
                throwToIfTrue.receive(updatedWorryLevel % commonFactor); // prevent worry level from spiralling to inf (Part 2)
            } else {
                throwToIfFalse.receive(updatedWorryLevel % commonFactor);
            };
        }
        inspectionCount += currentItems.size();
        currentItems.clear();
    }

    private long updateWorry(long currentWorry) {
        long updatedWorry = operation.updateWorry(currentWorry);
        return updatedWorry / this.worrySoothingQuot;
    }

    private void receive(long newItem) {
        receivedItems.add(newItem);
    }

    public long getInspectionCount() {
        return inspectionCount;
    }
}
