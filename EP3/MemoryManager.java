import java.io.File;
import java.io.IOException;

import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class MemoryManager {
    static int total, virt, s, p;
    static List<Process> processes = new ArrayList<>();
    static List<Event> events = new ArrayList<>();
    static FreeSpaceManager FSM;

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
                tf = Integer.parseInt(line[1]);
                b = Integer.parseInt(line[2]);
                name = line[3];

                Process p = new Process(name, t0, tf, b);
                Event arrival = new Event(p, -1, t0);
                Event finish = new Event(p, -1, tf);
                // System.out.printf("%d %d %s %d ", t0, tf, name, b);

                for (int i = 4; i < line.length; i += 2) {
                    int pi, ti;
                    pi = Integer.parseInt(line[i]);
                    ti = Integer.parseInt(line[i+1]);
                    p.insertEvent(pi, ti);
                    Event ev = new Event(p, pi, ti);
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
                System.out.println("Gerenciamento de espaço livre: Best Fit.");
                FSM = new BestFit(s, virt);
            }
            else if (line[0].equals("substitui")) {
                break;  /* TODO */
            }
            else if (line[0].equals("executa")) {
                break;  /* TODO */
            }
            else if (line[0].equals("sai"))
                break;
        }
    }
}
