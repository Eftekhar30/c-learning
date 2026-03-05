public class Student {
    private String name;
    private String id;
    private int[] marks;
    private int total;
    private double percentage;
    private String grade;

    public Student(String name, String id, int[] marks) {
        this.name = name;
        this.id = id;
        setMarks(marks);
    }

    private void calculateResults() {
        total = 0;
        if (marks == null || marks.length == 0) {
            percentage = 0.0;
            grade = "N/A";
            return;
        }
        for (int m : marks) {
            total += m;
        }
        percentage = (total / 500.0) * 100;

        if (percentage >= 80) grade = "A+";
        else if (percentage >= 70) grade = "A";
        else if (percentage >= 60) grade = "B";
        else if (percentage >= 50) grade = "C";
        else if (percentage >= 40) grade = "D";
        else grade = "F";
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public int[] getMarks() {
        return marks;
    }

    public int getTotal() {
        return total;
    }

    public double getPercentage() {
        return percentage;
    }

    public String getGrade() {
        return grade;
    }

    public void setMarks(int[] newMarks) {
        this.marks = newMarks;
        calculateResults();
    }

}