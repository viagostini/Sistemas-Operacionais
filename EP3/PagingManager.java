public abstract class PagingManager {
    Page[] pageAddress;
    int size;
    int n_pages;
    int v;
    int t;

    public PagingManager (int virtual, int p, int physical) {
        this.v = virtual;
        this.n_pages = physical / p;
        this.size = p;
        this.pageAddress = new Page[virtual/p];
    }

    public abstract void addPage (Page p);
    public abstract Page removePage ();
    //public abstract void add_pg_to_free_space(int address, Page p);
    //public abstract void terminate_page(int pg_index);

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
            pg.setPhysical(-1);
            pg.setVirtual(-1);
        }
    }

    public int requestPageFrame (int address) {

    }

}
