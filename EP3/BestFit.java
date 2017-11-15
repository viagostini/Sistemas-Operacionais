import java.util.BitSet;
// import java.io.IOException;
// import java.io.RandomAccessFile;

public class BestFit extends FreeSpaceManager {
    int bitmapSize;
    BitSet bitmap;

    public BestFit (int allocUnitSize, int memSize) {
        super(allocUnitSize, memSize);
    }

    public void add (Process p) {
        int j;
        int blockSize;
        int i = 0;
        int idx = -1;
        int min = this.bitmapSize;

        while (i < this.bitmapSize) {
            while (this.bitmap.get(i))
                i++;

            j = i;
    
            while (!this.bitmap.get(j) && j < this.bitmapSize)
                j++;

            // talvez precise de - 1
            blockSize = j - i;

            if (blockSize >= p.size() && blockSize < min) {
                min = blockSize;
                idx = i;
            }
            i = j;
        }
        this.bitmap.set(idx, idx + p.size(), true);
        p.setAddress(idx, idx + p.size());
        // write to memory file
    }
}
