package kata_8.betterThanAverage;

/*
Найти среднюю оценку класса и сравнить с вашей оценкой
Если ваша оценка больше средней оценки класса вернуть true
Если ваша оценка меньше средней оценки класса вернуть false
*/
public class betterThanAverage {
	public static boolean BetterThanAverage(int[] classPoints, int yourPoints) {
		//переменная куда будем фиксировать общую сумму массива
		int sum = 0;
		//цикл суммирования массива
		for (int point : classPoints) {
			sum += point;
		}
		//ищем среднее значение массива
		int average = sum / classPoints.length;
		//возвращаем результат ? true:false
		return yourPoints > average;
	}
}

