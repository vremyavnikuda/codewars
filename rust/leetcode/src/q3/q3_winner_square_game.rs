impl Solution {
    pub fn winner_square_game(n: i32) -> bool {
        let q1 = n as usize;
        let mut a1 = vec![false; q1 + 1];
        for a2 in 1..=q1 {
            let mut a3 = 1;
            while a3 * a3 <= a2 {
                if !a1[a2 - a3 * a3] {
                    a1[a2] = true;
                    break;
                }
                a3 += 1;
            }
        }
        a1[q1]
    }
}
