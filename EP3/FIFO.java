public class FIFO extends PagingManager {
    int last = -1;
    Page[] pages;

    public FIFO (int virtual, int p, int physical) {
        super(virtual, p, physical);
        pages = new Page[n_pages];
    }

    public int findFreePage () {
        if (last == pages.length-1)
            return -1;

        return ++last;
    }

    public void addPageFrame (Page p) {
        if (last == n_pages - 1)
            removePageFrame();
        pages[idx] = ++last;
        p.setPosPhysical(last);
    }

    public Page removePageFrame() {
        last--;
        return pages.remove(0);
    }

}
