public class Main{
    public static void main(String[] args){
        DisplayMenu menu = new DisplayMenu();
        int choice = 0;

        while(choice != 6){
            menu.ShowMenu();
            choice = menu.getUserChoice();

            if(choice == 1){
                System.out.println("Add student - coming soon");
            }
            else if(choice == 2){
                System.out.println("View All - Coming Soon");
            }
            else if(choice == 3){
                System.out.println("Search - Coming Soon");
            }
            else if(choice == 4){
                System.out.println("Update - Coming Soon");
            }
            else if(choice == 5){
                System.out.println("Delete - Coming Soon");
            }
            else if(choice == 6){
                System.out.println("Goodbye!");
            }
            else{
                System.out.println("Invalid choice! Try again.");
            }
            
            System.out.println();
        }

    }
}