import java.util.Scanner;


class user
{
    String username;
    String password;
    String repeatPassword;
    static String mail;
    public int randomNumber(){
        int n = (int)(Math.random()*1000);
        return n;
    }
    public void email(){
        System.out.println("Your email is: "+username + randomNumber() + mail);
    }
}
public class demo1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        user User = new user();
        System.out.print("enter your username: ");
        User.username = scanner.nextLine();
        
        
        while(true){
            System.out.print("Enter your password: ");
            User.password = scanner.nextLine();

            System.out.print("Repeat our password: ");
            User.repeatPassword = scanner.nextLine();
            if(User.password.equals(User.repeatPassword)){
                break;
            } else{
                System.out.println("Password doesn't match! Please try again.");
            }
        }

        user.mail = "@gmail.com";
        User.email();

        scanner.close();
    }
}
