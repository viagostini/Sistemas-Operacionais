

public class Event implements Comparable<Event> {
    private final int t;
    private final int pos;
    private final Process p;
    private final boolean needCompact;


    public Event (Process p, int t, int pos) {
        this.t = t;
        this.p = p;
        this.pos = pos;
        this.needCompact = false;
    }

    // Evento caso seja o comando 't COMPACTAR'
    public Event (int t) {
        this.t = t;
        this.p = null;
        this.pos = -1;
        this.needCompact = true;
    }

    public int getT() {
        return this.t;
    }

    public Process getP() {
        return this.p;
    }

    public boolean getCompact() {
        return this.needCompact;
    }

    public int compareTo (Event that) {
        if (this.t == that.getT())
            return this.p.getPID() - that.getP().getPID();
        return this.t - that.getT();
    }
}
