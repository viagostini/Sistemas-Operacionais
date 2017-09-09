import java.io.FileNotFoundException;
import java.io.PrintStream;

public class Process {
	private static double MAXt0 = 180.0;
	private static double MINdt = 1.0;
	private static double MAXdt = 5.0;
	private static double gordura = 2.0;
	private static int id = 1000;
	private int PID;
	private double t0, dt, deadline;
	private String nome;

	public Process() {
		this.PID = id++;
		this.nome = "pid" + Integer.toHexString(this.PID);
		this.t0 = Math.random() * MAXt0;
		this.dt = MINdt + (MAXdt - MINdt) * Math.random();
		this.deadline = t0 + gordura * this.dt;
	}

	@Override
	public String toString() {
		return this.t0 + " " + " " + this.dt + " " + this.deadline + " " + this.nome;
	}

	public static void main(String[] args) throws FileNotFoundException {
		int amount;
		PrintStream ps;

		for (int j = 1; j <= 90; j++) {
            ps = new PrintStream("traces/unsorted_trace_file_"+j+".txt");

            if (j < 31) amount = 50;
            else if (j < 61) amount = 150;
            else amount = 450;

            for (int i = 0; i < amount; i++) {
        		Process p = new Process();
        		ps.println(p);
        	}

            ps.close();
        }
	}
}
