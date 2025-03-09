package kata_8.GrassHopper;

public class GrassHopper {

	public static char getGrade(int s1, int s2, int s3) {
		int avarage = (s1 + s2 + s3) / 3;

		switch (avarage / 10) {
			case 10:
			case 9:
				return 'A';
			case 8:
				return 'B';
			case 7:
				return 'C';
			case 6:
				return 'D';
			default:
				return 'F';

		}
	}
}
