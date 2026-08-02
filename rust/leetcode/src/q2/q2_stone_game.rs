pub struct Solution;

impl Solution {
    pub fn stone_game(piles: Vec<i32>) -> bool {
        let n = piles.len();
        let mut q1 = vec![vec![0; n]; n];
        for a1 in 0..n {
            q1[a1][a1] = piles[a1];
        }
        for a2 in 2..=n {
            for a3 in 0..=n - a2 {
                let i = a3;
                let j = a3 + a2 - 1;
                q1[i][j] = (piles[i] - q1[i + 1][j]).max(piles[j] - q1[i][j - 1]);
            }
        }
        q1[0][n - 1] > 0
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn t1() {
        assert!(Solution::stone_game(vec![5, 3, 4, 5]));
    }

    #[test]
    fn t2() {
        assert!(Solution::stone_game(vec![3, 7, 2, 3]));
    }

    #[test]
    fn t3() {
        assert!(Solution::stone_game(vec![2, 1, 9, 1]));
    }
}
