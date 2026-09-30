impl Solution {
    pub fn max_depth_after_split(seq: String) -> Vec<i32> {
        let mut aa = 0_i32;
        seq.bytes()
            .map(|bb| {
                if bb == b'(' {
                    aa += 1;
                    (aa - 1) & 1
                } else {
                    aa -= 1;
                    aa & 1
                }
            })
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn aa() {
        assert_eq!(
            Solution::max_depth_after_split("(()())".into()),
            [0, 1, 1, 1, 1, 0]
        );
        assert_eq!(
            Solution::max_depth_after_split("()(())".into()),
            [0, 0, 0, 1, 1, 0]
        );
        assert_eq!(
            Solution::max_depth_after_split("((()))".into()),
            [0, 1, 0, 0, 1, 0]
        );
    }
}
