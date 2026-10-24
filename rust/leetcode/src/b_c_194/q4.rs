impl Solution {
    pub fn count_magical_pairs(s: String) -> i64 {
        let s: Vec<usize> = s.bytes().map(|b| (b - b'a') as usize).collect();
        let n = s.len() as i64;
        let mut prev = vec![-1i64; s.len()];
        let mut last = [-1i64; 26];
        for (p, &c) in s.iter().enumerate() {
            prev[p] = last[c];
            last[c] = p as i64;
        }
        last[s[s.len() - 1]] = prev[s.len() - 1];
        let mut nxt = [n; 26];
        let mut ans = 0i64;
        for j in (0..s.len() - 1).rev() {
            nxt[s[j + 1]] = j as i64 + 1;
            let mut p: Vec<i64> = last.iter().copied().filter(|&x| x >= 0).collect();
            p.sort_unstable_by(|a, b| b.cmp(a));
            p.push(-1);
            let mut q: Vec<i64> = nxt.iter().copied().filter(|&x| x < n).collect();
            q.sort_unstable();
            q.push(n);
            for d in 1..p.len().min(q.len()) {
                ans += (p[d - 1] - p[d]) * (q[d] - q[d - 1]);
            }
            last[s[j]] = prev[j];
        }
        ans
    }
}
