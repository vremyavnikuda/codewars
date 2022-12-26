package kata_6;

import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Mixing {
    private static final String LOWERCASE = "abcdefghijklmnopqrstuvwxyz";

    public static String mix(String s1, String s2) {
        Map<String, Integer> s1Results = getCounters(s1);
        Map<String, Integer> s2Results = getCounters(s2);
        List<String> keys = Arrays.stream(LOWERCASE.split(""))
                .filter(key -> s1Results.containsKey(key) || s2Results.containsKey(key))
                .sorted()
                .collect(Collectors.toList());

        List<String> results = keys.stream()
                .map(key -> {
                    if (s2Results.containsKey(key) && s1Results.containsKey(key)) {
                        if (s1Results.get(key).equals(s2Results.get(key))) {
                            return "=:" + repeat(key, s1Results.get(key));
                        } else if (s1Results.get(key) > s2Results.get(key)) {
                            return "1:" + repeat(key, s1Results.get(key));
                        } else {
                            return "2:" + repeat(key, s2Results.get(key));
                        }
                    } else {
                        if (s1Results.containsKey(key)) {
                            return "1:" + repeat(key, s1Results.get(key));
                        } else {
                            return "2:" + repeat(key, s2Results.get(key));
                        }
                    }
                })
                .collect(Collectors.toList());

        return String.join("/", sortResults(results));
    }

    private static Map<String, Integer> getCounters(String s) {
        return s.chars()
                .mapToObj(c -> (char) c)
                .filter(c -> LOWERCASE.indexOf(c) != -1)
                .collect(Collectors.groupingBy(Object::toString, Collectors.summingInt(c -> 1)));
    }

    private static String repeat(String s, int n) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++) {
            sb.append(s);
        }
        return sb.toString();
    }

    private static List<String> sortResults(List<String> results) {
        results.sort(String::compareTo);

        boolean isSorted = false;
        while (!isSorted) {
            isSorted = true;
            for (int i = 0; i < results.size() - 1; i++) {
                if (results.get(i).length() == results.get(i + 1).length()) {
                    if (results.get(i).charAt(0) > results.get(i + 1).charAt(0)) {
                        isSorted = false;
                        String temp = results.get(i);
                        results.set(i, results.get(i + 1));
                        results.set(i + 1, temp);
                    }
                } else if (results.get(i).length() < results.get(i + 1).length()) {
                    isSorted = false;
                    String temp = results.get(i);
                    results.set(i, results.get(i + 1));
                    results.set(i + 1, temp);
                }
            }
        }
        return results;
    }
}
