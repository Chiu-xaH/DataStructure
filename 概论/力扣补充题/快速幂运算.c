long long int quik_power(int base, int power) {
	long long int result = 1;
	while (power > 0) {
        //指数为奇数
		if (power % 2 == 1) {
			power -= 1;         //指数减一
			power /= 2;         //指数折半
			result *= base;     //分离出当前项并累乘后保存
			base *= base;       //底数变其平方
		}//指数为偶数
		else {
			power /= 2;         //指数折半
			base *= base;       //底数变其平方
		}
	}
	return result;              //返回最终结果
}
//思想概括
//例子(指数奇数)：5^6 = (5^2)^3 = (25^2)*(25^2)^(3-1) = 625*(625^1)^1 =  625*(625^1)*(625^1)^(1-1) = 625*625*1
//例子(指数偶数)：6^8 = (6^2)^4 = (36^2)^2 = (1296^2)^1