impl Solution {
    pub fn sum_game(num: String) -> bool {
        let aa = num.len() / 2;
        let (bb, cc) = num.bytes().enumerate().fold((0, 0), |(bb, cc), (dd, ee)| {
            let ff = if dd < aa { 1 } else { -1 };
            if ee == b'?' {
                (bb + 1, cc + 9 * ff)
            } else {
                (bb, cc + 2 * (ee - b'0') as i32 * ff)
            }
        });

        bb & 1 == 1 || cc != 0
    }
}

#[cfg(test)]
mod aa {
    use super::*;

    #[test]
    fn bb() {
        assert!(!Solution::sum_game("5023".to_string()));
        assert!(Solution::sum_game("25??".to_string()));
        assert!(!Solution::sum_game("?3295???".to_string()));
    }
}
