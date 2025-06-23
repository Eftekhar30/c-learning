import java.util.Scanner;

public class scanner{
    public static void main(String[] args) {
        double width = 0;
        double height = 0;
        double area = 0;
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter width: ");
        width = scanner.nextDouble();

        System.out.print("Enter height: ");
        height = scanner.nextDouble();
 
        area = width * height;

        System.out.println("Area: " + area + "cm²");

        scanner.close();
    }
}