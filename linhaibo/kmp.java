public class Solution {
    public String strStr(String haystack, String needle) {
        int len1 = haystack.length(), len2 = needle.length();
        int[] next = new int[len2];
        int j = -1;
        if(len2 == 0) return haystack;
        if(len1 < len2) return null;
        find_next(needle, next);
        for(int i = 0; i < len1; i++)
        {
            while(j > -1 && needle.charAt(j + 1) != haystack.charAt(i)) j = next[j];
            if(needle.charAt(j + 1) == haystack.charAt(i)) j++;
            if(j == len2 - 1)
            return haystack.substring(i - len2 + 1);
        }
        return null;
    }
    private void find_next(String needle, int[] next)
    {
        int len = needle.length();
        next[0] = -1;
        int j = -1;
        for(int i = 1; i < len; i++)
        {
            while(j > -1 && needle.charAt(j + 1) != needle.charAt(i)) j = next[j];
            if(needle.charAt(j + 1) == needle.charAt(i)) j++;
            next[i] = j;
        }
    }
}