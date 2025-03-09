package kata_6;

public class encrypt_decrypt {
    private static String alternatingSplit(final String text) {
        StringBuilder sb = new StringBuilder();
        final int len = text.length();
        final int step = len / 2;
        int pos = 1;
        for (int i = 0; i < step; i++) {
            sb.append(text.charAt(pos));
            pos += 2;
        }
        pos = 0;
        for (int i = 0; i < step; i++) {
            sb.append(text.charAt(pos));
            pos += 2;
        }
        if (len % 2 == 1) {
            sb.append(text.charAt(len - 1));
        }

        return sb.toString();
    }

    public static String encrypt(final String text, final int n) {
        if (text == null || "".equals(text.trim()) || n <= 0
                || text.length() == 1) {
            return text;
        }
        String result = text;
        for (int i = 0; i < n; i++) {
            result = alternatingSplit(result);
        }
        return result;
    }

    private static String restore(final String encryptedText) {
        StringBuilder sb = new StringBuilder();
        final int len = encryptedText.length();
        final int step = len / 2;
        for (int i = 0; i < step; i++) {
            sb.append(encryptedText.charAt(step + i));
            sb.append(encryptedText.charAt(i));
        }
        if (len % 2 == 1) {
            sb.append(encryptedText.charAt(len - 1));
        }

        return sb.toString();
    }

    public static String decrypt(final String encryptedText, final int n) {
        if (encryptedText == null || "".equals(encryptedText.trim()) || n <= 0
                || encryptedText.length() == 1) {
            return encryptedText;
        }
        String result = encryptedText;
        for (int i = 0; i < n; i++) {
            result = restore(result);
        }
        return result;
    }

}
