import java.util.Scanner;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;

public class MemoryManager {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try (FileReader file = new FileReader("trasce.txt");
             BufferedReader buffer = new BufferedReader(file);) {

            String line;
            while ((line = buffer.readLine()) != null)
                System.out.println(line);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
