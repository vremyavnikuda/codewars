impl Solution {
    pub fn create_grid(m: i32, n: i32, k: i32) -> Vec<String> {
        let q1 = m as usize;
        let q2 = n as usize;
        let q3 = match k {
            1 => Some((1usize, 1usize, false)),
            2 => (q1 >= 2 && q2 >= 2).then_some((2, 2, false)),
            3 => {
                if q2 >= 3 && q1 >= 2 {
                    Some((2, 3, false))
                } else if q1 >= 3 && q2 >= 2 {
                    Some((3, 2, false))
                } else {
                    None
                }
            }
            4 => {
                if q2 >= 4 && q1 >= 2 {
                    Some((2, 4, false))
                } else if q1 >= 4 && q2 >= 2 {
                    Some((4, 2, false))
                } else if q1 >= 3 && q2 >= 3 {
                    Some((3, 3, true))
                } else {
                    None
                }
            }
            _ => None,
        };
        let (a1, a2, a3) = match q3 {
            Some(q4) => q4,
            None => return Vec::new(),
        };
        let (b1, b2) = (a1 - 1, a2 - 1);
        (0..q1)
            .map(|q5| {
                (0..q2)
                    .map(|q6| {
                        let a4 = if q5 < a1 && q6 < a2 {
                            !(a3 && ((q5 == 0 && q6 == a2 - 1) || (q5 == a1 - 1 && q6 == 0)))
                        } else {
                            (q5 == b1 && q6 >= b2) || (q6 == q2 - 1 && q5 >= b1)
                        };
                        if a4 { '.' } else { '#' }
                    })
                    .collect::<String>()
            })
            .collect()
    }
}