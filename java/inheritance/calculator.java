

class calc
{
    public int add(int a, int b)
    {
        return a+b;
    }
}
class advClac extends calc
{
    public double add(double a, double b)
    {
        return a+b;
    }
}

public class calculator{
    public static void main(String[] args) {

        advClac obj = new advClac();
        
        System.out.println(obj.add(1.2,2));
    }
}
