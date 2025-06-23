import java.util.Scanner;

public class MadLibsGame {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String adjective1, noun1, adjective2, verb1, adjective3;

        System.out.print("Enter an adjective (description): ");
        adjective1 = scanner.nextLine();

        System.out.print("Enter a noun (animal or person): ");
        noun1 = scanner.nextLine();

        System.out.print("Enter an adjective (description): ");
        adjective2 = scanner.nextLine();

        System.out.print("Enter a verb end end with -ing (action): ");
        verb1 = scanner.nextLine();

        System.out.print("Enter an adjective (description): ");
        adjective3 = scanner.nextLine();

        System.out.print("\n\nToday I went to a " + adjective1 + " zoo.");
        System.out.print(" In an exihibit, i saw "+ noun1 + ". ");
        System.out.print(noun1 +" was "+ adjective2+" and "+verb1+ "!");
        System.out.print(" I was "+adjective3+ "!\n");

        scanner.close();
    }
}
