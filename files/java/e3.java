public class e3
{
	public static void main(String[] args)
	{
		int num = 20000;
		long[] arr = new long[num];
		for (int i = 0; i < num; i++){
			long ans = largestPrimeFactor(i);
			arr[i] = ans;
		}
		System.out.println(arr[32]);
	}

	public static long largestPrimeFactor(long num)
	{
		long i = 0;
		while (num != 1 && i < num){
			i++;
			if (num % i == 0) num = num / i;
		}

		return num;
	}
}
