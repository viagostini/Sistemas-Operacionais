import java.util.List;

public class Optimal extends PagingManager {
    Page[] freePages;
    List<Event> events;

    public Optimal (int virtual, int p, int physical, List<Event> events) {
        super(virtual, p, physical);
        this.freePages = new Page[n_pages];
        this.events = events;
    }

    // procura na lista de eventos a página física cujo próximo acesso está
    // mais distante do tempo atual
    public int getOptimalRemoval() {
        boolean check[] = new boolean[n_pages];
        int counter = 0;
        int i = 0;
        for (Event e : events) {
            if (e.getT() >= time) {
                int aux = e.getP().pages.get(e.getAccess()%size).getPhysical();
                if (e.getAccess() >= 0 && check[aux] == false && aux != -1) {
                    check[aux] = true;
                    counter++;
                }
                if (counter >= aux-1)
                    break;
            }
        }
        while (check[i] != false) {
            if (i >= n_pages)
                return 0;
            i++;
        }
        return i;
    }

    public int findFreePage() {
        for (int i = 0; i < n_pages; i++)
            if (freePages == null)
                return i;
        return -1;
    }

    public void addPageFrame (Page p) {
        int idx = findFreePage();

        if (idx != -1) {
            freePages[idx] = p;
            p.setPosPhysical(idx);
        } else {
            removePage();
            addPageFrame(p);
        }
    }

    public Page removePage() {
        int idx = getOptimalRemoval();
        Page x = freePages[idx];
        freePages[idx].setPosPhysical(-1);
        free[idx] = null;
        return x;
    }

    public void removePage (int idx) {
        int aux = pageAddress[idx].getPosPhysical();
        if (aux != -1)
            freePages[aux] = null;
    }
}
