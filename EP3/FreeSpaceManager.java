import java.util.BitSet;

public abstract class FreeSpaceManager {
    protected int allocUnitSize;
    protected int units;
    protected int bitmapSize;
    protected BitSet bitmap;

    public FreeSpaceManager (int allocUnitSize, int memSize) {
        this.allocUnitSize = allocUnitSize;
        this.bitmapSize = (int) Math.ceil(memSize / allocUnitSize);
        bitmap = new BitSet(this.bitmapSize);
        bitmap.set(0, bitmapSize, false);
    }

    // Depende do algoritmo de gerenciamento de memória
    abstract void addProcess (Process p);

    protected void removeProcess (Process p) {
        this.bitmap.set(p.getBase(), p.getBase() + p.size(), false);
    }
}