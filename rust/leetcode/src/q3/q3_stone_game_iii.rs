impl Solution {
    pub fn stone_game_iii(stone_value: Vec<i32>) -> String {
        let (mut q1, mut q2, mut q3) = (0i32, 0i32, 0i32);
        for i in (0..stone_value.len()).rev() {
            let mut a1 = 0i32;
            let mut a2 = i32::MIN;
            for k in 0..3 {
                if i + k >= stone_value.len() {
                    break;
                }
                a1 += stone_value[i + k];
                let a3 = match k {
                    0 => q1,
                    1 => q2,
                    _ => q3,
                };
                a2 = a2.max(a1 - a3);
            }
            q3 = q2;
            q2 = q1;
            q1 = a2;
        }
        if q1 > 0 {
            "Alice".to_string()
        } else if q1 < 0 {
            "Bob".to_string()
        } else {
            "Tie".to_string()
        }
    }
}
