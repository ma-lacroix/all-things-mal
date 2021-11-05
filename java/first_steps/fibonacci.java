import java.util.*;

public class fibonacci {
    
    public static void fibonacciSeq(int n){
        int n1=0,n2=1,n3=0;
        while (n3 < n){
            n3 = n2+n1;
            n1 = n2;
            n2 = n3;
            System.out.println(n3);
        }
    }

    public static void main(String[] args){
        System.out.println("Enter max value: ");
        Scanner input = new Scanner(System.in);
        int max = input.nextInt();
        fibonacciSeq(max);
        input.close();
    }
}
