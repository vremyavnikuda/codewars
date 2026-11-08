impl Solution {
    pub fn find_mismatched_segments(s1: String, s2: String) -> Vec<Vec<String>> {
        let (a, b) = (s1.as_bytes(), s2.as_bytes());
        let mut res = vec![];
        let mut i = 0;
        while i < a.len() {
            if a[i] == b[i] {
                i += 1;
                continue;
            }
            let start = i;
            while i < a.len() && a[i] != b[i] {
                i += 1;
            }
            res.push(vec![s1[start..i].to_string(), s2[start..i].to_string()]);
        }
        res
    }
}
