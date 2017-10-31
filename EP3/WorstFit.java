import java.util.BitSet;

public class WorstFit extends FreeSpaceManager {
    private BitSet bitmap;

    public WorstFit (int allocUnitSize, int memSize) {
        super(allocUnitSize, memSize);
    }

    public void add (Process p) {
        int i, j, idx, max, blockSize;
        i = 0;
        idx = -1;
        max = this.bitmapSize;

        while (i < this.bitmapSize) {
            while (this.bitmap.get(i++));

            j = i;

            while (!this.bitmap.get(j) && j < this.bitmapSize)
                j++;
            
            blockSize = j - i - 1;

            if (blockSize >= p.size() && blockSize > max) {
                max = blockSize;
                idx = i;
            }
            i = j;
        }
        this.bitmap.set(idx, idx + p.size(), true);
        p.setAddress(idx, idx + p.size());
        // write to memory file
    }
}