

public class Event implements Comparable<Event> {
    private final int t;
    private final int pos;
    private final Process p;


    public Event (Process p, int t, int pos) {
        this.t = t;
        this.p = p;
        this.pos = pos;
    }

    public int getT() {
        return this.t;
    }

    public Process getP() {
        return this.p;
    }

    public int compareTo (Event that) {
        if (this.t == that.getT())
            return this.p.getPID() - that.getP().getPID();
        return this.t - that.getT();
    }
}
