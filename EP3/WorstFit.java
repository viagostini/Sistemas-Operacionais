public class WorstFit extends FreeSpaceManager {

    public WorstFit (int allocUnitSize, int memSize) {
        super(allocUnitSize, memSize);
    }

    public void addProcess (Process p) {
        int i;
        int idx = -1;
        int max = -1;

        for (i = 0; i < freeBlocks.size(); i++) {
            int blockSize = freeBlocks.get(i).size();
            if (blockSize >= p.size() && blockSize >= max) {
                min = blockSize;
                idx = i;
            }
        }
        // Bloco idx será ocupado pelo processo p
        MemBlock memBlock = freeBlocks.get(idx);
        for (i = 0; i < usedBlocks.size(); i++)
            if (memBlock.getBase() > usedBlocks.get(i).getLimit())
                break;
        usedBlocks.add(i, memBlock);

        // junta blocos quebrados que se tornaram contíguos eventualmente
        joinBlocks(usedBlocks, i-1);

        memBlock.setAddress(memBlock.getBase() + p.size(), memBlock.getLimit());
        if (freeBlocks.get(idx).full())
            freeBlocks.remove(idx);

        p.setAddress(memBlock.getBase(), memBlock.getLimit());
        // write to memory file
    }
}
