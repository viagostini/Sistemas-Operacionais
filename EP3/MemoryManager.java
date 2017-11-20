import java.io.File;
import java.io.IOException;

import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.lang.Math;

public class MemoryManager {
    static int total, virt, s, p;
    static List<Process> processes = new ArrayList<Process>();
    static List<Event> events = new ArrayList<Event>();
    static FreeSpaceManager FSM;
    static PagingManager PM;

    public static void loadFile (String filepath) {
        int t0, tf, b;
        String name;
        String[] line;

        try (Scanner sc = new Scanner(new File(filepath));) {
            line = sc.nextLine().split(" ");
            total = Integer.parseInt(line[0]);
            virt = Integer.parseInt(line[1]);
            s = Integer.parseInt(line[2]);
            p = Integer.parseInt(line[3]);

            // System.out.printf("%d %d %d %d\n", total, virt, s, p);

            while (sc.hasNextLine()) {
                line = sc.nextLine().split(" ");

                t0 = Integer.parseInt(line[0]);
                if (line[1] == "COMPACTAR") {
                    Event ev = new Event(t0);
                    events.add(ev);
                    continue;
                }
                tf = Integer.parseInt(line[1]);
                b = Integer.parseInt(line[2]);
                name = line[3];

                Process p = new Process(name, t0, tf, b);
                Event arrival = new Event(p, t0, true);
                Event finish = new Event(p, tf, false);
                events.add(arrival);
                events.add(finish);
                // System.out.printf("%d %d %s %d ", t0, tf, name, b);

                for (int i = 4; i < line.length; i += 2) {
                    int pi, ti;
                    pi = Integer.parseInt(line[i]);
                    ti = Integer.parseInt(line[i+1]);
                    p.insertEvent(pi, ti);
                    Event ev = new Event(p, ti, pi);
                    events.add(ev);
                    //System.out.printf("%d %d ", pi, ti);
                }
                processes.add(p);
                // System.out.println();
            }
            Collections.sort(events);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String[] line;

        Scanner prompt = new Scanner(System.in);

        while (true) {
            System.out.print("[ep3]: ");
            line = prompt.nextLine().split(" ");

            if (line[0].equals("carrega"))
                loadFile(line[1]);
            else if (line[0].equals("espaco")) {          /* TODO */
                int alg = Integer.parseInt(line[1]);
                switch (alg) {
                    case 1:
                        System.out.println("Gerenciamento de espaço livre: Best Fit.");
                        FSM = new BestFit(s, virt);
                        break;
                    case 2:
                        FSM = new WorstFit(s, virt);
                        break;
                    case 3:
                        FSM = new QuickFit(s, virt, processes);
                }
            }
            else if (line[0].equals("substitui")) {
                int alg = Integer.parseInt(line[1]);
                switch (alg) {
                    case 1:
                        PM = new Optimal(virt, p, total, events);
                        break;
                    case 2:
                        PM = new FIFO(virt, p, total);
                        break;
                    case 3:
                        //PM = new LRU2();
                        break;
                    case 4:
                        PM = new LRU4(virt, p, total);
                }
            }
            else if (line[0].equals("executa")) {
                int dt = Integer.parseInt(line[1]);

                FSM.printMemBlocks();
                int t = dt;
                for (Event e : events) {
                    while (t <= e.getT()) {
                        FSM.printMemBlocks();

                        if (t % 10 == 0)
                            PM.resetBitR();

                        t += dt;
                        PM.t = t;
                    }

                    int typeEvent = e.getTypeEvent();

                    // Chegada de processo na memória virtual
                    if (typeEvent == 0) {
                        int nProcessPages = (int)Math.ceil(e.getP().size() / p);

                        // if (nProcessPages % p != 0)
                        //    nProcessPages++;

                        for (int i = 0; i < nProcessPages; i++) {
                            Page p = new Page(-1, -1);
                            PM.insertPage(p);
                            e.getP().insertPage(p);
                        }
                    } else if (typeEvent == 1) {
                        int address = e.getP().getPage(e.getPos() / p).getPosVirtual() * + e.getPos() % p;

                        address = PM.requestPageFrame(address);
                        // FSM.addProcess(address); PRECISAMOS ARRUMAR ESTA MERDA AQUI
                    } else if (typeEvent == 2) {
                        FSM.compactMemory();
                        PM.compactMemory();
                    } else if (typeEvent == 3) {
                        PM.removeProcess(e.getP());
                    }
                }
            }
            else if (line[0].equals("sai"))
                break;
            else
                System.out.println("Comando inválido!");
        }

        FSM.deleteMemoryFiles();
    }
}
