

public class Event implements Comparable<Event> {
    private final int t;
    private final int pos;
    private final Process p;
    // se o typeEvent = 0 : o processo chegou na memoria virtual
    // se o typeEvent = 1 : o processo chegou na memoria fisica
    // se o typeEvent = 2 : compactar
    // se o typeEvent = 3 : o processo saiu da memoria virtual
    private final int typeEvent;

    public Event (Process p, int t, int pos) {
        this.t = t;
        this.p = p;
        this.pos = pos;
        this.typeEvent = 1;
    }

    // Evento caso seja o comando 't COMPACTAR'
    public Event (int t) {
        this.t = t;
        this.p = null;
        this.pos = -1;
        this.typeEvent = 2;
    }

    // se in == true => o processo esta chegando na memoria virtual
    // se in == false => o processo esta saindo da memoria virtual
    public Event (Process p, int t, boolean in) {
        this.t = t;
        this.p = p;
        this.pos = -1;
        if (in)
            this.typeEvent = 0;
        else
            this.typeEvent = 3;
    }

    public int getT() {
        return this.t;
    }

    public int getPos() {
        return this.pos;
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
