
package kata_7;
class Solution {
    public static String whoLikesIt(String[] names) {
        String result = "";
        int size = names.length;
        switch (size) {
            case 0:
                result = "no one likes this";
                break;
            case 1:
                result = names[0] + " likes this";
                break;
            case 2:
                result = names[0] + " and " + names[1] + " like this";
                break;
            case 3:
                result = names[0] + ", " + names[1] + " and " + names[2] + " like this";
                break;
            default:
                result = names[0] + ", " + names[1] + " and " + (size - 2) + " others like this";
                break;
        }
        return result;
    }
}
