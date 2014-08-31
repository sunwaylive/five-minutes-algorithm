class Solution
{
	public static bubble_sort(int A[], int start, int end)
	{
		boolean exchange;
        for(int i = start; i < end - 1; ++i)
        {
        	exchange = false;
        	for(int j = end-1; j > i; --j)
        	{
        		if(A[j] < A[j-1])
        		{
        			int temp = A[j];
        			A[j] = A[j-1];
        			A[j-1] = temp;
        			exchange = true;
        		}
        	}
        	if(!exchange) return;
        }
	}
	public static void main(String[] args)
	{
		int A[] = {1,3,4,2,8,3,4};
		Solution.bubble(A, 0, A.length());
		for(int i = 0; i < A.length; ++i)
			System.out.println(A[i]);
	}
}