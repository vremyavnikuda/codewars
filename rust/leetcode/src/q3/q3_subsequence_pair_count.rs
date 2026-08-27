impl Solution {
    pub fn subsequence_pair_count(nums: Vec<i32>) -> i32 {
        fn q1(mut q2: usize, mut q3: usize) -> usize {
            while q3 != 0 {
                let q4 = q2 % q3;
                q2 = q3;
                q3 = q4;
            }
            q2
        }
        const A1: i32 = 1_000_000_007;
        const A2: usize = 201;
        let mut q2 = [[0i32; A2]; A2];
        q2[0][0] = 1;
        for &q3 in nums.iter() {
            let q4 = q3 as usize;
            let mut q5 = [0usize; A2];
            for q6 in 0..A2 {
                q5[q6] = q1(q6, q4);
            }
            let mut q6 = q2;
            for a1 in 0..A2 {
                for a2 in 0..A2 {
                    let a3 = q2[a1][a2];
                    if a3 == 0 {
                        continue;
                    }
                    let a4 = q5[a1];
                    let a5 = q5[a2];
                    q6[a4][a2] += a3;
                    if q6[a4][a2] >= A1 {
                        q6[a4][a2] -= A1;
                    }
                    q6[a1][a5] += a3;
                    if q6[a1][a5] >= A1 {
                        q6[a1][a5] -= A1;
                    }
                }
            }
            q2 = q6;
        }
        let mut q3 = 0;
        for q4 in 1..A2 {
            q3 += q2[q4][q4];
            if q3 >= A1 {
                q3 -= A1;
            }
        }
        q3
    }
}
