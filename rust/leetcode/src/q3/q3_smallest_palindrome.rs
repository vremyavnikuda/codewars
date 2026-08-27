impl Solution {
    pub fn smallest_palindrome(s: String, k: i32) -> String {
        let q1 = s.as_bytes();
        let q2 = k.max(1) as usize;
        const MAX: usize = 1_000_001;
        let mut a1 = [0usize; 26];
        for &q3 in q1 {
            a1[(q3 - b'a') as usize] += 1;
        }
        let mut q3 = 0usize;
        let mut q4 = 26u8;
        for q5 in 0..26 {
            if a1[q5] & 1 == 1 {
                q3 += 1;
                q4 = q5 as u8;
            }
        }
        if q3 > 1 {
            return String::new();
        }
        let mut a2 = [0usize; 26];
        let mut q5 = 0usize;
        for q6 in 0..26 {
            a2[q6] = a1[q6] / 2;
            q5 += a2[q6];
        }
        let a3 = |a4: &[usize; 26]| -> usize {
            let mut q7: usize = a4.iter().sum();
            let mut q8 = 1usize;
            for &q9 in a4 {
                if q9 == 0 {
                    continue;
                }
                let q10 = q9.min(q7 - q9);
                let mut q11 = 1usize;
                for q12 in 1..=q10 {
                    q11 = q11 * (q7 - q12 + 1) / q12;
                    if q11 >= MAX {
                        q11 = MAX;
                        break;
                    }
                }
                q8 = q8 * q11;
                if q8 >= MAX {
                    return MAX;
                }
                q7 -= q9;
            }
            q8
        };
        if q2 > a3(&a2) {
            return String::new();
        }
        let q13 = q1.len();
        let mut q14 = vec![0u8; q13];
        let mut q6 = q2;
        let mut q7 = 0usize;
        for _ in 0..q5 {
            for q8 in 0..26 {
                if a2[q8] == 0 {
                    continue;
                }
                a2[q8] -= 1;
                let q9 = a3(&a2);
                if q9 >= q6 {
                    q14[q7] = q8 as u8 + b'a';
                    q7 += 1;
                    break;
                }
                q6 -= q9;
                a2[q8] += 1;
            }
        }
        if q4 < 26 {
            q14[q5] = q4 + b'a';
        }
        for q8 in 0..q5 {
            q14[q13 - 1 - q8] = q14[q8];
        }
        String::from_utf8(q14).unwrap()
    }
}
