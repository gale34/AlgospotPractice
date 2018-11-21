package Solution;

import java.util.Stack;

public class BRACKETS2 {
    public static Boolean isRightBracket(String word) {
        Stack<Character> stack = new Stack<Character>();
        
        for(int i = 0; i < word.length(); i++) {
            char target = word.charAt(i);
            
            if(target == ')') {
                if(stack.empty())
                    return false;
                    
                if(stack.peek() == '(')
                    stack.pop();
                else
                    return false;
            }
            else if(target == '}') {
                if(stack.empty())
                    return false;

                if(stack.peek() == '{')
                    stack.pop();
                else
                    return false;
            }
            else if(target == ']') {
                if(stack.empty())
                    return false;

                if(stack.peek() == '[')
                    stack.pop();
                else
                    return false;
            }
            else
                stack.push(target);
        }
        
        if(stack.empty())
        	return true;
        else
        	return false;
    }
}