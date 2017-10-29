import java.util.BitSet;
import java.io.IOException;
//import java.io.RandomAccessFile;

public class BestFit extends FreeSpaceManager {
    // int allocUnitSize;           -- herdado de FreeSpaceManager
    // int blocks;                  -- herdado de FreeSpaceManager
    // int bitmapSize;
    // BitSet bitmap;
    // List<MemBlock> freeBlocks;   -- herdado de FreeSpaceManager
    // List<MemBlock> usedBlocks;   -- herdado de FreeSpaceManager

    public BestFit (int allocUnitSize, int memSize) {
        super(allocUnitSize, memSize);
    }

    /**
     * O algoritmo Best Fit, ao adicionar um novo processo, procura por um bloco
     * de memória que minimiza blockSize - p.size()
     */

    public void addProcess (Process p) {
        int i;
        int idx = -1;
        int min = this.units;

        for (i = 0; i < freeBlocks.size(); i++) {
            int blockSize = freeBlocks.get(i).size();
            if (blockSize >= p.size() && blockSize < min) {
                min = blockSize;
                idx = i;
            }
        }
        // Bloco i será ocupado pelo processo p
        MemBlock memBlock = freeBlocks.get(idx);
        for (i = 0; i < usedBlocks.size(); i++)
            if (memBlock.getBase() < usedBlocks.get(i).getLimit())
                break;
        usedBlocks.add(i, memBlock);

        // junta blocos quebrados que se tornaram contíguos eventualmente
        joinBlocks(usedBlocks, i-1);

        memBlock.setAddress(memBlock.getBase() + p.size(), memBlock.getLimit());
        if (freeBlocks.get(idx).full())
            freeBlocks.remove(idx);

        p.setAddress(memBlock.getBase(), memBlock.getBase() + p.size() - 1);
    }


    // Método para adicionar processo na implementação com BitSet
    //
    // public void add (Process p) {
    //     int j;
    //     int blockSize;
    //     int i = 0;
    //     int idx = -1;
    //     int min = this.bitmapSize;
    //
    //     while (i < this.bitmapSize) {
    //         while (this.bitmap.get(i))
    //             i++;
    //
    //         j = i;
    //
    //         while (!this.bitmap.get(j) && j < this.bitmapSize)
    //             j++;
    //
    //         blockSize = j - i - 1;
    //
    //         if (blockSize >= p.size() && blockSize < min) {
    //             min = blockSize;
    //             idx = i;
    //         }
    //         i = j;
    //     }
    //     this.bitmap.set(idx, idx + p.size(), true);
    //     p.setAddress(idx, idx + p.size());
    //     // write to memory file
    // }
}
