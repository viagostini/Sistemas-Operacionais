import java.util.List;
import java.util.LinkedList;
import java.io.RandomAccessFile;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.File;

public abstract class FreeSpaceManager {
    protected int allocUnitSize;
    protected int units;
    protected List<MemBlock> freeBlocks;
    protected List<MemBlock> usedBlocks;
    protected RandomAccessFile fmem, vmem;

    public FreeSpaceManager (int allocUnitSize, int memSize) {
        this.allocUnitSize = allocUnitSize;
        freeBlocks = new LinkedList<MemBlock>();
        usedBlocks = new LinkedList<MemBlock>();
        units = memSize/allocUnitSize;
        freeBlocks.add(new MemBlock(0, units-1));
        this.createMemoryFiles();
    }

    // Depende do algoritmo de gerenciamento de memória
    abstract void addProcess (Process p);

    protected void removeProcess (Process p) {
        int i;
        // acha bloco previamente ocupado por p e remove de usedBlocks
        for (i = 0; i < usedBlocks.size(); i++)
            if (usedBlocks.get(i).getBase() == p.base())
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

    protected void createMemoryFiles () {
        try {
            fmem = new RandomAccessFile("/tmp/ep3.mem", "rw");
            vmem = new RandomAccessFile("/tmp/ep3.vir", "rw");

            for (int i = 0; i < units; i++)
                fmem.writeInt (-1);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    protected void updateMemorySlots (int pid, int base, int size) {
        try {
            fmem.seek(base * 4);
            for (int i = 0; i < size; i++)
                fmem.writeInt (pid);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    protected void updateVirtualSlots (int pid, int base, int size) {
        try {
            vmem.seek(base * 4);
            for (int i = 0; i < size; i++)
                vmem.writeInt (pid);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    protected void printMemoryFile () {
        try {
            fmem.seek(0);
            for (int i = 0; i < units; i++)
                System.out.print(fmem.readInt() + " ");
            System.out.println();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    protected void deleteMemoryFiles() {
        try {
            fmem.close();
            vmem.close();
            File fm = new File("/tmp/ep3.mem");
            File vm = new File("/tmp/ep3.vir");
            fm.delete();
            vm.delete();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Compacta a memória física
    protected void compactMemory() {
        int pos = 0;
        for (MemBlock m : this.usedBlocks) {
            this.updateMemorySlots(-1, m.getBase(), m.size());
            m.setAddress(pos, m.size() + pos - 1);
            this.updateMemorySlots(m.getPID(), m.getBase(), m.size());
            pos += m.size();
        }
    }

    protected void printMemBlocks() {
        System.out.println("Espaços livres: ");
        System.out.println("(PID, Base, Limit)");
        for (MemBlock m : freeBlocks)
            System.out.printf("(%3d, %4d, %5d)\n", m.getPID(), m.getBase(), m.getLimit());

        System.out.println("Espaços usados: ");
        System.out.println("(PID, Base, Limit)");
        for (MemBlock m : usedBlocks)
            System.out.printf("(%3d, %4d, %5d)\n", m.getPID(), m.getBase(), m.getLimit());
    }
}
