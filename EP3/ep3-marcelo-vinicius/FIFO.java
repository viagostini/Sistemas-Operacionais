/*
 *  Exercício Programa 3 - Sistemas Operacionais
 *
 *  Marcelo Baiano Pastorino Trylesinski |  9297996
 *  Vinicius Perche de Toledo Agostini   |  4367487
 *
 */

import java.util.List;
import java.util.LinkedList;

public class FIFO extends PagingManager {
    LinkedList<Page> pages;

    public FIFO (int virt, int p, int total) {
        super(virt, p, total);
        pages = new LinkedList<Page>();
    }

    public int findFreePage () {
        if (pages.size() == numPages)
            return -1;
        return 1;
    }

    public void addPageFrame (Page p) {
        int idx = findFreePage();
        if (idx != -1) {
            pages.add(p);
            p.setPosPhysical(pages.size()-1);
        }
        else {
            removePage();
            addPageFrame(p);
        }

    }

    public Page removePage() {
        return pages.remove();
    }

    public void removePage (int idx) {
        int aux = pageAddress[idx].getPosPhysical();
        if (aux != -1)
            pages.remove(aux);
    }

}
