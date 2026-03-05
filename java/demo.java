// import java.util.Scanner;
// class students
// {
//     public void playMusic(){
//         System.out.println("playing music");
//     }
//     public String pen(int cost){
//         if(cost >= 10)
//             return "thanks for buying";
//         else
//             return "not enough money to buy the pen";
//     }


// } 

// class calculator
// {
//     public void sum(){
//         Scanner scanner =  new Scanner(System.in);
//         System.out.print("");
//         int a = scanner.nextInt();
//         int b = scanner.nextInt();
//         int sum = a+b; 
//         System.out.println(sum);
//         scanner.close();
//     }
// }
public class demo {
    public static void main(String[] args) {
        // students student = new students();
        // student.playMusic();

        // String str = student.pen(2);
        // System.out.println(str);
        // calculator cal = new calculator();
        // cal.sum();
        int arr[][] = new int[2][3];
        
        for(int i = 0; i<arr.length; i++){
            for(int j = 0; j<arr[i].length; j++){
                arr[i][j] = (int)(Math.random()* 10);;
            }
        }
        for (int[] row : arr) {
            for (int n : row) {
                System.out.print(n + " ");
            }
            System.out.println();
        }
        
    }
}
