import java.util.List;
import java.util.ArrayList;

public class Process {
    private static int _PID = 0;

    private int PID;
    private int size;
    private int t0;
    private int tf;
    private int base;
    private int limit;
    private String name;
    private List<Integer> ps;
    private List<Integer> ts;
    //private List<Page> pages;

	public Process(String name, int t0, int tf, int size) {
		this.PID = ++_PID;
		this.t0 = t0;
		this.tf = tf;
        this.size = size;
		this.name = name;
		this.ps = new ArrayList<>();
		this.ts = new ArrayList<>();
        //this.pages = new ArrayList<>();
	}

    /**
	* Adiciona um novo evento deste processo
	*/
    public void insertEvent (int pi, int ti) {
        this.ps.add(pi);
        this.ts.add(ti);
    }

    /**
	* Altera o valor da base e limite do espaço de endereço do processo
	*/
    public void setAddress (int base, int limit) {
        this.base = base;
        this.limit = limit;
    }

	/**
	* Devolve o valor do PID do processo
	*/
	public int getPID() {
		return PID;
	}

	/**
	* Devolve o tamanho do processo
	*/
	public int size() {
		return size;
	}

	/**
	* Devolve o tempo de chegada do processo
	*/
	public int t0() {
		return t0;
	}

	/**
	* Devolve o tempo de finalização do processo
	*/
	public int tf() {
		return tf;
	}

	/**
	* Devolve a base do espaço de endereço do processo
	*/
	public int base() {
		return base;
	}

	/**
	* Devolve o limite do espaço de endereço do processo
	*/
	public int limit() {
		return limit;
	}

	/**
	* Devolve o nome do processo
	*/
	public String name() {
		return name;
	}

}
