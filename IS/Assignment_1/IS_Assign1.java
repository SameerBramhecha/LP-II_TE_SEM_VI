public class IS_Assign1{
    int and(char x){
        return (x&127);
    }
    int or(char x){
        return (x|127);
    }
    int xor(char x){
        return (x^127);
    }
    public static void main(String[] args) {
        IS_Assign1 is = new IS_Assign1();
        String s = "\\HelloWorld";
        for(int i=0;i<s.length();i++){
            char x = s.charAt(i);
            System.out.println(s.charAt(i)+"("+(int) x+")");
            System.out.println("AND: "+ is.and(x));
            System.out.println("OR: " + is.or(x));
            System.out.println("XOR: "+is.xor(x));
        }
    }
}