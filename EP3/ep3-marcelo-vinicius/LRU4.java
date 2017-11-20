/*
 *  Exercício Programa 3 - Sistemas Operacionais
 *
 *  Marcelo Baiano Pastorino Trylesinski |  9297996
 *  Vinicius Perche de Toledo Agostini   |  4367487
 *
 */

public class LRU4 extends PagingManager {
    Page[] pages;
    int[] counter;

    public LRU4 (int virt, int p, int total) {
        super(virt, p, total);
        pages = new Page[numPages];
        counter = new int[numPages];
    }

    public int findFreePage() {
        for (int i = 0; i < numPages; i++)
            if (pages[i] == null)
                return i;
        return -1;
    }

    public int getLRUPage() {
        int max = 512;
        int idx = -1;
        for (int i = 0; i < numPages; i++)
            if (max > counter[i]) {
                idx = i;
                max = counter[i];
            }
        return idx;
    }

    public void updateCounter() {
        for (int i = 0; i < numPages; i++) {
            counter[i] >>>= 1;
            int R = (int) pages[i].getR();
            counter[i] += 256 * R;
        }
    }

    public void addPageFrame (Page p) {
        int idx = findFreePage();

        if (idx != -1) {
            pages[idx] = p;
            p.setPosPhysical(idx);
            counter[idx] = 0;
        } else {
            removePage();
            addPageFrame(p);
        }
    }

    public void removePage (int idx) {
        int aux = pageAddress[idx].getPosPhysical();
        if (aux != -1) {
            counter[aux] = 0;
            pages[aux] = null;
        }
    }

    public Page removePage() {
        int idx = getLRUPage();
        Page x = pages[idx];
        counter[idx] = 0;
        pages[idx].setPosPhysical(-1);
        pages[idx] = null;
        return x;
    }
}
