import java.util.List;
import java.util.LinkedList;

public class FIFO extends PagingManager {
    List<Page> pages;

    public FIFO (int virtual, int p, int physical) {
        super(virtual, p, physical);
        pages = new LinkedList<Page>();
    }

    // public int findFreePage () {
    //     if (pages.size() == n_pages)
    //         return -1;
    //     return 1;
    // }

    public void addPageFrame (Page p) {
        if (pages.size() == n_pages)
            removePage();
        pages.add(p);
        p.setPosPhysical(last);
    }

    public Page removePage() {
        return pages.remove();
    }

}
