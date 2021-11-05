import java.util.ArrayList;
import java.util.HashMap; 

public class hashmaptest {

    public static ArrayList<String> findRepeatedDnaSequences(String s){
        
        ArrayList<String> ans = new ArrayList<String>();
        HashMap<String,Integer> ansMap = new HashMap<String,Integer>();
        int a = 10;
        while (a<s.length()){
            String temp = s.substring(a-10, a);
            Integer value = ansMap.get(temp);
            if (value == null){
                ansMap.put(temp, 1);
            }
            else{
                ansMap.put(temp, value+1);
            } 
            ++a;
        }
        for (String key: ansMap.keySet()){
            if (ansMap.get(key) > 1) ans.add(key);
        }
        return ans;
    }

    public static void main(String[] args){
        System.out.println("Starting program");
        ArrayList<String> ans = findRepeatedDnaSequences("AAAABBBAAAABBBAAAABBBAAAABBB");
        for (int i = 0; i < ans.size(); ++i){
            System.out.println(ans.get(i));
        }
    }

}