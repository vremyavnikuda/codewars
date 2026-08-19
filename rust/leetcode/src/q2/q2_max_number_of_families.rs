impl Solution {
    pub fn max_number_of_families(n: i32, reserved_seats: Vec<Vec<i32>>) -> i32 {
        let mut q1 = reserved_seats;
        q1.sort_unstable();
        let q2 = [0b0111100000, 0b0000011110, 0b0001111000];
        let mut q3 = n * 2;
        for q0 in q1.chunk_by(|q4, q5| q4[0] == q5[0]) {
            let mut q6 = q0.iter().fold(0, |a1, a2| a1 | (1 << (10 - a2[1])));
            let mut q7 = 0;
            for &q8 in &q2 {
                if (q6 & q8) == 0 {
                    q6 |= q8;
                    q7 += 1;
                }
            }
            q3 += q7 - 2;
        }
        q3
    }
}
