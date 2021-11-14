import java.util.ArrayList;
import java.util.Scanner;
import java.math.*;

public class tictactoe {

    public static class gameBoard {

        private ArrayList<Character> choices = new ArrayList<Character>();

        public void initChoices(){
            for(int i = 0; i < 9 ; ++i ){
                choices.add(' ');
            }
        }

        public void updateChoices(int sel, char pl){
            if(pl == 'p' && choices.get(sel)==' ') choices.set(sel,'X');
            if(pl == 'c') choices.set(sel,'O');
        }

        public void computerMove(){
            double someVal = Math.random()*8;
            int computerChoice = (int) someVal;
            if(choices.get(computerChoice)!=' ') {
                computerMove();
            }else{
                updateChoices(computerChoice,'c');
            }
        }

        public boolean checkStatus(){

            if(choices.get(0)!=' ' && choices.get(0)==choices.get(1) && choices.get(1)==choices.get(2)||
                choices.get(3)!=' ' && choices.get(3)==choices.get(4) && choices.get(4)==choices.get(5)||
                choices.get(6)!=' ' && choices.get(6)==choices.get(7) && choices.get(7)==choices.get(8)||
                choices.get(0)!=' ' && choices.get(0)==choices.get(3) && choices.get(3)==choices.get(6)||
                choices.get(1)!=' ' && choices.get(1)==choices.get(4) && choices.get(4)==choices.get(7)||
                choices.get(2)!=' ' && choices.get(2)==choices.get(5) && choices.get(5)==choices.get(8)||
                choices.get(0)!=' ' && choices.get(0)==choices.get(4) && choices.get(4)==choices.get(8)||
                choices.get(6)!=' ' && choices.get(6)==choices.get(4) && choices.get(4)==choices.get(2)
            ){
                return false;
            }else{
                return true;
            }
        }

        public void printBoard(){
            String line1 = " " + choices.get(0) + " | " + choices.get(1) + " | " + choices.get(2) + "  ";
            String line2 = "-----------";
            String line3 = " " + choices.get(3) + " | " + choices.get(4) + " | " + choices.get(5) + "  ";
            String line4 = "-----------";
            String line5 = " " + choices.get(6) + " | " + choices.get(7) + " | " + choices.get(8) + "  ";
            ArrayList<String> theBoard = new ArrayList<String>();
            theBoard.add(line1);
            theBoard.add(line2);
            theBoard.add(line3);
            theBoard.add(line4);
            theBoard.add(line5);

            for (int i = 0;i < theBoard.size(); ++i ){
                System.out.println(theBoard.get(i));
            }
        }
    }

    public static void gameLoop(){

        gameBoard board = new gameBoard();
        board.initChoices();
        board.printBoard();
        Scanner aChoice = new Scanner(System.in);
        boolean gameOn = true;

        while(gameOn){
            System.out.print("\nEnter your next move: ");
            int newChoice = aChoice.nextInt()-1;
            board.updateChoices(newChoice,'p');
            board.printBoard();
            gameOn = board.checkStatus();
            System.out.println("\nComputer's turn: \n");
            board.computerMove();
            board.printBoard();
            gameOn = board.checkStatus();
        }
        System.out.println("\nGAME OVER");
    }

    public static void main(String[] args){
        System.out.println("Starting game\n");
        gameLoop();

    }
}
