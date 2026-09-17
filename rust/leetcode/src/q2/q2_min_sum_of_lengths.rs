pub struct Solution;

impl Solution {
    #[inline(always)]
    pub fn min_sum_of_lengths(arr: Vec<i32>, target: i32) -> i32 {
        // ponytail: arr[i] >= 1 => prefix sums strictly increase, so two pointers replace the hash map.
        // Single Vec<i32> scratch is the only allocation (prefix-min of the best window ending before i).
        let aa = arr.len();
        let bb = 1i32 << 30;
        let mut cc = vec![bb; aa + 1];
        let (mut dd, mut ee, mut ff) = (0i32, 0usize, bb);
        for gg in 0..aa {
            dd += arr[gg];
            while dd > target {
                dd -= arr[ee];
                ee += 1;
            }
            cc[gg + 1] = cc[gg];
            if dd == target {
                let hh = (gg + 1 - ee) as i32;
                cc[gg + 1] = cc[gg + 1].min(hh);
                ff = ff.min(cc[ee] + hh);
            }
        }
        if ff >= bb {
            -1
        } else {
            ff
        }
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn t1() {
        assert_eq!(Solution::min_sum_of_lengths(vec![3, 2, 2, 4, 3], 3), 2);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::min_sum_of_lengths(vec![7, 3, 4, 7], 7), 2);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::min_sum_of_lengths(vec![4, 3, 2, 6, 2, 3, 4], 6), -1);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::min_sum_of_lengths(vec![1, 1, 1, 1, 1, 1], 3), 6);
    }
}
