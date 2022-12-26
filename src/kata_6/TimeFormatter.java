package kata_6;

import java.util.Arrays;
import java.util.stream.*;

public class TimeFormatter {
    // Функция, форматирующая количество секунд в формате "X year(s), Y day(s), Z hour(s), W minute(s), U second(s)"
    public static String formatDuration(int seconds) {
        // Если секунд нет, то возвращаем строку "now"
        if (seconds == 0) {
            return "now";
        }

        return Arrays.stream(
                        // Создаем массив строк, содержащий форматированное количество лет, дней, часов, минут и секунд
                        new String[]{
                                // количество лет
                                formatTime("year",  seconds / 31536000),
                                // количество дней
                                formatTime("day",   seconds / 86400 % 365),
                                // количество часов
                                formatTime("hour",  seconds / 3600 % 24),
                                // количество минут
                                formatTime("minute", seconds / 60 % 60),
                                //количество секунд
                                formatTime("second", seconds % 60)})
                // Отфильтровываем пустые строки из массива
                .filter(e->e!="")
                .collect(Collectors.joining(", "))
                // Заменяем все запятые на "and", кроме последней
                .replaceAll(", (?!.+,)", " and ");
    }
    // Функция, форматирующая количество временного промежутка (например, часов, минут) в формате "X s"
    public static String formatTime(String s, int time){
        if (time == 0) {
            return "";
        }
        return Integer.toString(time)+ " " + s + (time==1?"" : "s");
    }
}