import java.util.Scanner;

public class DisplayMenu{

    Scanner scan = new Scanner(System.in);

    public void ShowMenu(){
        System.out.println("1. Add Student");
        System.out.println("2. View All Students");
        System.out.println("3. Search Student");
        System.out.println("4. Update Marks");
        System.out.println("5. Delete Student");
        System.out.println("6. Exit"); 
    }

    public int getUserChoice(){
    System.out.print("Enter your choice: ");
    return scan.nextInt();
}

}