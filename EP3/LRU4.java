public class LRU4 extends PagingManager {
    Page[] freePages;
    int[] counter;

    public LRU (int virtual, int p, int physical) {
        super(virtual, p, physical);
        freePages = new Page[n_pages];
        counter = new int[n_pages];
    }

    public int findFreePage() {
        for (int i = 0; i < n_pages; i++)
            if (freePages[i] == null)
                return i;
        return -1;
    }

    public int getLRUPage() {
        int max = 512;
        int idx = -1;
        for (int i = 0; i < n_pages; i++)
            if (max > counter[i]) {
                idx = i;
                max = counter[i];
            }
        return idx;
    }

    public void updateCounter() {
        for (int i = 0; i < n_pages; i++) {
            counter[i] >>>= 1;
            int R = (int) freePages[i].getR();
            counter[i] += 256 * R;
        }
    }

    public void addPage (Page p) {
        int idx = findFreePage();

        if (idx != -1) {
            freePages[idx] = p;
            p.setPosPhysical(idx);
            counter[aux] = 0;
        } else {
            removePage();
            addPage(p);
        }
    }

    public void removePage (int idx) {
        int aux = pageAddress[idx].getPosPhysical();
        if (aux != -1) {
            counter[aux] = 0;
            freePages[aux] = null;
        }
    }

    public Page removePage() {
        int idx = getLRUPage();
        Page x = freePages[idx];
        counter[idx] = 0;
        freePages[idx].setPosPhysical(-1);
        freePages[idx] = null;
        return x;
    }
}
