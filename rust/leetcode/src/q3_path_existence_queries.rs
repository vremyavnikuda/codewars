impl Solution {
    pub fn path_existence_queries(
        n: i32,
        nums: Vec<i32>,
        max_diff: i32,
        queries: Vec<Vec<i32>>,
    ) -> Vec<i32> {
        let n = n as usize;
        let mut q1: Vec<(i32, usize)> = Vec::with_capacity(n);
        for (q2, &q3) in nums.iter().enumerate() {
            q1.push((q3, q2));
        }
        q1.sort_unstable();
        let m = 20;
        let mut q4: Vec<Vec<usize>> = vec![vec![0; m]; n];
        let mut q5 = n - 1;
        for q6 in (0..n).rev() {
            while q1[q5].0 - q1[q6].0 > max_diff {
                q5 -= 1;
            }
            let q7 = q1[q6].1;
            let q8 = q1[q5].1;
            q4[q7][0] = q8;
            for q9 in 1..m {
                q4[q7][q9] = q4[q4[q7][q9 - 1]][q9 - 1];
            }
        }
        let mut q0: Vec<i32> = Vec::with_capacity(queries.len());
        for qq in &queries {
            let mut a1 = qq[0] as usize;
            let mut a2 = qq[1] as usize;
            if nums[a1] > nums[a2] {
                std::mem::swap(&mut a1, &mut a2);
            }
            if a1 == a2 {
                q0.push(0);
                continue;
            }
            if nums[a1] == nums[a2] {
                q0.push(1);
                continue;
            }
            let mut a3 = 0i32;
            for a4 in (0..m).rev() {
                if nums[q4[a1][a4]] < nums[a2] {
                    a3 |= 1 << a4;
                    a1 = q4[a1][a4];
                }
            }
            if nums[q4[a1][0]] < nums[a2] {
                q0.push(-1);
            } else {
                q0.push(a3 + 1);
            }
        }
        q0
    }
}
