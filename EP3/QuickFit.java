import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class QuickFit extends FreeSpaceManager {
    /**
    * O algoritmo Quick Fit mantém listas com blocos de memórias dos tamanhos
    * mais utilizados pelo caso de teste para agilizar esses acessos
    */
    private Map<Integer, List<MemBlock>> mostUsed;
    private final int n = 2;

    public QuickFit (int allocUnitSize, int memSize, List<Process> processes) {
        super(allocUnitSize, memSize);
        mostUsed = new HashMap<Integer, List<MemBlock>>(n+1, (float)1.0);

        List<AuxiliarClass> list = new ArrayList<AuxiliarClass>();
        // conta frequencia dos p.size()
        int[] freq = new int[10000000];
        for (Process p : processes)
            freq[p.size()]++;

        // cria os objetos auxiliares pra ordenar
        for (int i = 0; i < units; i++)
            if (freq[i] != 0)
                list.add(new AuxiliarClass(i, freq[i]));

        // ordena para descobrir os sizes mais comuns
        Collections.sort(list);

        // inicia as listas no hashmap para os sizes mais comuns
        // em mostUsed.get(size) existe uma lista vazia que terá blocos
        // de tamanho size
        for (int i = 0; i < n; i++)
            mostUsed.put(list.get(i).size, new ArrayList<MemBlock>());
    }

    public void addProcess (Process p) {
        int i;
        MemBlock memBlock;
        // verifica se existe um bloco livre de tamanho p.size()
        if (mostUsed.containsKey(p.size())
                    && !mostUsed.get(p.size()).isEmpty()) {
            // existe pelo menos um bloco de tamanho p.size()
            memBlock = mostUsed.get(p.size()).remove(0);
            for (i = 0; i < usedBlocks.size(); i++) {
                if (memBlock.getBase() > usedBlocks.get(i).getLimit()) {
                    break;
                }
            }
            usedBlocks.add(i, memBlock);
        } else {
            // não existe bloco livre de tamanho p.size()
            // usa Best Fit
            int idx = -1;
            int min = this.units;

            for (i = 0; i < freeBlocks.size(); i++) {
                int blockSize = freeBlocks.get(i).size();
                if (blockSize >= p.size() && blockSize <= min) {
                    min = blockSize;
                    idx = i;
                }
            }
            // Bloco idx será ocupado pelo processo p
            memBlock = freeBlocks.get(idx);
            for (i = 0; i < usedBlocks.size(); i++) {
                if (memBlock.getBase() > usedBlocks.get(i).getLimit()) {
                    break;
                }
            }
            usedBlocks.add(i, memBlock);
            freeBlocks.get(idx).setAddress(memBlock.getBase() + p.size(), memBlock.getLimit());
            if (freeBlocks.get(idx).full())
                freeBlocks.remove(idx);
        }
        // já adicionou novo bloco ao usedBlocks
        // junta blocos quebrados que se tornaram contíguos eventualmente
        joinBlocks(usedBlocks, i-1);
        p.setAddress(memBlock.getBase(), memBlock.getLimit());
        this.updateMemorySlots(p.getPID(), memBlock.getBase(), p.size());
    }

    @Override
    public void removeProcess (Process p) {
        int i;
        MemBlock memBlock;
        // acha bloco previamente ocupado por p e remove de usedBlocks
        for (i = 0; i < usedBlocks.size(); i++)
            if (usedBlocks.get(i).getBase() == p.base()) {
                break;
            }
        memBlock = usedBlocks.remove(i);
        // se o bloco tiver tamanho interessante para o QuickFit,
        // o bloco é adicionado ao HashMap
        if (mostUsed.containsKey(memBlock.size()))
            mostUsed.get(memBlock.size()).add(memBlock);
        else {
            //  se não, insere o bloco liberado em freeBlocks
            for (i = 0; i < freeBlocks.size(); i++) {
                if (memBlock.getBase() < freeBlocks.get(i).getLimit()) {
                    break;
                }
            }
            freeBlocks.add(i, memBlock);
            // junta blocos quebrados que se tornaram contíguos eventualmente
            joinBlocks(freeBlocks, i-1);
        }
        p.setAddress(-1, -1);
    }
}

class AuxiliarClass implements Comparable<AuxiliarClass> {
    int size;
    int freq;

    public AuxiliarClass (int size, int freq) {
        this.size = size;
        this.freq = freq;
    }

    @Override
    public int compareTo (final AuxiliarClass that) {
        return Integer.compare(that.freq, this.freq);
    }
}
