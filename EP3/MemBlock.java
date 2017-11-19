public class MemBlock {
    private boolean isProcess;
    private int PID;
    private int base;
    private int limit;
    private int size;

    public MemBlock (int base, int limit) {
        this.base = base;
        this.limit = limit;
        size = limit - base + 1;
    }

    public int getBase() {
        return this.base;
    }

    public int getLimit() {
        return this.limit;
    }

    public int size() {
        return this.size;
    }

    public int getPID() {
        return this.PID;
    }

    public void setAddress (int base, int limit) {
        this.base = base;
        this.limit = limit;
    }

    public boolean full() {
        return this.base > this.limit;
    }
}
