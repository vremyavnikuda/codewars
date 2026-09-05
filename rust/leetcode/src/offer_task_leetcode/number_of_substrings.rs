#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn number_of_substrings(s: String) -> i32 {
        let n = s.len();
        let bytes = s.as_bytes();
        let mut nxt = vec![n; n + 1];
        for i in (0..n).rev() {
            nxt[i] = nxt[i + 1];
            if bytes[i] == b'0' {
                nxt[i] = i;
            }
        }
        let mut ans = 0;
        for i in 0..n {
            let mut cnt0 = if bytes[i] == b'0' { 1 } else { 0 };
            let mut j = i;
            while j < n && (cnt0 as i64) * (cnt0 as i64) <= n as i64 {
                let cnt1 = nxt[j + 1] as i32 - i as i32 - cnt0;
                if cnt1 >= cnt0 * cnt0 {
                    ans += std::cmp::min((nxt[j + 1] - j) as i32, cnt1 - cnt0 * cnt0 + 1);
                }
                j = nxt[j + 1];
                cnt0 += 1;
            }
        }
        ans
    }
}

fn main() {
    let test1 = Solution::number_of_substrings("00011".to_string());
    println!("Test 1: \"00011\" => {}", test1);

    let test2 = Solution::number_of_substrings("101101".to_string());
    println!("Test 2: \"101101\" => {}", test2);
}
