public abstract class PagingManager {
    Page[] pageAddress;
    int size;
    int n_pages;
    int v;
    int t;

    public PagingManager (int virtual, int p, int physical) {
        this.v = virtual;
        this.n_pages
    }

    public abstract void addPage (Page p);
    public abstract Page removePage ();
    //public abstract void add_pg_to_free_space(int address, Page p);
    //public abstract void terminate_page(int pg_index);

    public int virtualToPhysical(int v_address) {
        int aux = v_address / size;
        if (page_Address[aux].getPhysical() == -1)
            return -1;
        else
            return (page_Address[aux].getPhysical() * size + v_address % size);
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

    public void removeProcess (Process p);

    public int requestPageFrame (int address);

    public void compactMemory();

}
