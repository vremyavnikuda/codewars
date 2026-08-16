impl Solution {
    pub fn stone_game_ix(stones: Vec<i32>) -> bool {
        let mut q1 = [0; 3];
        for a1 in stones {
            q1[a1.rem_euclid(3) as usize] += 1;
        }
        let mut q2 = [q1[0], q1[2], q1[1]];
        fn q3(q4: &mut [i32; 3]) -> bool {
            if q4[1] == 0 {
                return false;
            }
            q4[1] -= 1;
            let mut a2 = 1 + q4[1].min(q4[2]) * 2 + q4[0];
            if q4[1] > q4[2] {
                q4[1] -= 1;
                a2 += 1;
            }
            a2 % 2 == 1 && q4[1] != q4[2]
        }
        q3(&mut q1) || q3(&mut q2)
    }
}
