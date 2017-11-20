/*
 *  Exercício Programa 3 - Sistemas Operacionais
 *
 *  Marcelo Baiano Pastorino Trylesinski |  9297996
 *  Vinicius Perche de Toledo Agostini   |  4367487
 *
 */

public abstract class PagingManager {
    Page[] pageAddress;
    int size;
    int numPages;
    int v;
    int t;

    public PagingManager (int virt, int p, int total) {
        this.v = virt;
        this.numPages = total / p;
        this.size = p;
        this.pageAddress = new Page[virt/p];
    }

    public abstract void addPageFrame (Page p);
    public abstract Page removePage ();
    public abstract void removePage (int idx);
    public abstract int findFreePage();

    public int virtualToPhysical(int v_address) {
        int aux = v_address / size;
        if (pageAddress[aux].getPosPhysical() == -1)
            return -1;
        else
            return (pageAddress[aux].getPosPhysical() * size + v_address % size);
    }

    public void insertPage (Page p) {
        for (int i = 0; i < (v / size); i++)
            if (pageAddress[i] == null) {
                pageAddress[i] = p;
                p.setPosVirtual(i);
            }
    }

    public void resetBitR () {
        for (Page p : pageAddress)
            p.setR(false);
    }

    public void compactMemory () {
        for (int i = 0; i < (v / size); i++) {
            if (pageAddress[i] == null) {
                for (int j = i + 1; j < (v / size); j++) {

                }
            }
        }
    }

    public void removeProcess (Process p) {
        for(Page pg : p.getPages()) {
            removePage(pg.getPosVirtual());
            pageAddress[pg.getPosVirtual()] = null;
            pg.setPosPhysical(-1);
            pg.setPosVirtual(-1);
        }
    }


    public int requestPageFrame (int address) {
        int aux = virtualToPhysical(address);

        if (aux != -1) {
            pageAddress[address / size].setR(true);
            return aux;
        } else {
            if(findFreePage() == -1)
                addPageFrame(pageAddress[address / size]);
            pageAddress[address / size].setR(true);
            return virtualToPhysical(address);
       }
    }

}
