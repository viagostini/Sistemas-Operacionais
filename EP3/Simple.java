import java.io.File;
import java.util.Scanner;
import java.io.IOException;

public class Simple {
    public static void main(String[] args) {
        int total, virt, s, p;
        int t0, tf, b;
        String nome;
        String[] line;

        try (Scanner sc = new Scanner(new File("trace.txt"));) {

            line = sc.nextLine().split(" ");
            total = Integer.parseInt(line[0]);
            virt = Integer.parseInt(line[1]);
            s = Integer.parseInt(line[2]);
            p = Integer.parseInt(line[3]);

            System.out.printf("%d %d %d %d\n", total, virt, s, p);

            while (sc.hasNextLine()) {
                line = sc.nextLine().split(" ");

                t0 = Integer.parseInt(line[0]);
                tf = Integer.parseInt(line[1]);
                nome = line[2];
                b = Integer.parseInt(line[3]);

                System.out.printf("%d %d %s %d ", t0, tf, nome, b);

                for (int i = 4; i < line.length; i += 2) {
                    int pi, ti;
                    pi = Integer.parseInt(line[i]);
                    ti = Integer.parseInt(line[i+1]);
                    System.out.printf("%d %d ", pi, ti);
                }
                System.out.println();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
