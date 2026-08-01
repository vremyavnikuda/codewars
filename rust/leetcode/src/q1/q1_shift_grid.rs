impl Solution {
    pub fn shift_grid(grid: Vec<Vec<i32>>, k: i32) -> Vec<Vec<i32>> {
        let mut q1 = grid;
        let q2 = q1.len();
        if q2 == 0 {
            return q1;
        }
        let q3 = q1[0].len();
        let q4 = q2 * q3;
        if q4 == 0 {
            return q1;
        }
        let q5 = k as usize % q4;
        if q5 == 0 {
            return q1;
        }
        let mut q6 = 0;
        let mut q7 = 0;
        while q6 < q4 {
            let mut q8 = q7;
            let mut q9 = q1[q8 / q3][q8 % q3];
            loop {
                let q10 = (q8 + q5) % q4;
                let q11 = std::mem::replace(&mut q1[q10 / q3][q10 % q3], q9);
                q8 = q10;
                q9 = q11;
                q6 += 1;

                if q8 == q7 {
                    break;
                }
            }
            q7 += 1;
        }
        q1
    }
}
