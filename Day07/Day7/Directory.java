// created with reference aid from https://github.com/ash42/adventofcode/blob/main/adventofcode2022/src/nl/michielgraat/adventofcode2022/day07/Directory.java
package Day7;
import java.util.*;

public class Directory {
    private final String name;
    private Directory parent = null;
    private final List<Directory> subDirectories = new ArrayList<>();
    private final Map<String, Integer> files = new HashMap<>();

    public int totalMaxSubDirSizes = 0; // total size of all subdirectories found with min size
    public Integer sizeToDelete = Integer.MAX_VALUE; // Part 2

    public Directory(final String name, final Directory parent) {
        this.name = name;
        this.parent = parent;
    }

    public int getSize() {
        int size = 0;
        for (Directory subDir : subDirectories) size += subDir.getSize();
        for (Integer fileSize : files.values()) size += fileSize;
        return size;
    }

    private int getAllSizeByThreshold(int threshold, Directory root) {
        int size = 0;
        for (Directory subDir : subDirectories) {
            int subDirSize = subDir.getAllSizeByThreshold(threshold, root);
            if (subDirSize <= threshold) {
                root.totalMaxSubDirSizes += subDirSize;
            }
            size += subDirSize;
        }
        for (Integer fileSize : files.values()) {
            size += fileSize;
        }
        return size;
    }

    public int getTotalMaxSubDirSizes(int threshold) {
        getAllSizeByThreshold(threshold, this);
        return this.totalMaxSubDirSizes;
    }

    private Integer getMinSubDirSizeByThreshold(int threshold, Directory root) {
        int size = 0;
        for (Directory subDir : subDirectories) {
            Integer subDirSize = subDir.getMinSubDirSizeByThreshold(threshold, root);
            if (subDirSize >= threshold && subDirSize < root.sizeToDelete) {
                root.sizeToDelete = subDirSize;
            }
            size += subDirSize;
        }
        for (Integer fileSize : files.values()) {
            size += fileSize;
        }
        return size;
    }

    public Integer getFileToDeleteSize(int totalDiskSpace, int spaceNeeded) {
        int spaceNeededToClear = spaceNeeded - (totalDiskSpace - this.getSize());
        getMinSubDirSizeByThreshold(spaceNeededToClear, this);
        return this.sizeToDelete;
    }

    public void addSubDirectory(String subDirname) {
        subDirectories.add(new Directory(subDirname, this));
    }

    public void addFile(String fileName, Integer fileSize) {
        files.put(fileName, fileSize);
    }

    public void setParent(Directory parentDir) {
        this.parent = parentDir;
    }

    public Directory enterSubDirectory(String targetSubDirName) throws Exception {
        for (Directory subDir : subDirectories) {
            if (subDir.getName().equals(targetSubDirName)) return subDir;
        }
        throw new Exception("cd command invalid - subdir " + targetSubDirName + " not found");
    }

    public Directory getParent() {return this.parent;}

    public String getName() {return this.name;}
}
