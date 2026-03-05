/*  some math stuffs
 * //result = Math.pow(2,3);
        //result = Math.abs(-5);
        //result = Math.sqrt(9);
        //result = Math.round(3.14);
        //result = Math.floor(3.14);
        //result = Math.ceil(3.14);
        //result = Math.max(10,20);
        //result = Math.min(10,20);
 */
 
//exercise 1;
import java.util.Scanner;

public class math {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        double result = 0;
        System.out.println("***********HYPOTENUSE PROBLEM***********");

        System.out.print("Enter angle A: ");
        int A = scanner.nextInt();
        System.out.print("Enter angle B: ");
        int B = scanner.nextInt();
        System.out.println("****************************************\n");

        result = Math.sqrt(Math.pow(A, 2)+ Math.pow(B, 2));
        System.out.printf("The hypotenuse (side C) is: %.2fcm", result);
        scanner.close();
    }
}
