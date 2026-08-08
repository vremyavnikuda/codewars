struct Solution;

impl Solution {
    pub fn valid_sequence(word1: String, word2: String) -> Vec<i32> {
        let a1 = word1.as_bytes();
        let a2 = word2.as_bytes();
        let mut q1 = vec![-1i32; a2.len()];
        // ponytail: q1 doubles as scratch for `last[]` (C++), the required output
        // allocation — reads at q1[j+1] always stay ahead of writes at q1[j]
        let mut q2 = a2.len() as isize - 1;
        let mut q3 = a1.len() as isize - 1;
        while q3 >= 0 && q2 >= 0 {
            if a1[q3 as usize] == a2[q2 as usize] {
                q1[q2 as usize] = q3 as i32;
                q2 -= 1;
            }
            q3 -= 1;
        }
        let mut q4 = true;
        let mut q5 = 0usize;
        for (q6, &q7) in a1.iter().enumerate() {
            if q5 == a2.len() {
                break;
            }
            if q7 == a2[q5] {
                q1[q5] = q6 as i32;
                q5 += 1;
            } else if q4 && (q5 + 1 == a2.len() || (q6 as i32) < q1[q5 + 1]) {
                q4 = false;
                q1[q5] = q6 as i32;
                q5 += 1;
            }
        }
        if q5 == a2.len() { q1 } else { Vec::new() }
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn t1() {
        assert_eq!(Solution::valid_sequence("aab".into(), "ab".into()), vec![0, 1]);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::valid_sequence("ab".into(), "aa".into()), vec![0, 1]);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::valid_sequence("abcde".into(), "axe".into()), vec![0, 1, 4]);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::valid_sequence("bc".into(), "ab".into()), Vec::new());
    }

    #[test]
    fn t5() {
        assert_eq!(Solution::valid_sequence("ba".into(), "ab".into()), Vec::new());
    }

    #[test]
    fn t6() {
        assert_eq!(Solution::valid_sequence("ab".into(), "".into()), Vec::new());
    }

    #[test]
    fn t7() {
        assert_eq!(
            Solution::valid_sequence("bbeigiibhjafjig".into(), "iihhj".into()),
            vec![3, 5, 6, 8, 9]
        );
    }
}
