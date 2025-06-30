import java.util.Scanner;

public class QuestionServices {
    Questions[] questions = new Questions[5];
    String[] selection = new String[5];

    public QuestionServices(){
        questions[0] = new Questions(1, "Project language?", "java", "C", "cpp", "c#", "java");
        questions[1] = new Questions(2, "size of int", "2", "6", "4", "8", "4");
        questions[2] = new Questions(3, "Size of double", "2", "6", "4", "8", "8");
        questions[3] = new Questions(4, "Size of char", "2", "6", "4", "8", "2");
        questions[4] = new Questions(5, "Size of boolean", "1", "6", "4", "8", "1");
    }

    public void playQuiz(){
        Scanner scanner = new Scanner(System.in);
        int i = 0;
        for(Questions q : questions){
        System.out.println("Question no. : " + q.getId());
        System.out.println(q.getQuestion());
        System.out.print(q.getOpt1() + "   ");
        System.out.print(q.getOpt2() + "   ");
        System.out.print(q.getOpt3() + "   ");
        System.out.println(q.getOpt4() + "   ");

       

        selection[i] = scanner.nextLine();
        i++;
        }

        System.out.println("\n" + "answers:");

        for(String s : selection)
        {
            System.out.println(s);
        }

        scanner.close();
    }

    public void printScore(){
        int score = 0;

        for(int i = 0; i<questions.length; i++){
            Questions que = questions[i];
            String actualAnswer = que.getAnswer();
            String userAnswer = selection[i];
            if(actualAnswer.equals(userAnswer)){
                score++;
            } 
        }
        System.out.println("Your Score is : " + score);
    }

}
