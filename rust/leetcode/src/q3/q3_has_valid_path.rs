impl Solution {
    pub fn has_valid_path(grid: Vec<Vec<char>>) -> bool {
        let aa = grid.len();
        let bb = grid[0].len();
        if (aa + bb) % 2 == 0 || grid[0][0] == ')' || grid[aa - 1][bb - 1] == '(' {
            return false;
        }
        let mut cc = [0u128; 100];
        cc[0] = 1;
        for dd in &grid {
            for (ee, &ff) in dd.iter().enumerate() {
                let gg = cc[ee] | if ee > 0 { cc[ee - 1] } else { 0 };
                cc[ee] = if ff == '(' { gg << 1 } else { gg >> 1 };
            }
        }
        cc[bb - 1] & 1 != 0
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn valid_parentheses_path() {
        assert!(Solution::has_valid_path(vec![
            vec!['(', '(', ')'],
            vec!['(', ')', ')'],
        ]));
        assert!(!Solution::has_valid_path(vec![
            vec!['(', '(', '('],
            vec!['(', '(', ')'],
        ]));
        assert!(!Solution::has_valid_path(vec![
            vec!['(', ')'],
            vec!['(', ')']
        ]));
    }
}
