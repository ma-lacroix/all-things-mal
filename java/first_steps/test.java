// some simple Java code to help me onboard new projects at work
// author: Marc-Antoine Lacroix

import java.util.ArrayList;

class test {

    static int someNumber = 40;
    static float coordinate = 0.3f;

    public static ArrayList<String> buildArray(){
        ArrayList<String> someArray = new ArrayList<String>();
        someArray.add("Canada");
        someArray.add("Mexico");
        someArray.add("Brazil");
        someArray.add("South Africa");
        return someArray;
    }
    
    public static void someLoop(int n){
        int i = 0;
        ArrayList<String> countries = new ArrayList<String>();
        countries = buildArray();
        while(i < countries.size()){
            System.out.println("Line: " + countries.get(i));
            if(countries.get(i)=="Mexico"){
                System.out.print("No he's not from Mexico!");
            }
            ++i;
        }
        i = 0;
        while(i<someNumber){
            System.out.println(i);
            ++i;
        }
    }
    public static void main(String[] args) {
        System.out.println("Starting program");
        System.out.println(someNumber + " is the number of KMs I ran last week");
        someLoop(10);
    }  
}