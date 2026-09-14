impl Solution {
    pub fn is_rectangle_overlap(rec1: Vec<i32>, rec2: Vec<i32>) -> bool {
        let (aa, bb, cc, dd) = (rec1[0], rec1[1], rec1[2], rec1[3]);
        let (ee, ff, gg, hh) = (rec2[0], rec2[1], rec2[2], rec2[3]);
        aa < gg && ee < cc && bb < hh && ff < dd
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn t0() {
        assert!(Solution::is_rectangle_overlap(vec![0, 0, 2, 2], vec![1, 1, 3, 3]));
        assert!(!Solution::is_rectangle_overlap(vec![0, 0, 1, 1], vec![1, 0, 2, 1]));
        assert!(!Solution::is_rectangle_overlap(vec![0, 0, 1, 1], vec![2, 2, 3, 3]));
    }
}
