pub struct Solution;

impl Solution {
    #[inline(always)]
    pub fn number_of_sets(n: i32, k: i32) -> i32 {
        // ponytail: k <= n-1 <= 999 per constraints, so fixed stack buffers — zero heap.
        let (aa, bb) = (1_000_000_007i64, k as usize);
        let (mut cc, mut dd) = ([0i64; 1000], [0i64; 1000]);
        cc[0] = 1;
        for _ in 1..n {
            for ee in (0..=bb).rev() {
                let ff = dd[ee];
                cc[ee] = (cc[ee] + ff) % aa;
                if ee > 0 {
                    dd[ee] = (ff + cc[ee - 1] + dd[ee - 1]) % aa;
                }
            }
        }
        ((cc[bb] + dd[bb]) % aa) as i32
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn it_works() {
        assert_eq!(Solution::number_of_sets(4, 2), 5);
        assert_eq!(Solution::number_of_sets(3, 1), 3);
        assert_eq!(Solution::number_of_sets(30, 7), 796297179);
    }
}
