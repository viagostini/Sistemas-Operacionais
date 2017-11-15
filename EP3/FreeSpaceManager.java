import java.util.List;
import java.util.LinkedList;

public abstract class FreeSpaceManager {
    protected int allocUnitSize;
    protected int units;
    protected List<MemBlock> freeBlocks;
    protected List<MemBlock> usedBlocks;

    public FreeSpaceManager (int allocUnitSize, int memSize) {
        this.allocUnitSize = allocUnitSize;
        freeBlocks = new LinkedList<>();
        usedBlocks = new LinkedList<>();
        units = memSize/allocUnitSize;
        freeBlocks.add(new MemBlock(0, units-1));
    }

    // Depende do algoritmo de gerenciamento de memória
    abstract void addProcess (Process p);

    protected void removeProcess (Process p) {
        int i;
        // acha bloco previamente ocupado por p e remove de usedBlocks
        for (i = 0; i < usedBlocks.size(); i++)
            if (usedBlocks.get(i).getBase() == p.getBase())
                break;
        MemBlock memBlock = usedBlocks.remove(i);

        // insere o bloco liberado em freeBlocks
        for (i = 0; i < freeBlocks.size(); i++)
            if (memBlock.getBase() < freeBlocks.get(i).getLimit())
                break;
        freeBlocks.add(i, memBlock);

        // junta blocos quebrados que se tornaram contíguos eventualmente
        joinBlocks(freeBlocks, i-1);

        p.setAddress(-1, -1);
    }

    protected void joinBlocks (List<MemBlock> list, int idx) {
        int i = 0;
        while (i < list.size()-1) {
            while (list.get(i+1).getBase() == list.get(i).getLimit() + 1) {
                // remove list(i) e list(i+1) e adiciona o novo bloco
                MemBlock memBlock = new MemBlock(list.get(i).getBase(),
                                                 list.get(i+1).getLimit());
                list.remove(i);
                list.remove(i+1);
                list.add(i, memBlock);
            }
        }
        i++;
    }
}
