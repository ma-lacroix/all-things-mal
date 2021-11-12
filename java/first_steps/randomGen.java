import java.util.ArrayList;
import  java.math.*;

public class main {

    public static int genRand() {

        double someRand = Math.random()*26;
        int someValue = (int) someRand;
        return someValue;

    }

    public static String genPass(int len) {

        String lower = "abcdefghijklmnopqrstuvwxyz";
        String upper = lower.toUpperCase();
        String specials = "{}#[]!1234567890{}#[]!%&@*";
        String passWord = "";

        int i = 0;
        while (i < len){
            int someValue = genRand();
            char newChar;
            if(someValue%2==0){
                newChar = lower.charAt(someValue);
            }else if(someValue%3==0){
                newChar = upper.charAt(someValue);
            }else{
                newChar = specials.charAt(someValue);
            }
            passWord+=newChar;
            ++i;
        }
        return passWord;
    }

    public static void main(String[] args){

        String passWord = new String();
        passWord = genPass(12);
        System.out.println(passWord);

    }
}
