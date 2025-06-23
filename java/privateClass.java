import java.util.Scanner;
class human
{
    private String name;
    private String email;
    private int roll;

    public void setName(String n){
        name = n;
    }
    public void setEmail(String Email){
        email = Email;
    }
    public void setRoll(int Roll){
        roll = Roll;
    }
    public String getName(){
        return name;
    }
    public String getEmail(){
        return email;
    }
    public int getRoll(){
        return roll;
    }
}

public class privateClass {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        human h = new human();

        int roll;
        String name, email;

        System.out.print("Enter your Name: ");
        name = scanner.nextLine();
        h.setName(name);
        System.out.print("Enter your Email: ");
        email = scanner.nextLine();
        h.setEmail(email);
        System.out.print("Enter your Roll: ");
        roll = scanner.nextInt();
        h.setRoll(roll);
        
        System.out.println("Your name is : " + h.getName() + "\n" + "Email : " + h.getEmail() + "\n" + "Roll : " + h.getRoll());

        scanner.close();

    }
}
