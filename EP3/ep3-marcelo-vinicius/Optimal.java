/*
 *  Exercício Programa 3 - Sistemas Operacionais
 *
 *  Marcelo Baiano Pastorino Trylesinski |  9297996
 *  Vinicius Perche de Toledo Agostini   |  4367487
 *
 */

import java.util.List;

public class Optimal extends PagingManager {
    Page[] pages;
    List<Event> events;

    public Optimal (int virt, int p, int total, List<Event> events) {
        super(virt, p, total);
        this.pages = new Page[numPages];
        this.events = events;
    }

    // procura na lista de eventos a página física cujo próximo acesso está
    // mais distante do tempo atual
    public int getOptimalRemoval() {
        boolean check[] = new boolean[numPages];
        int counter = 0;
        int i = 0;
        for (Event e : events) {
            if (e.getT() >= t) {
                int aux = e.getP().getPage(e.getPos()%size).getPosPhysical();
                if (e.getTypeEvent() == 1 && check[aux] == false && aux != -1) {
                    check[aux] = true;
                    counter++;
                }
                if (counter >= aux-1)
                    break;
            }
        }
        while (check[i] != false) {
            if (i >= numPages)
                return 0;
            i++;
        }
        return i;
    }

    public int findFreePage() {
        for (int i = 0; i < numPages; i++)
            if (pages == null)
                return i;
        return -1;
    }

    public void addPageFrame (Page p) {
        int idx = findFreePage();

        if (idx != -1) {
            pages[idx] = p;
            p.setPosPhysical(idx);
        } else {
            removePage();
            addPageFrame(p);
        }
    }

    public Page removePage() {
        int idx = getOptimalRemoval();
        Page x = pages[idx];
        pages[idx].setPosPhysical(-1);
        pages[idx] = null;
        return x;
    }

    public void removePage (int idx) {
        int aux = pageAddress[idx].getPosPhysical();
        if (aux != -1)
            pages[aux] = null;
    }
}
